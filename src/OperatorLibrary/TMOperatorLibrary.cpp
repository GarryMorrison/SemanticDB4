//
// Semantic DB 4
// Created 2023/5/16
// Updated 2023/5/16
// Author Garry Morrison
// License GPL v3
//

#include "TMOperatorLibrary.h"

Superposition TM_head_vec_to_sp(std::vector<std::vector<size_t>>& hash_vec, std::map<size_t, std::string>& merged_string_map, std::string& seq_merge_str)
{
    Superposition result_sp;
    for (const auto& vec : hash_vec)
    {
        std::string working_string;
        bool first_pass = true;
        for (size_t hash : vec)
        {
            if (!first_pass)
            {
                working_string.append(seq_merge_str);
            }
            first_pass = false;
            working_string.append(merged_string_map[hash]);
        }
        result_sp.add(working_string);
    }
    return result_sp;
}

std::vector<std::vector<size_t>> TM_partition_sequence(size_t pos, size_t max_len, std::vector<uint32_t>& vec, std::map<size_t, bool>& exists_map)
{
    // std::cout << "vec size: " << vec.size() << "\n";
    // std::cout << "pos: " << pos << "\n";

    size_t vec_size = vec.size();
    std::vector<std::vector<size_t>> result;
    if (pos >= vec_size) { return result; }
    if (pos + 1 == vec_size)
    {
        std::vector<uint32_t> local_vec;
        local_vec.push_back(vec[pos]);
        size_t local_hash = int_vector_to_hash(local_vec);
        std::vector<size_t> local_seq;
        local_seq.push_back(local_hash);
        result.push_back(local_seq);
        return result;
    }
    std::vector<uint32_t> local_vec;
    size_t max_i = std::min(pos + max_len, vec_size);
    for (size_t i = pos; i < max_i; i++)
    {
        local_vec.push_back(vec[i]);
        size_t local_hash = int_vector_to_hash(local_vec);
        if (exists_map.find(local_hash) != exists_map.end())
        {
            std::vector<size_t> head_vec;
            head_vec.push_back(local_hash);
            std::vector<std::vector<size_t>> tail_vec = TM_partition_sequence(i + 1, max_len, vec, exists_map);
            if (tail_vec.empty())
            {
                result.push_back(std::move(head_vec));
            }
            else
            {
                for (const auto& tail : tail_vec)
                {
                    std::vector<size_t> head_tail_vec(head_vec);
                    head_tail_vec.insert(head_tail_vec.end(), tail.begin(), tail.end());
                    result.push_back(std::move(head_tail_vec));
                }
            }
        }
    }
    return result;
}

Superposition op_TM_ngram_partition(const Sequence& input_seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters)
{
    Superposition result;
    // Check correct input sizes:
    if (parameters.size() != 2 && parameters.size() != 4) { return result; }
    if (input_seq.size() <= 1) { return input_seq.to_sp(); }
    size_t size = input_seq.size();

    // Now unpack our parameters:
    ulong op_idx = parameters[0]->get_operator().get_idx();
    size_t max_ngram_len = parameters[1]->get_int();

    std::string merge_str = " ";  // Set default values, if not specified in parameters:
    std::string seq_merge_str = " . ";

    if (parameters.size() == 4)
    {
        merge_str = parameters[2]->get_string();  // Note, if you don't use default values, make sure your operator is acting on the appropriate ket.
        seq_merge_str = parameters[3]->get_string();
    }

    // Populate ket_vec with our ket indices:
    std::vector<ulong> ket_vec;
    std::vector<uint32_t> seq_vec;
    for (const auto& sp : input_seq)
    {
        ulong idx = sp.to_ket().label_idx();  // Yes, we assume the input sequence is a sequence of kets, not full superpositions!
        ket_vec.push_back(idx);
        seq_vec.push_back(static_cast<uint32_t>(idx));
    }

    std::map<size_t, bool> exists_map;
    std::map<size_t, std::string> merged_string_map;
    std::vector<uint32_t> working_vec;
    std::size_t working_hash;
    std::string working_str;

    // Load some dummy/test data:
    // context.learn(ket_map.get_str(op_idx), "A B C", "yes");
    // context.learn(ket_map.get_str(op_idx), "D E", "yes");

    // Now populate our maps:
    for (size_t pos = 0; pos < size; pos++)
    {
        working_vec.clear();
        working_str.clear();
        bool first_pass = true;
        size_t loop_size = std::min(size, pos + max_ngram_len);
        for (size_t i = pos; i < loop_size; i++)
        {
            if (first_pass)
            {
                working_vec.push_back(ket_vec[i]);
                working_hash = int_vector_to_hash(working_vec);
                working_str = ket_map.get_str(ket_vec[i]);
                merged_string_map.emplace(working_hash, working_str);
                exists_map.emplace(working_hash, true);

                first_pass = false;
            }
            else
            {
                working_vec.push_back(ket_vec[i]);
                working_hash = int_vector_to_hash(working_vec);
                working_str.append(merge_str);
                working_str.append(ket_map.get_str(ket_vec[i]));

                ulong working_idx = ket_map.get_idx(working_str);
                unsigned int rule_type = context.recall_type(op_idx, working_idx);
                if (rule_type == RULENORMAL)
                {
                    merged_string_map.emplace(working_hash, working_str);
                    exists_map.emplace(working_hash, true);
                }
            }
        }
    }

    /*
    // Now a quick look at what we know so far:
    for (const auto& it : merged_string_map)
    {
        std::cout << it.second << " \t" << std::boolalpha << exists_map[it.first] << "\n";
    }
    */

    std::vector<std::vector<size_t>> hash_vec = TM_partition_sequence(0, max_ngram_len, seq_vec, exists_map);

    return TM_head_vec_to_sp(hash_vec, merged_string_map, seq_merge_str);
}

