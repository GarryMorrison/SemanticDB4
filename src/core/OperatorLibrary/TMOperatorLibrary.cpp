//
// Semantic DB 4
// Created 2023/5/16
// Updated 2023/5/16
// Author Garry Morrison
// License GPL v3
//


#include "TMOperatorLibrary.h"
#include "../Function/SplitJoin.h"



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

Ket op_TM_compress_stars(const Ket& k)
{
    if (k.is_empty_ket()) { return Ket(); }
    std::vector<std::string> split_str = split(k.label(), " ");
    std::string result_str;
    std::string replace_str = "..";
    int word_count = 0;
    bool first_pass = true;
    for (const auto& s : split_str)
    {
        if (s == "*")
        {
            if (!first_pass && !replace_str.empty())
            {
                result_str.append(" ");
            }
            result_str.append(replace_str);
            // replace_str = "";
            replace_str.clear();
        }
        else
        {
            if (!first_pass)
            {
                result_str.append(" ");
            }
            result_str.append(s);
            replace_str = "..";
            word_count++;
        }
        first_pass = false;
    }
    return Ket(result_str, word_count);
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
    ulong max_idx = ket_map.get_idx("max");
    // ulong sentence_length_idx = ket_map.get_idx("sentence length");
    ulong sentence_raw_idx = ket_map.get_idx("sentence-raw");
    ulong splitter_idx = parameters[0]->get_operator().get_idx();
    ulong sentence_template_idx = ket_map.get_idx("sentence-template");
    ulong sentence_length_idx = ket_map.get_idx("sentence-length");
    ulong sentence_type_idx = ket_map.get_idx("sentence-type");
    ulong sentence_value_idx = ket_map.get_idx("sentence-value");

    // Learn the currently known max sentence length:
    int max_sentence_len = 0;    // Should this be int or size_t?
    // First, try to load it:
    int rule_type = context.recall_type(max_idx, sentence_length_idx);
    if (rule_type == RULENORMAL)
    {
        std::string len_str = context.recall(max_idx, sentence_length_idx)->to_ket().label();
        // Now try to convert it to an integer:
        try
        {
            int len = std::stoi(len_str);
            max_sentence_len = std::max(max_sentence_len, len);
        }
        catch (const std::invalid_argument& e) {
            (void)e;  // Needed to suppress C4101 warning.
        }
    }

    // Find max sentence node, so we don't stomp on it, and write to new node numbers:
    // Perhaps, instead, just use a global variable that stores the current max sentence number? Would be faster!
    std::set<ulong> known_sentences_set;
    std::vector<ulong> rel_kets_vec = context.relevant_kets(sentence_template_idx);
    int max_sentence_node = 0;
    for (ulong idx : rel_kets_vec)
    {
        ulong value_idx = ket_map.get_value_idx(idx);
        try
        {
            int sentence_node_number = std::stoi(ket_map.get_str(value_idx));
            max_sentence_node = std::max(max_sentence_node, sentence_node_number);
            ulong sentence_idx = context.recall(sentence_raw_idx, idx)->to_ket().label_idx();
            known_sentences_set.insert(sentence_idx);
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
        if (known_sentences_set.find(input_idx) == known_sentences_set.end())
        {
            std::string raw_sentence = ket_map.get_str(input_idx);
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
                context.learn(sentence_raw_idx, node_idx, Sequence(raw_sentence));
                context.learn(sentence_template_idx, node_idx, our_template);
                context.learn(sentence_length_idx, node_idx, Sequence(std::to_string(our_template.size())));
                context.learn(sentence_type_idx, node_idx, template_type);
                context.learn(sentence_value_idx, node_idx, template_value);

                max_sentence_len = std::max(max_sentence_len, static_cast<int>(our_template.size()));
            }
        }
    }

    // Store new max sentence length:
    context.learn(max_idx, sentence_length_idx, Sequence(std::to_string(max_sentence_len)));

    // Return the number of learn't sentences:
    return Ket(std::to_string(new_sentence_count));
}

