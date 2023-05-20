//
// Semantic DB 4
// Created 2023/5/16
// Updated 2023/5/16
// Author Garry Morrison
// License GPL v3
//


#include "TMOperatorLibrary.h"



// Copied from here:
// https://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector
std::size_t int_vector_to_hash(const std::vector<ulong>& vec)
{
    std::size_t seed = vec.size();
    for (auto y : vec)
    {
        uint32_t x = static_cast<uint32_t>(y);  // Not sure if the magic numbers work with ulong, so we cast them to uint32_t first.
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = (x >> 16) ^ x;
        seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}


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

                // ulong working_idx = ket_map.get_idx(working_str);  // Causes ket-map "pollution", ie, filling the ket-map with strings we don't need to learn.
                ulong working_idx = ket_map.get_idx_if_known(working_str);  
                if (working_idx)   // working_idx is 0 if not known. In which case it can't be a RULENORMAL, as we would already know it.
                {
                    unsigned int rule_type = context.recall_type(op_idx, working_idx);
                    if (rule_type == RULENORMAL)
                    {
                        merged_string_map.emplace(working_hash, working_str);
                        exists_map.emplace(working_hash, true);
                    }
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

Ket op_TM_sequence_hash(const Sequence& input_seq)
{
    if (input_seq.is_empty_ket()) { return Ket(); }

    std::string working_string;
    for (const auto& sp : input_seq)
    {
        working_string.append(sp.to_ket().label());
    }
    uint32_t hash = APHash(working_string.c_str(), static_cast<uint32_t>(working_string.size()));
    return Ket(std::to_string(hash));
}

Ket op_TM_ket_hash(const Ket& k)
{
    if (k.is_empty_ket()) { return Ket(); }
    uint32_t hash = APHash(k.label().c_str(), static_cast<uint32_t>(k.label().size()));
    return Ket(std::to_string(hash), k.value());
}


Ket op_TM_extract_text(const Sequence& input_seq, const Sequence& one)
{
    if (input_seq.is_empty_ket() || one.is_empty_ket()) { return Ket(); }
    size_t input_size = input_seq.size();
    Superposition local_sp = one.to_sp();
    std::vector<int> int_vec;
    for (const auto& k : local_sp)  // Maybe use superposition::get_idx_vector() instead of iterating with kets?
    {
        int current_val = -1;
        try {
            current_val = std::stoi(k.label());
            if (current_val >= 1 && current_val <= input_size)
            {
                int_vec.push_back(current_val);
            }
        }
        catch (const std::invalid_argument& e) {
            (void)e;  // Needed to suppress C4101 warning.
            continue;
        }
    }
    if (int_vec.empty()) { return Ket(); }
    std::sort(int_vec.begin(), int_vec.end());
    std::string working_str;
    bool first_pass = true;
    int previous_i = -1;
    for (int current_i : int_vec)
    {
        if (!first_pass)
        {
            if (previous_i + 1 == current_i)
            {
                working_str.append(" "); // Yeah, hard-coded in space and underline chars for now.
            }
            else
            {
                working_str.append(" _ ");
            }
        }
        working_str.append(input_seq.get(current_i - 1).to_ket().label());
        previous_i = current_i;
        first_pass = false;
    }
    return Ket(working_str);
}

Ket op_TM_learn_sentences(const Sequence& input_seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters)
{
    // Make sure we have the right input conditions:
    if (input_seq.is_empty_ket() || parameters.size() != 1) { return Ket("0"); }

    // Learn a bunch of indices:
    ulong splitter_idx = parameters[0]->get_operator().get_idx();
    ulong sentence_template_idx = ket_map.get_idx("sentence-template");
    ulong sentence_length_idx = ket_map.get_idx("sentence-length");
    ulong sentence_type_idx = ket_map.get_idx("sentence-type");
    ulong sentence_value_idx = ket_map.get_idx("sentence-value");

    // Find max sentence node, so we don't stomp on it, and write to new node numbers:
    // Perhaps, instead, just use a global variable that stores the current max sentence number? Would be faster!
    std::vector<ulong> rel_kets_vec = context.relevant_kets(sentence_template_idx);
    int max_sentence_node = 0;
    for (ulong idx : rel_kets_vec)
    {
        ulong value_idx = ket_map.get_value_idx(idx);
        try
        {
            int sentence_node_number = std::stoi(ket_map.get_str(value_idx));
            max_sentence_node = std::max(max_sentence_node, sentence_node_number);
        }
        catch (const std::invalid_argument& e) {
            (void)e;  // Needed to suppress C4101 warning.
            continue;
        }
    }

    // Now, with the preamble out of the way, we can learn our sentences:
    int new_sentence_count = 0;
    std::vector<ulong> input_idx_vec = input_seq.to_sp().get_idx_vector();
    for (ulong input_idx : input_idx_vec)
    {
        Sequence our_template = context.active_recall(splitter_idx, input_idx);
        if (!our_template.is_empty_ket())
        {
            // House keeping:
            max_sentence_node++;
            new_sentence_count++;
            
            // Build them:
            Sequence template_type(our_template);
            Sequence template_value(our_template);
            template_type.extract_head();
            template_value.extract_value();

            // Now finally learn them:
            ulong node_idx = ket_map.get_idx("sentence: " + std::to_string(max_sentence_node));
            context.learn(sentence_template_idx, node_idx, our_template);
            context.learn(sentence_length_idx, node_idx, Sequence(std::to_string(our_template.size())));
            context.learn(sentence_type_idx, node_idx, template_type);
            context.learn(sentence_value_idx, node_idx, template_value);
        }
    }

    // Return the number of learn't sentences:
    return Ket(std::to_string(new_sentence_count));
}