Superposition op_TM_generate(const Sequence& input_seq, ContextList& context)
{
    if (input_seq.is_empty_ket()) { return Superposition(); }
    std::vector<ulong> sentence_nodes = input_seq.to_sp().get_idx_vector();

    // Learn some indices:
    ulong max_idx = ket_map.get_idx("max");
    ulong sentence_length_idx = ket_map.get_idx("sentence-length");
    ulong template_node_idx = ket_map.get_idx("template-node");

    // Load in a couple of needed globals:
    std::string max_sentence_length_str = context.recall(max_idx, sentence_length_idx)->to_ket().label();
    std::string max_template_node_str = context.recall(max_idx, template_node_idx)->to_ket().label();

    // Try to convert them to integers:
    int max_sentence_length = 0;
    int max_template_node = 0;
    try
    {
        max_sentence_length = std::stoi(max_sentence_length_str);
        max_template_node = std::stoi(max_template_node_str);
    }
    catch (const std::invalid_argument& e) {
        (void)e;  // Needed to suppress C4101 warning.
    }
    // If max sentence length is 0, we have nothing to do, so return the empty ket:
    if (max_sentence_length == 0) { return Superposition(); }

    // Now, learn "empty" nodes:
    std::set<ulong> known_kets;
    std::string empty_node_text = "*";
    for (int i = 0; i < max_sentence_length; i++)
    {
        empty_node_text.append(" *");
        ulong empty_node_idx = ket_map.get_idx(empty_node_text);
        known_kets.insert(empty_node_idx);
        std::cout << "Empty node text: " << empty_node_text << "\n";
    }

    // Now load up the sentences into memory:
    // First learn some label to idx mappings:
    ulong sentence_raw_idx = ket_map.get_idx("sentence-raw");
    ulong sentence_type_idx = ket_map.get_idx("sentence-type");
    ulong sentence_value_idx = ket_map.get_idx("sentence-value");

    // Now load them:
    /*
    std::map<int, SentenceStruct> sentences;  // Use pointer here instead?
    int sentence_number = 0;
    for (ulong node_idx : sentence_nodes)
    {
        SentenceStruct local_sentence;
        local_sentence.node_idx = node_idx;
        local_sentence.raw_sentence_idx = context.recall(sentence_raw_idx, node_idx)->to_ket().label_idx();  // Check they are actually defined?
        local_sentence.type_vec = context.recall(sentence_type_idx, node_idx)->to_seq().get_idx_vector();
        local_sentence.value_vec = context.recall(sentence_value_idx, node_idx)->to_seq().get_idx_vector();
        local_sentence.size = local_sentence.type_vec.size();

        sentence_number++;
        sentences[sentence_number] = std::move(local_sentence);
    }
    */
    /*
    // Pointer version:
    std::map<int, std::shared_ptr<SentenceStruct>> sentences;
    int sentence_number = 0;
    for (ulong node_idx : sentence_nodes)
    {
        if (context.recall_type(sentence_raw_idx, node_idx) != RULENORMAL) { continue; }  // Check they are defined.
        if (context.recall_type(sentence_type_idx, node_idx) != RULENORMAL) { continue; }
        if (context.recall_type(sentence_value_idx, node_idx) != RULENORMAL) { continue; }

        std::shared_ptr<SentenceStruct> local_sentence = std::make_shared<SentenceStruct>();
        local_sentence->node_idx = node_idx;
        local_sentence->raw_sentence_idx = context.recall(sentence_raw_idx, node_idx)->to_ket().label_idx();
        local_sentence->type_vec = context.recall(sentence_type_idx, node_idx)->to_seq().get_idx_vector();
        local_sentence->value_vec = context.recall(sentence_value_idx, node_idx)->to_seq().get_idx_vector();
        if (local_sentence->type_vec.size() != local_sentence->value_vec.size()) { continue; }  // Sanity check they are both the same size.
        for (ulong value_idx : local_sentence->value_vec)
        {
            local_sentence->text_vec.push_back(ket_map.get_str(value_idx));
        }

        local_sentence->size = local_sentence->type_vec.size();

        sentence_number++;
        sentences[sentence_number] = local_sentence;
    }
    */
    // Next version:
    std::map<int, std::shared_ptr<TemplateMachine>> TMs;
    for (ulong node_idx : sentence_nodes)
    {
        if (context.recall_type(sentence_raw_idx, node_idx) != RULENORMAL) { continue; }  // Check they are defined.
        if (context.recall_type(sentence_type_idx, node_idx) != RULENORMAL) { continue; }
        if (context.recall_type(sentence_value_idx, node_idx) != RULENORMAL) { continue; }

        SentenceStruct sentence;
        sentence.node_idx = node_idx;
        sentence.raw_sentence_idx = context.recall(sentence_raw_idx, node_idx)->to_ket().label_idx();
        sentence.type_vec = context.recall(sentence_type_idx, node_idx)->to_seq().get_idx_vector();
        sentence.value_vec = context.recall(sentence_value_idx, node_idx)->to_seq().get_idx_vector();
        if (sentence.type_vec.size() != sentence.value_vec.size()) { continue; }  // Sanity check they are both the same size.
        for (ulong value_idx : sentence.value_vec)
        {
            sentence.text_vec.push_back(ket_map.get_str(value_idx));
        }

        sentence.size = sentence.type_vec.size();

        TM_seed(context, sentence, max_template_node, TMs);
    }

    TM_write_template_to_context(context, TMs);

    return Superposition("TM-generate");
}

void TM_seed(ContextList& context, const SentenceStruct& sentence, int& max_template_node, std::map<int, std::shared_ptr<TemplateMachine>>& TMs)
{
    ulong star_idx = ket_map.get_idx("*");
    ulong template_node_idx = ket_map.get_idx("template-node");
    size_t size = sentence.size;

    // Learn range_stars and range_non_stars:
    std::set<int> range_stars;
    std::set<int> range_non_stars;
    for (int i = 0; i < size; i++)
    {
        if (sentence.type_vec[i] == star_idx)
        {
            range_stars.insert(i);
        }
        else
        {
            range_non_stars.insert(i);
        }
    }

    // for (size_t i = 0; i < size; i++)
    for (int i : range_non_stars)
    {
        std::vector<std::string> local_text_vec(sentence.text_vec);
        if (local_text_vec[i] == "*") { continue; }  // If range_non_stars is correct, we probably don't need this check
        local_text_vec[i] = "*";
        bool first_pass = true;
        std::string local_text;
        for (const auto& s : local_text_vec)
        {
            if (!first_pass)
            {
                local_text.append(" ");
            }
            local_text.append(s);
            first_pass = false;
        }
        ulong local_text_idx = ket_map.get_idx(local_text);
        if (context.recall_type(template_node_idx, local_text_idx) == RULEUNDEFINED)
        {
            std::shared_ptr<TemplateMachine> local_TM = std::make_shared<TemplateMachine>();
            max_template_node++;
            std::string the_node = "node: " + std::to_string(max_template_node);
            context.learn(template_node_idx, local_text_idx, Sequence(the_node));
            ulong the_node_idx = ket_map.get_idx(the_node);

            local_TM->the_node_idx = the_node_idx;
            local_TM->size = size;
            local_TM->text_vec = std::move(local_text_vec);
            local_TM->type_vec = sentence.type_vec;
            local_TM->value_vec = sentence.value_vec;
            local_TM->type_vec[i] = star_idx;
            local_TM->value_vec[i] = star_idx;

            Ket compressed_text_ket = op_TM_compress_stars(Ket(local_text_idx));
            local_TM->compressed_text = compressed_text_ket.label();
            local_TM->structure_word_count = static_cast<int>(compressed_text_ket.value());
            local_TM->compressed_text_idx = ket_map.get_idx(local_TM->compressed_text);

            local_TM->range_stars = range_stars;
            local_TM->range_non_stars = range_non_stars;
            local_TM->range_stars.insert(i);
            local_TM->range_non_stars.erase(i);

            TMs[max_template_node] = local_TM;
        }
    }
}

void TM_write_template_to_context(ContextList& context, std::map<int, std::shared_ptr<TemplateMachine>>& TMs)
{
    // First, learn some string to idx mappings:
    ulong template_type_idx = ket_map.get_idx("template-type");
    ulong template_value_idx = ket_map.get_idx("template-value");
    ulong length_idx = ket_map.get_idx("length");
    ulong compressed_text_idx = ket_map.get_idx("compressed-text");
    ulong activation_count_idx = ket_map.get_idx("activation-count");
    ulong structure_word_count_idx = ket_map.get_idx("structure-word-count");
    ulong range_star_idx = ket_map.get_idx("range-star");
    ulong range_non_star_idx = ket_map.get_idx("range-non-star");

    //  Now write them to context:
    for (const auto iter : TMs)
    {
        ulong node_idx = iter.second->the_node_idx;
        context.learn(compressed_text_idx, node_idx, Sequence(iter.second->compressed_text));
        context.learn(template_type_idx, node_idx, Sequence(iter.second->type_vec));
        context.learn(template_value_idx, node_idx, Sequence(iter.second->value_vec));
        context.learn(length_idx, node_idx, Sequence(std::to_string(iter.second->size)));

        // Create range_star and range_non_star superpositions:
        Superposition range_star_sp;
        Superposition range_non_star_sp;
        for (int i : iter.second->range_stars)
        {
            range_star_sp.add(std::to_string(i + 1));
        }
        for (int i : iter.second->range_non_stars)
        {
            range_non_star_sp.add(std::to_string(i + 1));
        }

        context.learn(range_star_idx, node_idx, range_star_sp);
        context.learn(range_non_star_idx, node_idx, range_non_star_sp);

        context.learn(structure_word_count_idx, iter.second->compressed_text_idx, Sequence(std::to_string(iter.second->structure_word_count)));
    }
}
