//
// Created by Garry Morrison on 21/09/2020.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <iomanip>
#include <cmath>
#include <set>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include "OperatorLibrary.h"
#include "../CompoundConstant/ConstantString.h"
#include "../Function/misc.h"
#include "FunctionOperatorLibrary.h"
#include "../Sequence/SelfKet.h"
#include "../Operator/FunctionOperator.h"


Superposition split(const Ket k) {
    Superposition sp;
    for (const auto c : k.label()) {
        std::string s;
        s.push_back(c);
        sp.add(s, k.value());
    }
    return sp;
}

Superposition split(const Ket k, const std::string& delimiter) {
    if (delimiter.empty()) { return split(k); }
    Superposition sp;
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::string s = k.label();
    double value = k.value();

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        sp.add(token, value);
    }
    sp.add(s.substr(pos_start), value);
    return sp;
}

Superposition op_split(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    // if (parameters.empty()) { return Superposition(); }  // Maybe return split(k) instead?
    if (parameters.empty()) { return split(k); }
    // std::string delim = std::dynamic_pointer_cast<ConstantString>(parameters[0])->get_string();
    std::string delim = parameters[0]->get_string();
    return split(k, delim);
}

Sequence ssplit(const Ket k) {
    Sequence seq;
    /*
    for (const auto c : k.label()) {
        // std::cout << c << std::endl;
        std::string s;
        s.push_back(c);
        // Ket k2(s, k.value());
        seq.append(s, k.value());
    }
    */
    for (char c : k.label())
    {
        seq.append(std::string(1, c), k.value());
    }
    return seq;
}

Sequence ssplit(const Ket k, const std::string& delimiter) {
    if (delimiter.empty()) { return ssplit(k); }
    Sequence seq;
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::string s = k.label();
    double value = k.value();

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);  // Maybe use string_view instead: https://www.youtube.com/watch?v=ZO68JEgoPeg
        pos_start = pos_end + delim_len;
        // Ket k2(token, value);
        seq.append(token, value);
    }
    // Ket k2(s.substr(pos_start), value);
    seq.append(s.substr(pos_start), value);
    return seq;
}

/*
Sequence ssplit(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> > &parameters) {
    // if (parameters.empty()) { return Sequence(); }  // Maybe return ssplit(k) instead?
    if (parameters.empty()) { return ssplit(k); }
    // std::string delim = std::dynamic_pointer_cast<ConstantString>(parameters[0])->get_string();
    std::string delim = parameters[0]->get_string();
    return ssplit(k, delim);
}
*/

Sequence op_ssplit(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return ssplit(k); }
    std::string delim = parameters[0]->get_string();
    return ssplit(k, delim);
}

Superposition op_split_ket(const Ket k) {
    return split(k);
}

Sequence op_ssplit_ket(const Ket k) {
    Sequence seq;
    for (char c : k.label())
    {
        seq.append(std::string(1, c), k.value());
    }
    return seq;
}

Ket extract_head(const Ket k) {
    ulong head_idx = ket_map.get_head_idx(k.label_idx());
    return Ket(head_idx, k.value());
}

Ket extract_tail(const Ket k) {
    ulong tail_idx = ket_map.get_tail_idx(k.label_idx());
    return Ket(tail_idx, k.value());
}

Ket extract_category(const Ket k) {
    ulong category_idx = ket_map.get_category_idx(k.label_idx());
    return Ket(category_idx, k.value());
}

Ket extract_value(const Ket k) {
    ulong value_idx = ket_map.get_value_idx(k.label_idx());
    return Ket(value_idx, k.value());
}

Ket extract_headless(const Ket k) {
    ulong headless_idx = ket_map.get_headless_idx(k.label_idx());
    return Ket(headless_idx, k.value());
}

// Sequence based versions of extract-*:
Sequence op_extract_head(const Sequence& input_seq)
{
    Sequence result(input_seq);
    result.extract_head();
    return result;
}

Sequence op_extract_tail(const Sequence& input_seq)
{
    Sequence result(input_seq);
    result.extract_tail();
    return result;
}

Sequence op_extract_category(const Sequence& input_seq)
{
    Sequence result(input_seq);
    result.extract_category();
    return result;
}

Sequence op_extract_value(const Sequence& input_seq)
{
    Sequence result(input_seq);
    result.extract_value();
    return result;
}

Sequence op_extract_headless(const Sequence& input_seq)
{
    Sequence result(input_seq);
    result.extract_headless();
    return result;
}


Ket op_floor(const Ket& k) {
    auto idx_vec = k.label_split_idx();
    if (idx_vec.empty()) { return Ket(); }
    try {
        long double value = std::floor(std::stold(ket_map.get_str(idx_vec.back())));
        idx_vec.pop_back();
        std::string label = ket_map.get_str(idx_vec);  // What happens if idx_vec is empty?
        if (label.length() > 0) { label += ": "; }
        return Ket(label + float_to_int(value, default_decimal_places), k.value());
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return k;
    }
}

Ket op_ceiling(const Ket& k) {
    auto idx_vec = k.label_split_idx();
    if (idx_vec.empty()) { return Ket(); }
    try {
        long double value = std::ceil(std::stold(ket_map.get_str(idx_vec.back())));
        idx_vec.pop_back();
        std::string label = ket_map.get_str(idx_vec);  // What happens if idx_vec is empty?
        if (label.length() > 0) { label += ": "; }
        return Ket(label + float_to_int(value, default_decimal_places), k.value());
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return k;
    }
}

Ket op_log(const Ket& k) {
    auto idx_vec = k.label_split_idx();
    if (idx_vec.empty()) { return Ket(); }
    try {
        long double value = std::log(std::stold(ket_map.get_str(idx_vec.back())));
        idx_vec.pop_back();
        std::string label = ket_map.get_str(idx_vec);  // What happens if idx_vec is empty?
        if (label.length() > 0) { label += ": "; }
        return Ket(label + float_to_int(value, default_decimal_places), k.value());
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return k;
    }
}



Ket ket_length(const Ket k) {
    size_t len = k.label().size();
    return Ket("number: " + std::to_string(len), k.value());
}

Ket push_float(const Ket& k) {
    if (k.label_idx() == ket_map.get_idx("")) { return k; }
    // std::cout << "push-float, decimal places: " << default_decimal_places << "\n";
    std::string label = k.label();

    if (label == " ") {
        label = "";
    }
    else {
        label += ": ";
    }
    return Ket(label + float_to_int(k.value(), default_decimal_places));
}

Ket pop_float(const Ket& k) {
    auto k_vec = k.label_split_idx();
    if (k_vec.empty()) { return Ket(); } // should never happen
    std::string value_str = ket_map.get_str(k_vec.back());
    try {
        double value = std::stod(value_str);
        if (k_vec.size() == 1) {
            return Ket(" ", value * k.value());
        }
        k_vec.pop_back();
        ulong label_idx = ket_map.get_idx(k_vec);
        return Ket(label_idx, value * k.value());
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return k;
    }
}

Superposition rank(const Superposition& sp) {
    Superposition result;
    ulong pos = 0;
    for (const auto k : sp) {
        pos++;
        result.add(k.label_idx(), pos);
    }
    return result;
}

Sequence sp2seq(const Superposition& sp) {
    Sequence result;
    for (const auto k : sp) {
        result.append(k);
    }
    return result;
}

Superposition seq2sp(const Sequence& seq) {
    Superposition result;
    for (const auto& sp : seq) {
        result.add(sp);
    }
    return result;
}

Ket bar_chart(const Superposition& sp, const unsigned int width) {
    if (sp.size() == 0 || width <= 0) { return Ket(); }

    size_t max_len = 0;
    for (const auto k : sp) {
        max_len = std::max(k.label().size(), max_len);
    }
    // Superposition one = sp.rescale(width); // do we need .drop() too? Probably.
    Superposition one = sp.drop().rescale(width);
    std::cout << "----------" << std::endl;
    for (const auto k : one) {
        std::cout << std::left << std::setfill(' ') << std::setw(max_len) << k.label() << " : ";
        std::cout << std::setfill('|') << std::setw((ulong)k.value()) << "|" << std::endl;
    }
    std::cout << "----------" << std::endl;
    return Ket("bar chart");
}

Ket op_bar_chart(const Superposition& sp, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    unsigned int width = 10;
    if (parameters.empty()) {
        width = 10;
    }
    else {
        width = parameters[0]->get_int();
    }
    return bar_chart(sp, width);
}

Ket op_raw_bar_chart(const Superposition& sp)
{
    if (sp.is_empty_ket()) { return Ket(); }
    size_t max_len = 0;
    for (const auto k : sp)
    {
        max_len = std::max(k.label().size(), max_len);
    }
    std::cout << "----------" << std::endl;
    for (const auto k : sp) {
        std::cout << std::left << std::setfill(' ') << std::setw(max_len) << k.label() << " : ";
        std::cout << std::setfill('|') << std::setw((ulong)k.value()) << "|" << std::endl;
    }
    std::cout << "----------" << std::endl;
    return Ket("raw bar chart");
}

Ket print_ket(const Ket k) {
    // std::cout << k.label() << std::endl;
    std::cout << k.label() << "\n";
    return k;
}

Superposition op_relevant_kets(const Sequence& seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return Superposition(); }
    Superposition result;
    for (const auto& param : parameters) {
        ulong op_idx = param->get_operator().get_idx();
        // Superposition tmp(context.relevant_kets(op_idx));
        // result.add(tmp);
        result.add(context.relevant_kets(op_idx));
    }
    return result;
}

Superposition op_similar_input(const Sequence& seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return Superposition(); }  // Alternatively, return seq.
    ulong op_idx = parameters[0]->get_operator().get_idx();
    std::vector<ulong> ket_vec = context.relevant_kets(op_idx);
    double min_score = 0;
    if (parameters.size() == 2) {
        min_score = parameters[1]->get_float();  // Caused a seg-fault at train-image: 282. digit2sp[4].
    }
    Superposition result;
    for (const ulong label_idx : ket_vec) {
        Sequence pattern = context.recall(op_idx, label_idx)->to_seq();  // active recall? Would that stomp on memoize rules too?
        double score = simm(seq, pattern);
        if (score > min_score) {
            result.add(label_idx, score);
        }
    }
    result.coeff_sort();
    return result;
    /*
    switch (parameters.size()) {
        case 1: { return result; }
        case 2: {
            int stop = parameters[1]->get_int();
            return result.select(1, stop);
            }
        case 3: {
            int start = parameters[1]->get_int();
            int stop = parameters[2]->get_int();
            return result.select(start, stop);  // Bug here if stop > len(result)
        }
        default: return Superposition();  // Alternatively, we could return seq.
    }
    */
}

Superposition op_strict_similar_input(const Sequence& seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return Superposition(); }  // Alternatively, return seq.
    ulong op_idx = parameters[0]->get_operator().get_idx();
    std::vector<ulong> ket_vec = context.relevant_kets(op_idx);
    Superposition result;
    for (const ulong label_idx : ket_vec) {
        Sequence pattern = context.recall(op_idx, label_idx)->to_seq();  // active recall? Would that stomp on memoize rules too?
        double score = strict_simm(seq, pattern);
        if (score > 0) {
            result.add(label_idx, score);
        }
    }
    result.coeff_sort();
    switch (parameters.size()) {
    case 1: { return result; }
    case 2: {
        int stop = parameters[1]->get_int();
        return result.select(1, stop);
    }
    case 3: {
        int start = parameters[1]->get_int();
        int stop = parameters[2]->get_int();
        return result.select(start, stop);
    }
    default: return Superposition();  // Alternatively, we could return seq.
    }
}

Superposition op_natural_similar_input(const Sequence& seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return Superposition(); }  // Alternatively, return seq.
    ulong op_idx = parameters[0]->get_operator().get_idx();
    std::vector<ulong> ket_vec = context.relevant_kets(op_idx);
    double min_score = 0;
    if (parameters.size() == 2) {
        min_score = parameters[1]->get_float();  // Caused a seg-fault at train-image: 282. digit2sp[4].
    }
    Superposition result;
    for (const ulong label_idx : ket_vec) {
        Sequence pattern = context.recall(op_idx, label_idx)->to_seq();  // active recall? Would that stomp on memoize rules too?
        double score = natural_simm(seq, pattern);
        if (score > min_score) {
            result.add(label_idx, score);
        }
    }
    result.coeff_sort();
    return result;
}

Superposition op_unscaled_similar_input(const Sequence& seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return Superposition(); }  // Alternatively, return seq.
    ulong op_idx = parameters[0]->get_operator().get_idx();
    std::vector<ulong> ket_vec = context.relevant_kets(op_idx);
    double min_score = 0;
    if (parameters.size() == 2) {
        min_score = parameters[1]->get_float();  // Caused a seg-fault at train-image: 282. digit2sp[4].
    }
    Superposition result;
    for (const ulong label_idx : ket_vec) {
        Sequence pattern = context.recall(op_idx, label_idx)->to_seq();  // active recall? Would that stomp on memoize rules too?
        double score = unscaled_simm(seq, pattern);
        if (score > min_score) {
            result.add(label_idx, score);
        }
    }
    result.coeff_sort();
    return result;
}


Superposition op_equal_input(const Sequence& seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return Superposition(); }  // Alternatively, return seq.
    ulong op_idx = parameters[0]->get_operator().get_idx();
    std::vector<ulong> ket_vec = context.relevant_kets(op_idx);
    Superposition result;
    for (const ulong label_idx : ket_vec) {
        Sequence pattern = context.recall(op_idx, label_idx)->to_seq();  // active recall? Would that stomp on memoize rules too?
        if (seq == pattern) {
            result.add(label_idx);
        }
    }
    return result;
}

Superposition op_star_equal_input(const Sequence& seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return Superposition(); }  // Alternatively, return seq.
    ulong op_idx = parameters[0]->get_operator().get_idx();
    std::vector<ulong> ket_vec = context.relevant_kets(op_idx);
    ulong star_idx = ket_map.get_idx("*");
    Superposition result;
    for (const ulong label_idx : ket_vec) {
        Sequence pattern = context.recall(op_idx, label_idx)->to_seq();  // active recall? Would that stomp on memoize rules too?
        if (seq == pattern) {
            result.add(label_idx);
        }
        else if (seq.size() != pattern.size())
        {
            continue;
        }
        else
        {
            bool match = true;
            for (size_t i = 0; i < seq.size(); i++)
            {
                if (pattern.get(i).to_ket().label_idx() == star_idx)
                {
                    continue;
                }
                if (!(seq.get(i) == pattern.get(i)))
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                result.add(label_idx);
            }
        }
    }
    return result;
}


// Wow! A lot of work just to subtract a number!!
Ket op_minus(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (k.size() == 0 || parameters.empty()) { return Ket(); }  // Alternatively, return k.
    long double value = parameters[0]->get_float();
    auto split_idx = k.label_split_idx();
    try
    {
        long double number = std::stold(ket_map.get_str(split_idx.back()));  // Possibly wrap this in a try/catch.
        split_idx.pop_back();
        if (split_idx.empty()) {
            return Ket(float_to_int(number - value, default_decimal_places), k.value());
        }
        else {
            std::string category = ket_map.get_str(split_idx) + ": ";
            return Ket(category + float_to_int(number - value, default_decimal_places), k.value());
        }
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return Ket();  // Return |> or k?
    }
}

Ket op_plus(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (k.size() == 0 || parameters.empty()) { return Ket(); }  // Alternatively, return k.
    long double value = parameters[0]->get_float();
    auto split_idx = k.label_split_idx();
    try
    {
        long double number = std::stold(ket_map.get_str(split_idx.back()));  // Possibly wrap this in a try/catch.
        split_idx.pop_back();
        if (split_idx.empty()) {
            return Ket(float_to_int(number + value, default_decimal_places), k.value());
        }
        else {
            std::string category = ket_map.get_str(split_idx) + ": ";
            return Ket(category + float_to_int(number + value, default_decimal_places), k.value());
        }
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return Ket();  // Return |> or k?
    }
}

Ket op_times_by(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (k.size() == 0 || parameters.empty()) { return Ket(); }  // Alternatively, return k.
    long double value = parameters[0]->get_float();
    auto split_idx = k.label_split_idx();
    try
    {
        long double number = std::stold(ket_map.get_str(split_idx.back()));  // Possibly wrap this in a try/catch.
        split_idx.pop_back();
        if (split_idx.empty()) {
            return Ket(float_to_int(number * value, default_decimal_places), k.value());
        }
        else {
            std::string category = ket_map.get_str(split_idx) + ": ";
            return Ket(category + float_to_int(number * value, default_decimal_places), k.value());
        }
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return Ket();  // Return |> or k?
    }
}

Ket op_divide_by(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (k.size() == 0 || parameters.empty()) { return Ket(); }  // Alternatively, return k.
    long double value = parameters[0]->get_float();
    if (double_eq(value, 0)) { return k; } // prevent divide by zero.
    auto split_idx = k.label_split_idx();
    try
    {
        long double number = std::stold(ket_map.get_str(split_idx.back()));  // Possibly wrap this in a try/catch.
        split_idx.pop_back();
        if (split_idx.empty()) {
            return Ket(float_to_int(number / value, default_decimal_places), k.value());
        }
        else {
            std::string category = ket_map.get_str(split_idx) + ": ";
            return Ket(category + float_to_int(number / value, default_decimal_places), k.value());
        }
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return Ket();  // Return |> or k?
    }
}

Ket op_int_divide_by(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (k.size() == 0 || parameters.empty()) { return Ket(); }  // Alternatively, return k.
    long double value = parameters[0]->get_float();
    if (double_eq(value, 0)) { return k; } // prevent divide by zero.
    auto split_idx = k.label_split_idx();
    try
    {
        long double number = std::stold(ket_map.get_str(split_idx.back()));  // Possibly wrap this in a try/catch.
        split_idx.pop_back();
        if (split_idx.empty()) {
            return Ket(float_to_int((long double)(number / value), default_decimal_places), k.value());
        }
        else {
            std::string category = ket_map.get_str(split_idx) + ": ";
            return Ket(category + float_to_int(number / value, default_decimal_places), k.value());
        }
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return Ket();  // Return |> or k?
    }
}

Ket op_round(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (k.size() == 0 || parameters.empty()) { return Ket(); }  // Alternatively, return k.
    unsigned int value = parameters[0]->get_int();
    if (double_eq(value, 0)) { return k; } // prevent divide by zero.
    auto split_idx = k.label_split_idx();
    try
    {
        long double number = std::stold(ket_map.get_str(split_idx.back()));  // Possibly wrap this in a try/catch.
        split_idx.pop_back();
        if (split_idx.empty()) {
            return Ket(float_to_int(number, value), k.value());
        }
        else {
            std::string category = ket_map.get_str(split_idx) + ": ";
            return Ket(category + float_to_int(number, value), k.value());
        }
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return Ket();  // Return |> or k?
    }
}


Ket op_modulus(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (k.size() == 0 || parameters.empty()) { return Ket(); }  // Alternatively, return k.
    long double value = parameters[0]->get_float();
    auto split_idx = k.label_split_idx();
    try
    {
        long double number = std::stold(ket_map.get_str(split_idx.back()));  // Possibly wrap this in a try/catch.
        split_idx.pop_back();
        long long result = static_cast<long long>(number) % static_cast<long long>(value);
        if (split_idx.empty()) {
            return Ket(float_to_int((long double)result, default_decimal_places), k.value());
        }
        else {
            std::string category = ket_map.get_str(split_idx) + ": ";
            return Ket(category + float_to_int((long double)result, default_decimal_places), k.value());
        }
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return Ket();  // Return |> or k?
    }
}

Ket op_toupper(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (k.size() == 0 || parameters.empty()) { return k; }
    std::string label = k.label();
    for (const auto& elt : parameters) {
        int idx = elt->get_int() - 1;  // to-upper[1] changes case of first char, not the second.
        if (idx < 0 || idx >= label.size()) {
            continue;
        }
        // if (label[idx] >= 'a' && label[idx] <= 'z') {  // assumes ASCII. Is there a better way to do this?
        //     label[idx] = label[idx] - 32;
        // }
        label[idx] = std::toupper(label[idx]);
    }
    return Ket(label, k.value());
}

Ket op_tolower(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (k.size() == 0 || parameters.empty()) { return k; }
    std::string label = k.label();
    for (const auto& elt : parameters) {
        int idx = elt->get_int() - 1;  // to-lower[1] changes case of first char, not the second.
        if (idx < 0 || idx >= label.size()) {
            continue;
        }
        // if (label[idx] >= 'A' && label[idx] <= 'Z') {  // assumes ASCII. Is there a better way to do this?
        //     label[idx] = label[idx] + 32;
        // }
        label[idx] = std::tolower(label[idx]);
    }
    return Ket(label, k.value());
}

Ket toupperket(const Ket k) {
    std::string label = k.label();
    std::transform(label.begin(), label.end(), label.begin(),
        [](unsigned char c) { return std::toupper(c); });
    return Ket(label, k.value());
}

Ket tolowerket(const Ket k) {
    std::string label = k.label();
    std::transform(label.begin(), label.end(), label.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return Ket(label, k.value());
}


Ket table_back_end(const Superposition& sp, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters, bool is_tidy) {
    if (parameters.empty()) { return Ket(""); }

    std::vector<SimpleOperator> operators;
    if (parameters.size() == 2) {
        if (parameters[1]->get_operator().to_string() == "*") {
            SimpleOperator op = parameters[0]->get_operator();
            operators.push_back(op);
            Superposition supported_ops;
            for (const auto& k : sp) {
                Superposition tmp_sp = context.recall("supported-ops", k.label())->to_sp(); // swap to idx version later.
                supported_ops.add(tmp_sp);
            }
            for (const auto& s_op : supported_ops) {
                ulong idx = s_op.label_split_idx()[1];  // Assumes our s_op are in form: |op: some-op>
                SimpleOperator op2(idx);
                operators.push_back(op2);
            }
        }
    }
    if (operators.empty()) {
        for (const auto& elt : parameters) {
            SimpleOperator op = elt->get_operator();
            operators.push_back(op);
        }
    }

    unsigned int width = (unsigned int)(operators.size());
    unsigned int height = (unsigned int)(sp.size());
    std::vector<std::string> header;
    header.reserve(width);
    std::vector<unsigned int> column_widths;
    column_widths.reserve(width);
    std::vector<std::string> table_body;
    table_body.reserve(width * height);

    for (const auto& op : operators) {
        std::string op_label = op.to_string();
        header.push_back(op_label);
        unsigned int column_width = (unsigned int)(op_label.size());
        column_widths.push_back(column_width);  // initial size of columns is the header widths
    }

    for (const auto& k : sp) {
        Sequence seq = k.to_seq();
        unsigned int idx = 0;
        for (const auto& op : operators) {
            std::string str;
            if (idx == 0) {
                if (!is_tidy)
                {
                    str = k.label();
                }
                else
                {
                    str = ket_map.get_str(ket_map.get_headless_idx(k.label_idx())); // Heh! Is there a cleaner way to do this? Does it matter?
                }
            }
            else {
                // str = op.Compile(context, seq).to_string();  // Swap in something better to display in a table than Sequence::to_string().
                str = op.Compile(context, seq).readable_display(is_tidy);
            }
            table_body.push_back(str);
            column_widths[idx] = std::max(column_widths[idx], (unsigned int)str.size());
            idx++;
        }
    }

    unsigned int idx = 0;
    for (const auto column_width : column_widths) {
        std::cout << "+" << std::left << std::setfill('-') << std::setw(column_width + 2) << "-";
    }
    std::cout << "+" << std::endl;
    for (const auto& str : header) {
        std::cout << "| " << std::left << std::setfill(' ') << std::setw(column_widths[idx]) << str << " ";
        idx++;
    }
    std::cout << "|" << std::endl;
    for (const auto column_width : column_widths) {
        std::cout << "+" << std::left << std::setfill('-') << std::setw(column_width + 2) << "-";
    }
    std::cout << "+" << std::endl;

    idx = 0;
    for (const auto& str : table_body) {
        std::cout << "| " << std::left << std::setfill(' ') << std::setw(column_widths[idx]) << str << " ";
        idx++;
        idx %= width;
        if (idx == 0) {
            std::cout << "|" << std::endl;
        }
    }

    for (const auto column_width : column_widths) {
        std::cout << "+" << std::left << std::setfill('-') << std::setw(column_width + 2) << "-";
    }
    std::cout << "+" << std::endl;
    if (is_tidy) { return Ket("tidy table"); }
    return Ket("table");
}

Ket op_table(const Superposition& sp, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters)
{
    return table_back_end(sp, context, parameters, false);
}

Ket op_tidy_table(const Superposition& sp, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters)
{
    return table_back_end(sp, context, parameters, true);
}

Ket op_transpose_table(const Superposition& sp, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return Ket(""); }

    std::vector<SimpleOperator> operators;
    if (parameters.size() == 2) {
        if (parameters[1]->get_operator().to_string() == "*") {
            SimpleOperator op = parameters[0]->get_operator();
            operators.push_back(op);
            Superposition supported_ops;
            for (const auto& k : sp) {
                Superposition tmp_sp = context.recall("supported-ops", k.label())->to_sp(); // swap to idx version later.
                supported_ops.add(tmp_sp);
            }
            for (const auto& s_op : supported_ops) {
                ulong idx = s_op.label_split_idx()[1];  // Assumes our s_op are in form: |op: some-op>
                SimpleOperator op2(idx);
                operators.push_back(op2);
            }
        }
    }
    if (operators.empty()) {
        for (const auto& elt : parameters) {
            SimpleOperator op = elt->get_operator();
            operators.push_back(op);
        }
    }

    unsigned int height = (unsigned int)(operators.size());
    unsigned int width = (unsigned int)(sp.size()) + 1;
    std::vector<std::string> header;
    header.reserve(width);
    std::vector<unsigned int> column_widths;
    column_widths.reserve(width);
    std::vector<std::string> table_body;
    table_body.reserve(width * (height - 1));

    header.push_back(operators[0].to_string());
    column_widths.push_back((unsigned int)(operators[0].to_string().size()));
    for (const auto& k : sp) {
        header.push_back(k.label());
        column_widths.push_back((unsigned int)(k.label().size()));
    }

    unsigned int idx = 0;
    std::string str;
    bool first_pass = true;
    for (const auto& op : operators) {
        if (first_pass) {
            first_pass = false;
            continue;
        }
        else {
            idx = 0;
            table_body.push_back(op.to_string());
            column_widths[0] = std::max(column_widths[0], (unsigned int)op.to_string().size());
            idx++;
            for (const auto& k : sp) {
                Sequence seq = k.to_seq();
                str = op.Compile(context, seq).readable_display();
                table_body.push_back(str);
                column_widths[idx] = std::max(column_widths[idx], (unsigned int)str.size());
                idx++;
            }
        }
    }

    for (const auto column_width : column_widths) {
        std::cout << "+" << std::left << std::setfill('-') << std::setw(column_width + 2) << "-";
    }
    std::cout << "+" << std::endl;
    idx = 0;
    for (const auto& str : header) {
        std::cout << "| " << std::left << std::setfill(' ') << std::setw(column_widths[idx]) << str << " ";
        idx++;
    }
    std::cout << "|" << std::endl;

    idx = 0;
    for (const auto& str : table_body) {
        std::cout << "| " << std::left << std::setfill(' ') << std::setw(column_widths[idx]) << str << " ";
        idx++;
        idx %= width;
        if (idx == 0) {
            std::cout << "|" << std::endl;
        }
    }

    for (const auto column_width : column_widths) {
        std::cout << "+" << std::left << std::setfill('-') << std::setw(column_width + 2) << "-";
    }
    std::cout << "+" << std::endl;

    return Ket("table");
}

Ket op_smerge(const Sequence& seq) {
    std::string s;
    for (const auto& sp : seq) {
        for (const auto& k : sp) {
            s += k.label();
        }
    }
    return Ket(s);
}

Ket op_smerge1(const Sequence& seq, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return op_smerge(seq); }
    std::string merge_str = parameters[0]->get_string();
    std::string s;
    bool first_pass = true;
    for (const auto& sp : seq) {
        for (const auto& k : sp) {
            if (first_pass) {
                s += k.label();
                first_pass = false;
            }
            else {
                s += merge_str + k.label();
            }
        }
    }
    return Ket(s);
}

ulong grid_element(const unsigned int x, const unsigned int y) {
    return ket_map.get_idx("grid: " + std::to_string(x) + ": " + std::to_string(y));
}

ulong grid_element(const std::string& s, const unsigned int x, const unsigned int y) {
    return ket_map.get_idx(s + std::to_string(x) + ": " + std::to_string(y));
}

bool is_in_grid(const int x, const int y, const unsigned int width, const unsigned int height) {
    if (x < 0 || y < 0 || x >= (int)width || y >= (int)height) { return false; }
    return true;
}

Ket op_learn_grid(const Superposition& sp, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.size() < 2) { return Ket(""); }
    unsigned int width = parameters[0]->get_int();
    unsigned int height = parameters[1]->get_int();

    ulong op_idx = ket_map.get_idx("value");
    if (parameters.size() == 3) {
        op_idx = parameters[2]->get_operator().get_idx();
    }
    else if (parameters.size() > 3) {  // later maybe handle more than one operator to zero out?
        return Ket("");
    }
    std::shared_ptr<BaseSequence> zero_seq = std::make_shared<Ket>("0");

    ulong north_idx = ket_map.get_idx("N");
    ulong north_east_idx = ket_map.get_idx("NE");
    ulong east_idx = ket_map.get_idx("E");
    ulong south_east_idx = ket_map.get_idx("SE");
    ulong south_idx = ket_map.get_idx("S");
    ulong south_west_idx = ket_map.get_idx("SW");
    ulong west_idx = ket_map.get_idx("W");
    ulong north_west_idx = ket_map.get_idx("NW");

    for (int y = 0; y < (int)height; y++) {
        for (int x = 0; x < (int)width; x++) {
            ulong element_idx = grid_element(y, x);
            context.learn(op_idx, element_idx, zero_seq);
            if (is_in_grid(x, y - 1, width, height)) {   // I'm confused why is_in_grid() and grid_element() have opposite parameter orders?
                ulong neighbour_idx = grid_element(y - 1, x);
                std::shared_ptr<BaseSequence> neighbour = std::make_shared<Ket>(neighbour_idx);
                context.learn(north_idx, element_idx, neighbour);
            }
            if (is_in_grid(x + 1, y - 1, width, height)) {
                ulong neighbour_idx = grid_element(y - 1, x + 1);
                std::shared_ptr<BaseSequence> neighbour = std::make_shared<Ket>(neighbour_idx);
                context.learn(north_east_idx, element_idx, neighbour);
            }
            if (is_in_grid(x + 1, y, width, height)) {
                ulong neighbour_idx = grid_element(y, x + 1);
                std::shared_ptr<BaseSequence> neighbour = std::make_shared<Ket>(neighbour_idx);
                context.learn(east_idx, element_idx, neighbour);
            }
            if (is_in_grid(x + 1, y + 1, width, height)) {
                ulong neighbour_idx = grid_element(y + 1, x + 1);
                std::shared_ptr<BaseSequence> neighbour = std::make_shared<Ket>(neighbour_idx);
                context.learn(south_east_idx, element_idx, neighbour);
            }
            if (is_in_grid(x, y + 1, width, height)) {
                ulong neighbour_idx = grid_element(y + 1, x);
                std::shared_ptr<BaseSequence> neighbour = std::make_shared<Ket>(neighbour_idx);
                context.learn(south_idx, element_idx, neighbour);
            }
            if (is_in_grid(x - 1, y + 1, width, height)) {
                ulong neighbour_idx = grid_element(y + 1, x - 1);
                std::shared_ptr<BaseSequence> neighbour = std::make_shared<Ket>(neighbour_idx);
                context.learn(south_west_idx, element_idx, neighbour);
            }
            if (is_in_grid(x - 1, y, width, height)) {
                ulong neighbour_idx = grid_element(y, x - 1);
                std::shared_ptr<BaseSequence> neighbour = std::make_shared<Ket>(neighbour_idx);
                context.learn(west_idx, element_idx, neighbour);
            }
            if (is_in_grid(x - 1, y - 1, width, height)) {
                ulong neighbour_idx = grid_element(y - 1, x - 1);
                std::shared_ptr<BaseSequence> neighbour = std::make_shared<Ket>(neighbour_idx);
                context.learn(north_west_idx, element_idx, neighbour);
            }
        }
    }
    return Ket("learn-grid");
}

Ket op_display_grid(const Superposition& sp, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.size() < 2) { return Ket(""); }
    unsigned int width = parameters[0]->get_int();
    unsigned int height = parameters[1]->get_int();

    ulong op_idx = ket_map.get_idx("value");
    std::string empty_char = ".";
    std::string cell_prefix = "grid: ";
    if (parameters.size() >= 3) {
        op_idx = parameters[2]->get_operator().get_idx();
    }
    if (parameters.size() >= 4) {
        empty_char = parameters[3]->get_string();
    }
    if (parameters.size() == 5) {
        cell_prefix = parameters[4]->get_string();
    }
    if (parameters.size() > 5) {
        return Ket("");
    }

    ulong ant_location = context.recall("location", "ant")->to_ket().label_idx();
    std::string the_ant = context.recall("the", "ant")->to_ket().label();
    std::string value_char;

    std::cout << "width:  " << width << "\n";
    std::cout << "height: " << height << "\n\n";
    std::cout << std::left << std::setfill(' ') << std::setw(3) << " ";
    for (int x = 0; x < (int)width; x++) {
        std::cout << std::right << std::setw(4) << x;
    }
    std::cout << "\n\n";
    for (int y = 0; y < (int)height; y++) {
        std::cout << std::left << std::setw(3) << y;
        for (int x = 0; x < (int)width; x++) {
            ulong element_idx = grid_element(cell_prefix, y, x);
            if (element_idx == ant_location) {
                std::cout << std::right << std::setw(4) << the_ant;
            }
            else {
                Ket cell_value = context.recall(op_idx, element_idx)->to_ket();
                value_char = cell_value.label();
                if (value_char == " ") {
                    value_char = float_to_int(cell_value.value(), default_decimal_places);
                }
                else if (value_char == "0") {
                    value_char = empty_char;
                }
                std::cout << std::right << std::setw(4) << value_char;
            }
        }
        std::cout << "\n";
    }
    std::cout << std::endl;  // Flush. Not sure if needed, but should be fine to leave it in.
    return Ket("display-grid");
}


Ket op_is_less_than(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return k; }  // Maybe something different here.
    long double value = parameters[0]->get_float();
    auto k_vec = k.label_split_idx();
    if (k_vec.empty()) { return Ket(); }
    try {
        long double ket_value = std::stold(ket_map.get_str(k_vec.back()));
        if (ket_value < value) {
            return Ket("yes");
        }
        return Ket("no");
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return Ket("");
    }
}

Ket op_is_less_equal_than(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return k; }  // Maybe something different here.
    long double value = parameters[0]->get_float();
    auto k_vec = k.label_split_idx();
    if (k_vec.empty()) { return Ket(); }
    try {
        long double ket_value = std::stold(ket_map.get_str(k_vec.back()));
        if (ket_value <= value) {
            return Ket("yes");
        }
        return Ket("no");
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return Ket("");
    }
}

Ket op_is_equal(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return k; }  // Maybe something different here.
    long double value = parameters[0]->get_float();
    auto k_vec = k.label_split_idx();
    if (k_vec.empty()) { return Ket(); }
    try {
        long double ket_value = std::stold(ket_map.get_str(k_vec.back()));
        if (long_double_eq(ket_value, value)) {
            return Ket("yes");
        }
        return Ket("no");
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return Ket("");
    }
}

Ket op_is_greater_than(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return k; }  // Maybe something different here.
    long double value = parameters[0]->get_float();
    auto k_vec = k.label_split_idx();
    if (k_vec.empty()) { return Ket(); }
    try {
        long double ket_value = std::stold(ket_map.get_str(k_vec.back()));
        if (ket_value > value) {
            return Ket("yes");
        }
        return Ket("no");
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return Ket("");
    }
}

Ket op_is_greater_equal_than(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return k; }  // Maybe something different here.
    long double value = parameters[0]->get_float();
    auto k_vec = k.label_split_idx();
    if (k_vec.empty()) { return Ket(); }
    try {
        long double ket_value = std::stold(ket_map.get_str(k_vec.back()));
        if (ket_value >= value) {
            return Ket("yes");
        }
        return Ket("no");
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return Ket("");
    }
}

Ket op_is_in_range(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.size() < 2) { return k; }  // Maybe something different here.
    long double value1 = parameters[0]->get_float();
    long double value2 = parameters[1]->get_float();
    auto k_vec = k.label_split_idx();
    if (k_vec.empty()) { return Ket(); }
    try {
        long double ket_value = std::stold(ket_map.get_str(k_vec.back()));
        if (value1 <= ket_value && ket_value <= value2) {
            return Ket("yes");
        }
        return Ket("no");
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return Ket("");
    }
}

bool is_prime(const long long p) {  // Just a naive is_prime() function.
    bool is_prime = true;
    if (p == 0 || p == 1) {
        is_prime = false;
    }
    else {
        for (long long i = 2; i <= p / 2; ++i) {
            if (p % i == 0) {
                is_prime = false;
                break;
            }
        }
    }
    return is_prime;
}

Ket op_is_prime(const Ket k) {
    auto k_vec = k.label_split_idx();
    if (k_vec.empty()) { return Ket(""); }
    try {
        long long ket_value = std::stoll(ket_map.get_str(k_vec.back()));  // Would be nice to not have to use try/catch here.
        if (is_prime(ket_value)) {
            return Ket("yes");
        }
        return Ket("no");
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return Ket("");
    }
}

Superposition op_prime_factors(const Ket k) {  // Just a naive prime_factors() function.
    Superposition result;
    auto k_vec = k.label_split_idx();
    if (k_vec.empty()) { return Ket(""); }
    std::string ket_label = ket_map.get_str(k_vec.back());
    k_vec.pop_back();
    std::string category = ket_map.get_str(k_vec);
    if (!category.empty()) {
        category += ": ";
    }
    try {
        long long p = std::stoll(ket_label);  // Would be nice to not have to use try/catch here.
        while (p % 2 == 0) {
            result.add(category + "2");
            p /= 2;
        }
        for (long long i = 3; i <= sqrt(p); i += 2)
        {
            while (p % i == 0)
            {
                result.add(category + std::to_string(i));
                p /= i;
            }
        }
        if (p > 2) {
            result.add(category + std::to_string(p));
        }
        return result;
    }
    catch (const std::invalid_argument& e) {
        (void)e; // To silence C4101 warning.
        return Superposition("");
    }
}

Sequence op_such_that(const Sequence& seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return Sequence(""); }
    SimpleOperator op = parameters[0]->get_operator();
    Sequence result;
    for (const auto& sp : seq) {
        Sequence tmp;
        for (const auto& k : sp) {
            std::string value = op.Compile(context, k.to_seq()).to_ket().label();
            if (value == "yes" || value == "true") {
                tmp.add(k);
            }
        }
        result.append(tmp);
    }
    return result;
}

Sequence op_smap(const Sequence& seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (seq.size() == 0 || parameters.size() < 3) { return Sequence(""); }
    unsigned int min_ngram_size = parameters[0]->get_int();
    unsigned int max_ngram_size = parameters[1]->get_int();
    unsigned int width = (unsigned int)(seq.size());
    min_ngram_size = std::min(min_ngram_size, width);
    max_ngram_size = std::min(max_ngram_size, width);
    if (min_ngram_size <= 0 || max_ngram_size <= 0 || max_ngram_size < min_ngram_size) { return Sequence(""); }
    SimpleOperator op = parameters[2]->get_operator();
    Sequence result;
    Superposition empty("");
    for (int i = 0; i < (int)width; i++) {  // Pad the result sequence with empty superpositions.
        result.append(empty);          // This is needed so that result.set() works.
    }
    ulong the_idx = ket_map.get_idx("the");
    ulong smap_pos_idx = ket_map.get_idx("smap pos");
    for (unsigned int size = min_ngram_size; size <= max_ngram_size; size++) {
        for (unsigned int start = 0; start < width - size + 1; start++) {
            auto start_iter = seq.cbegin() + (size_t)start;
            auto stop_iter = seq.cbegin() + (size_t)(start + size);
            Sequence patch;
            for (auto iter = start_iter; iter != stop_iter; ++iter) {
                patch.append(*iter);
            }
            // context.learn("the", "smap pos", std::to_string(start + size));  // Should we optimise this? Ie, convert "the" and "smap pos" to ulong indices?
            std::shared_ptr<BaseSequence> bSeq = std::make_shared<Ket>(std::to_string(start + size));
            context.learn(the_idx, smap_pos_idx, bSeq);
            Superposition patch_result = op.Compile(context, patch).to_sp();
            Superposition new_patch_result = result.get(start + size - 1);
            new_patch_result.add(patch_result);
            result.set(start + size - 1, new_patch_result);
        }
    }
    return result;
}

// Maybe shift to Function/misc.cpp
// bool is_number(const std::string &str) {  // a quick check if a string is a number or not. NB: not perfect, since invalid numbers will return true.
//     return !str.empty() && str.find_first_not_of("-.0123456789") == std::string::npos;
// }

long double Gaussian1(long double x, long double y, long double sigma) {
    long double ED = std::sqrt((x - y) * (x - y));  // Euclidean distance for a 1D "vector"
    return std::exp(-ED / (2 * sigma * sigma));
}

long double Gaussian2(long double x1, long double x2, long double y1, long double y2, long double sigma) {
    long double ED = std::sqrt((x1 - y1) * (x1 - y1) + (x2 - y2) * (x2 - y2));  // Euclidean distance for a 2D vector
    return std::exp(-ED / (2 * sigma * sigma));
}


Superposition op_Gaussian(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return Superposition(); }

    double sigma = parameters[0]->get_float();
    double dx = 1.0;
    if (parameters.size() == 2) {
        dx = parameters[1]->get_float();
        if (double_eq(dx, 0)) { return Superposition(); }
    }
    auto k_vec = k.label_split_idx();
    std::string categories;
    std::vector<long double> values;
    bool first_pass = true;
    for (const auto idx : k_vec) {
        std::string label = ket_map.get_str(idx);
        if (!is_number(label)) {
            if (first_pass) {
                categories += label + ": ";
            }
            else {
                break;
            }
        }
        else {
            long double value = std::stold(label);
            values.push_back(value);
            first_pass = false;
        }
    }
    if (values.empty()) { return Superposition(); }
    double gauss_width = 9 * sigma * sigma;
    Superposition result;
    if (values.size() == 1) {
        long double x = values[0];
        long double start = std::ceil((x - gauss_width) / dx);
        long double finish = std::floor((x + gauss_width) / dx);
        unsigned int step_count = (unsigned int)(std::floor(finish - start + 1));
        long double y = start * dx;
        for (unsigned int i = 0; i < step_count; i++) {
            long double value = Gaussian1(x, y, sigma);
            result.add(categories + float_to_int(y, default_decimal_places), value * k.value());
            y += dx;
        }
        return result;
    }
    if (values.size() == 2) {
        long double x1 = values[0];
        long double x2 = values[1];
        long double start1 = std::ceil((x1 - gauss_width) / dx);
        long double finish1 = std::floor((x1 + gauss_width) / dx);
        unsigned int step_count1 = (unsigned int)(std::floor(finish1 - start1 + 1));

        long double start2 = std::ceil((x2 - gauss_width) / dx);
        long double finish2 = std::floor((x2 + gauss_width) / dx);
        unsigned int step_count2 = (unsigned int)(std::floor(finish2 - start2 + 1));

        long double y1 = start1 * dx;
        for (unsigned int i = 0; i < step_count1; i++) {
            long double y2 = start2 * dx;
            for (unsigned int j = 0; j < step_count2; j++) {
                long double value = Gaussian2(x1, x2, y1, y2, sigma);
                result.add(categories + float_to_int(y1, default_decimal_places) + ": " + float_to_int(y2, default_decimal_places), value * k.value());
                y2 += dx;
            }
            y1 += dx;
        }
        return result;
    }
    return result;
}

Ket op_find_inverse(const Sequence& seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return Ket(""); }
    for (const auto& param : parameters) {
        ulong idx = param->get_operator().get_idx();
        context.find_inverse(idx);
    }
    return Ket("find-inverse");
}

Ket op_remove_suffix(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {  // Optimise this!!
    if (parameters.empty()) { return k; }
    std::string suffix = parameters[0]->get_string();
    if (suffix.empty()) { return k; }
    size_t suffix_width = suffix.size();
    size_t label_width = k.label().size();
    if (suffix_width > label_width) { return k; }
    std::string label_suffix = k.label().substr(label_width - suffix_width);
    if (label_suffix == suffix) {
        std::string label_front = k.label().substr(0, label_width - suffix_width);
        return Ket(label_front, k.value());
    }
    return k;
}

Ket op_has_suffix(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {  // Optimise this!!
    if (parameters.empty()) { return Ket("no"); }
    std::string suffix = parameters[0]->get_string();
    if (suffix.empty()) { return Ket("no"); }
    if (std::equal(suffix.rbegin(), suffix.rend(), k.label().rbegin())) {
        return Ket("yes");
    }
    return Ket("no");
    /*
    size_t suffix_width = suffix.size();
    size_t label_width = k.label().size();
    if (suffix_width > label_width) { return Ket("no"); }
    std::string label_suffix = k.label().substr(label_width - suffix_width);
    if (label_suffix == suffix) {
        return Ket("yes");
    }
    return Ket("no");
     */
}

Ket op_remove_prefix(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {  // Optimise this!!
    if (parameters.empty()) { return k; }
    std::string prefix = parameters[0]->get_string();
    if (prefix.empty()) { return k; }
    size_t prefix_width = prefix.size();
    size_t label_width = k.label().size();
    if (prefix_width > label_width) { return k; }
    std::string label_prefix = k.label().substr(0, prefix_width);
    if (label_prefix == prefix) {
        std::string label_back = k.label().substr(prefix_width);
        return Ket(label_back, k.value());
    }
    return k;
}

Ket op_has_prefix(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {  // Optimise this!!
    if (parameters.empty()) { return Ket("no"); }
    std::string prefix = parameters[0]->get_string();
    if (prefix.empty()) { return Ket("no"); }
    if (std::equal(prefix.begin(), prefix.end(), k.label().begin())) {
        return Ket("yes");
    }
    return Ket("no");
    /*
    size_t prefix_width = prefix.size();
    size_t label_width = k.label().size();
    if (prefix_width > label_width) { return Ket("no"); }
    std::string label_prefix = k.label().substr(0, prefix_width);
    if (label_prefix == prefix) {
        return Ket("yes");
    }
    return Ket("no");
    */
}

Ket op_to_comma_number(const Ket k) {
    auto k_vec = k.label_split_idx();
    std::string categories;
    long double value = 0;
    for (const auto idx : k_vec) {
        std::string label = ket_map.get_str(idx);
        if (!is_number(label)) {  // maybe should relabel "is-number" to "is-probably-number" ?
            categories += label + ": ";
        }
        else {
            std::string int_label;
            std::string decimal_label;
            size_t decimal_pos = label.find_last_of('.');
            if (decimal_pos == std::string::npos) {
                int_label = label;
            }
            else {
                int_label = label.substr(0, decimal_pos);
                decimal_label = label.substr(decimal_pos);
            }
            int n = (int)int_label.length() - 3;
            while (n > 0) {
                int_label.insert(n, ",");
                n -= 3;
            }
            return Ket(categories + int_label + decimal_label, k.value());
        }
    }
    return k;
}


// if (t1, t2) is a grid-neighbour of (s1,s2) of distance k, return true, else false
bool is_grid_neighbour(int s1, int s2, int t1, int t2, int k) {
    bool is_full_neighbour = (s1 - k <= t1 && t1 <= s1 + k) && (s2 - k <= t2 && t2 <= s2 + k);
    bool is_inner_neighbour = (s1 - k + 1 <= t1 && t1 <= s1 + k - 1) && (s2 - k + 1 <= t2 && t2 <= s2 + k - 1);
    return is_full_neighbour && !is_inner_neighbour;
}

// Is there a smarter way to implement this function?
unsigned int grid_distance(int s1, int s2, int t1, int t2, int max_k) {
    for (int k = 0; k < max_k; k++) {
        if (is_grid_neighbour(s1, s2, t1, t2, k)) { return k; }
    }
    return max_k;
}

// Nope. This idea is dead! It gives terrible results on MNIST.
Superposition digit2sp(const Superposition& sp, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (sp.size() == 0) { return Superposition(""); }
    // std::cout << "sp: " << sp.to_string() << std::endl;
    unsigned int break_from_loop = 10000;  // I have no idea how big this needs to be.
    int max_k = 28;  // In practice, this needs to be larger. For MNIST, somewhere around 28.
    unsigned int min_grid_dist = 1;
    if (parameters.size() == 1) {
        int tmp = parameters[0]->get_int();
        if (tmp > 0) {
            min_grid_dist = tmp;
        }
    }

    std::set<ulong> Q;
    std::map<ulong, unsigned int> dist;
    std::map<ulong, ulong> prev;
    std::map<ulong, bool> is_valid;
    std::map<ulong, std::set<ulong>> nghbrs;
    std::map<std::pair<ulong, ulong>, unsigned int> the_grid_distances;
    std::map<std::pair<ulong, ulong>, unsigned int> the_operator_distances;

    for (const auto& k1 : sp) {
        auto k1_vec = k1.label_split_idx();
        if (k1_vec.size() < 2) {
            continue;
        }
        ulong vertex1 = k1.label_idx();
        int s0 = std::stoi(ket_map.get_str(k1_vec[0]));
        int s1 = std::stoi(ket_map.get_str(k1_vec[1]));
        for (const auto& k2 : sp) {
            auto k2_vec = k2.label_split_idx();
            if (k2_vec.size() < 2) {
                continue;
            }
            ulong vertex2 = k2.label_idx();
            int t0 = std::stoi(ket_map.get_str(k2_vec[0]));
            int t1 = std::stoi(ket_map.get_str(k2_vec[1]));
            if (vertex1 == vertex2) {
                continue;
            }
            unsigned int grid_dist = grid_distance(s0, s1, t0, t1, max_k);
            // std::cout << "(" << s0 << ", " << s1 << ") (" << t0 << ", " << t1 << ") grid-distance: " << grid_dist << std::endl;
            the_grid_distances[std::make_pair(vertex1, vertex2)] = grid_dist;
            if (grid_dist == 1) {  // Add to the neighbours set:
                nghbrs[vertex1].emplace(vertex2);
            }
        }
    }
    /*
    for (const auto &k: sp) {  // print out the neighbours map to check for correctness.
        ulong vertex = k.label_idx();
        std::cout << "vertex: " << k.to_string() << " nghbrs: ";
        for (const auto &v: nghbrs[vertex]) {
            std::cout << ket_map.get_str(v) << ", ";
        }
        std::cout << std::endl;
    }
    */

    for (const auto& k1 : sp) {
        ulong u = k1.label_idx();
        unsigned int loop_count = 0;
        Q.clear();
        prev.clear();
        for (const auto& k2 : sp) {  // populate the the_operator_distances map:
            ulong vertex2 = k2.label_idx();
            Q.emplace(vertex2);
            dist[vertex2] = std::numeric_limits<unsigned int>::max();
            is_valid[vertex2] = true;
        }
        dist[u] = 0;
        while (!Q.empty()) {  // Currently an infinite loop if there are objects in Q that can not be reached from u. I don't yet know how to fix!
            unsigned int min_dist = std::numeric_limits<unsigned int>::max();
            for (const ulong vertex : Q) {
                if (dist[vertex] < min_dist) {
                    u = vertex;
                    min_dist = dist[vertex];
                }
            }
            Q.erase(u);
            if (loop_count >= break_from_loop) {
                is_valid[k1.label_idx()] = false;
                break;
            }
            loop_count++;
            for (const auto& v : nghbrs[u]) {
                if (Q.find(v) != Q.end()) {
                    unsigned int alt = dist[u] + 1;  // all neighbours are 1 step away.
                    if (alt < dist[v]) {
                        dist[v] = alt;
                        prev[v] = u;
                    }
                }
            }
        }
        for (const auto& k2 : sp) {
            ulong v = k2.label_idx();
            unsigned int op_dist = 0;
            if (prev.find(v) != prev.end() || v == k1.label_idx()) {
                while (prev.find(v) != prev.end()) {
                    op_dist++;
                    v = prev[v];
                }
            }
            the_operator_distances[std::make_pair(k1.label_idx(), k2.label_idx())] = op_dist;
            // std::cout << "op_dist: " << k1.to_string() << " " << k2.to_string() << ": " << op_dist << std::endl;
        }
    }
    // Finally, calculate the result:
    // version 1, gives terrible results!
    /*
    Superposition result;
    for (const auto &k1: sp) {
        ulong vertex1 = k1.label_idx();
        for (const auto &k2: sp) {
            ulong vertex2 = k2.label_idx();
            if (vertex1 != vertex2) {
                unsigned int the_grid_dist = the_grid_distances[std::make_pair(vertex1, vertex2)];
                unsigned int the_op_dist = the_operator_distances[std::make_pair(vertex1, vertex2)];
                unsigned int dist_delta = the_op_dist - the_grid_dist;  // NB: the operator distance should always be longer than the grid distance!
                if (the_grid_dist >= min_grid_dist) {
                    result.add(std::to_string(dist_delta));
                }
            }
        }
    }
    */
    // version 2, gives better results:
    unsigned int max_int = std::numeric_limits<unsigned int>::max();
    Superposition result;
    for (const auto& k1 : sp) {
        std::string label = k1.label() + ": ";
        ulong vertex1 = k1.label_idx();
        if (!is_valid[vertex1]) {
            result.add(k1);
            continue;
        }
        for (const auto& k2 : sp) {
            ulong vertex2 = k2.label_idx();
            if (vertex1 != vertex2) {
                unsigned int the_grid_dist = the_grid_distances[std::make_pair(vertex1, vertex2)];
                unsigned int the_op_dist = the_operator_distances[std::make_pair(vertex1, vertex2)];
                unsigned int dist_delta = the_op_dist - the_grid_dist;  // NB: the operator distance should always be longer than the grid distance!
                if (the_grid_dist >= min_grid_dist) {
                    if (dist_delta < 500) {
                        result.add(label + std::to_string(dist_delta), k1.value());
                    }
                    else {
                        result.add(k1);
                    }
                }
            }
        }
    }
    return result;
}

Ket op_unlearn(const Superposition& sp, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty() || sp.size() == 0) { return Ket(); }
    ulong star_idx = ket_map.get_idx("*");
    if (parameters.size() == 1 && (parameters[0]->get_operator().get_idx() == star_idx)) {  // Unlearn everything.
        for (const auto& k : sp) {
            ulong label_idx = k.label_idx();
            std::vector<ulong> supported_ops = context.supported_ops(label_idx);
            for (ulong op_idx : supported_ops) {
                context.unlearn(op_idx, label_idx);
            }
        }
    }
    else {
        for (const auto& param : parameters) {
            ulong op_idx = param->get_operator().get_idx();
            for (const auto& k : sp) {
                ulong label_idx = k.label_idx();
                context.unlearn(op_idx, label_idx);
            }
        }
    }
    return Ket("unlearned");
}

/*
Ket op_scompress_v1(const Sequence &seq, ContextList &context, const std::vector<std::shared_ptr<CompoundConstant> > &parameters) {
    if (parameters.size() != 2) { return Ket(); }
    ulong source_op = parameters[0]->get_operator().get_idx(); // Do we need to check our operators are valid?
    ulong dest_op = parameters[1]->get_operator().get_idx();
    std::vector<ulong> source_kets = context.relevant_kets(source_op);
    if (source_kets.empty()) { return Ket(); }
    // std::unordered_map<unsigned int, Sequence> source_patterns;  // Should we use unordered_map or vector?
    std::unordered_map<unsigned int, std::vector<Superposition>> source_patterns;
    std::unordered_map<unsigned int, ulong> source_pattern_labels;
    std::unordered_map<unsigned int, size_t> source_pattern_lengths;
    size_t max_seq_len = 0;
    unsigned int source_pattern_pos = 0;
    for (ulong idx: source_kets) {
        Sequence pattern = context.recall(source_op, idx)->to_seq();
        if (pattern.size() > 0) {
            max_seq_len = std::max(pattern.size(), max_seq_len);
            source_pattern_lengths[source_pattern_pos] = pattern.size();
            source_pattern_labels[source_pattern_pos] = idx;
            std::vector<Superposition> vector_pattern;
            vector_pattern.insert(vector_pattern.cbegin(), pattern.cbegin(), pattern.cend());
            source_patterns[source_pattern_pos] = vector_pattern;
            source_pattern_pos++;
        }
    }
    if (max_seq_len == 0) { return Ket(); }
    std::cout << "scompress: max_seq_len: " << max_seq_len << std::endl;
    unsigned int compress_count = 0;
    unsigned int working_ngram_len = max_seq_len;
    // unsigned int working_ngram_len = 4;  // Just so we can test the ngram code.
    while (working_ngram_len > 1) {
        std::vector<std::vector<Superposition>> working_patterns;
        std::unordered_map<unsigned int, unsigned int> working_patterns_count;
        unsigned int max_pattern_count = 0;
        unsigned int max_pattern_count_pos = 0;
        for (const auto &iter: source_pattern_lengths) {
            if (iter.second < working_ngram_len) { continue; }
            std::vector<Superposition> source_pattern = source_patterns[iter.first];
            for (unsigned int start_idx = 0; iter.second >= working_ngram_len + start_idx; start_idx++) {
                std::vector<Superposition> vector_pattern;
                vector_pattern.insert(vector_pattern.cbegin(), source_pattern.cbegin() + start_idx,
                                      source_pattern.cbegin() + start_idx + working_ngram_len);
                for (const auto &sp: vector_pattern) {
                    std::cout << sp.to_string() << " . ";
                }
                std::cout << std::endl;
                unsigned int pos = 0;
                bool match = false;
                for (const auto &working_pattern: working_patterns) {
                    if (working_pattern ==
                        vector_pattern) {  // Maybe later we could use simm() here for fuzzy matching?
                        std::cout << "Found duplicate!\n";
                        working_patterns_count[pos]++;
                        if (working_patterns_count[pos] > max_pattern_count) {
                            max_pattern_count = working_patterns_count[pos];
                            max_pattern_count_pos = pos;
                        }
                        match = true;
                        break;
                    }
                    pos++;
                }
                if (!match) {
                    working_patterns.push_back(vector_pattern);
                    working_patterns_count[pos] = 1;
                    pos++;
                }
            }
        }
        if (max_pattern_count < 2) { working_ngram_len--; continue; }
        unsigned int pos = 0;
        std::cout << std::endl;
        std::cout << "Working patterns:" << std::endl;
        for (const auto &pattern: working_patterns) {
            for (const auto &sp: pattern) {
                std::cout << sp.to_string() << " . ";
            }
            std::cout << working_patterns_count[pos] << std::endl;
            pos++;
        }
        std::vector<Superposition> best_pattern = working_patterns[max_pattern_count_pos];
        Sequence best_matching_pattern(best_pattern);
        std::cout << "max_pattern_count: " << max_pattern_count << std::endl;
        std::cout << "max_pattern_count_pos: " << max_pattern_count_pos << std::endl;
        std::cout << "best_matching_pattern: " << best_matching_pattern.to_string() << std::endl;
        ulong ket_label_idx = ket_map.get_idx("scompress: " + std::to_string(compress_count));
        Superposition ket_label_sp(ket_label_idx);
        std::unordered_map<unsigned int, std::vector<Superposition>> new_source_patterns;  // I'm starting to think these should be vectors not unordered_maps.
        std::unordered_map<unsigned int, ulong> new_source_pattern_labels;
        std::unordered_map<unsigned int, size_t> new_source_pattern_lengths;
        pos = 0;
        for (const auto &iter: source_pattern_lengths) {
            // if (iter.second < working_ngram_len) { pos++; continue; }  // I don't know if we need pos++ here or not!
            std::vector<Superposition> final_pattern;
            std::vector<Superposition> source_pattern = source_patterns[iter.first];
            ulong source_label_idx = source_pattern_labels[iter.first];
            if (iter.second < working_ngram_len) {
                new_source_patterns[pos] = source_pattern;
                new_source_pattern_labels[pos] = source_label_idx;
                new_source_pattern_lengths[pos] = source_pattern.size();
                pos++;
                continue;
            }
            unsigned int final_idx = 0;
            for (unsigned int start_idx = 0; iter.second >= working_ngram_len + start_idx; start_idx++) {
                std::vector<Superposition> vector_pattern;
                vector_pattern.insert(vector_pattern.cbegin(), source_pattern.cbegin() + start_idx,
                                      source_pattern.cbegin() + start_idx + working_ngram_len);
                bool match = false;
                if (best_pattern == vector_pattern) {
                    std::cout << "source_label: " << ket_map.get_str(source_label_idx) << ", start_idx: " << start_idx
                              << std::endl;
                    final_pattern.push_back(ket_label_sp);
                    start_idx += working_ngram_len - 1;
                    match = true;
                }
                if (!match) {
                    final_pattern.push_back(source_pattern[start_idx]);
                }
                final_idx = start_idx;
            }
            final_idx++;
            for (; final_idx < iter.second; final_idx++) {
                final_pattern.push_back(source_pattern[final_idx]);
            }
            Sequence tmp_pattern(final_pattern);
            std::cout << "final_pattern: " << tmp_pattern.to_string() << ", source_label: " << ket_map.get_str(source_label_idx) << std::endl;
            new_source_patterns[pos] = final_pattern;
            new_source_pattern_labels[pos] = source_label_idx;
            new_source_pattern_lengths[pos] = final_pattern.size();
            pos++;
        }
        new_source_patterns[pos] = best_pattern;
        new_source_pattern_labels[pos] = ket_label_idx;
        new_source_pattern_lengths[pos] = best_pattern.size();
        source_patterns = std::move(new_source_patterns);
        source_pattern_labels = std::move(new_source_pattern_labels);
        source_pattern_lengths = std::move(new_source_pattern_lengths);
        compress_count++;
    }
    // Now learn the final patterns:
    for (const auto &iter: source_patterns) {
        std::shared_ptr<BaseSequence> bSeq = std::make_shared<Sequence>(iter.second);
        context.learn(dest_op, source_pattern_labels[iter.first], bSeq);
    }
    ulong star_idx = ket_map.get_idx("*");
    std::shared_ptr<BaseSequence> bSeq = std::make_shared<SelfKet>();
    context.stored_learn(dest_op, star_idx, bSeq);
    return Ket("scompress");
}
*/

Ket op_scompress(const Sequence& seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.size() < 2) { return Ket(); }
    ulong source_op = parameters[0]->get_operator().get_idx(); // Do we need to check our operators are valid?
    ulong dest_op = parameters[1]->get_operator().get_idx();
    std::vector<ulong> source_kets = context.relevant_kets(source_op);
    if (source_kets.empty()) { return Ket(); }

    std::string prefix;
    if (parameters.size() >= 3) {
        prefix = parameters[2]->get_string();
    }
    else {
        prefix = "scompress: ";          // Change this as desired.
    }
    bool verbose = false;                // Switch on/off verbose printing of processing.

    // std::vector<Sequence> source_patterns;  // Should we use vectors of superpositions, or Sequences?
    std::vector<std::vector<Superposition>> source_patterns;
    std::vector<ulong> source_pattern_labels;
    std::vector<size_t> source_pattern_lengths;
    size_t max_seq_len = 0;
    for (ulong idx : source_kets) {
        Sequence pattern = context.recall(source_op, idx)->to_seq();
        if (pattern.size() > 0) {
            max_seq_len = std::max(pattern.size(), max_seq_len);
            source_pattern_lengths.push_back(pattern.size());
            source_pattern_labels.push_back(idx);
            std::vector<Superposition> vector_pattern;
            vector_pattern.insert(vector_pattern.cbegin(), pattern.cbegin(), pattern.cend());
            source_patterns.push_back(vector_pattern);
        }
    }
    if (max_seq_len == 0) { return Ket(); }
    if (verbose) {
        std::cout << "scompress: max_seq_len: " << max_seq_len << std::endl;
    }

    unsigned int compress_count = 0;
    unsigned int working_ngram_len = (unsigned int)max_seq_len;  // Unsigned int vs size_t .... 
    unsigned int min_ngram_len = 2;
    if (parameters.size() == 5) {
        min_ngram_len = std::min((unsigned int)max_seq_len, (unsigned int)(parameters[3]->get_int()));
        working_ngram_len = std::min(working_ngram_len, (unsigned int)(parameters[4]->get_int()));
        // std::cout << "min_ngram_len: " << min_ngram_len << "\n";
        // std::cout << "working_ngram_len: " << working_ngram_len << "\n";
    }

    while (working_ngram_len >= min_ngram_len) {

        std::vector<std::vector<Superposition>> working_patterns;
        std::unordered_map<unsigned int, unsigned int> working_patterns_count;
        unsigned int max_pattern_count = 0;
        unsigned int max_pattern_count_pos = 0;

        unsigned int pos = 0;
        for (const auto len : source_pattern_lengths) {
            if (len < working_ngram_len) { pos++; continue; }
            std::vector<Superposition> source_pattern(source_patterns[pos]);
            for (unsigned int start_idx = 0; len >= working_ngram_len + start_idx; start_idx++) {
                std::vector<Superposition> vector_pattern;  // Is there a better way than building all these ngrams each time?
                vector_pattern.insert(vector_pattern.cbegin(), source_pattern.cbegin() + start_idx,
                    source_pattern.cbegin() + start_idx + working_ngram_len);
                if (verbose) {
                    for (const auto& sp : vector_pattern) {
                        std::cout << sp.to_string() << " . ";
                    }
                    std::cout << std::endl;
                }
                unsigned int pos2 = 0;
                bool match = false;
                for (const auto& working_pattern : working_patterns) {
                    if (working_pattern == vector_pattern) {  // Maybe later we could use simm() here for fuzzy matching?
                        if (verbose) {
                            std::cout << "Found duplicate!\n";
                        }
                        working_patterns_count[pos2]++;
                        if (working_patterns_count[pos2] > max_pattern_count) {
                            max_pattern_count = working_patterns_count[pos2];
                            max_pattern_count_pos = pos2;
                        }
                        match = true;
                        break;
                    }
                    pos2++;
                }
                if (!match) {
                    working_patterns.push_back(std::move(vector_pattern));
                    working_patterns_count[pos2] = 1;
                    pos2++;
                }
            }
            pos++;
        }
        if (max_pattern_count < 2) { working_ngram_len--; continue; }
        std::vector<Superposition> best_pattern(working_patterns[max_pattern_count_pos]);
        if (verbose) {
            pos = 0;
            std::cout << std::endl;
            std::cout << "Working patterns:" << std::endl;
            for (const auto& pattern : working_patterns) {
                for (const auto& sp : pattern) {
                    std::cout << sp.to_string() << " . ";
                }
                std::cout << working_patterns_count[pos] << std::endl;
                pos++;
            }
            Sequence best_matching_pattern(best_pattern);
            std::cout << "max_pattern_count: " << max_pattern_count << std::endl;
            std::cout << "max_pattern_count_pos: " << max_pattern_count_pos << std::endl;
            std::cout << "best_matching_pattern: " << best_matching_pattern.to_string() << std::endl;
        }

        ulong ket_label_idx = ket_map.get_idx(prefix + std::to_string(compress_count));
        Superposition ket_label_sp(ket_label_idx);

        std::vector<std::vector<Superposition>> new_source_patterns;
        std::vector<ulong> new_source_pattern_labels;
        std::vector<size_t> new_source_pattern_lengths;

        pos = 0;
        for (const auto len : source_pattern_lengths) {
            std::vector<Superposition> final_pattern;
            std::vector<Superposition> source_pattern(source_patterns[pos]);
            ulong source_label_idx = source_pattern_labels[pos];
            if (len < working_ngram_len) {
                new_source_pattern_lengths.push_back(source_pattern.size());
                new_source_patterns.push_back(std::move(source_pattern));
                new_source_pattern_labels.push_back(source_label_idx);
                pos++;
                continue;
            }
            unsigned int final_idx = 0;
            for (unsigned int start_idx = 0; len >= working_ngram_len + start_idx; start_idx++) {
                // std::vector<Superposition> vector_pattern;   // Is there a better way than building all these ngrams each time?
                // vector_pattern.insert(vector_pattern.cbegin(), source_pattern.cbegin() + start_idx,
                //                       source_pattern.cbegin() + start_idx + working_ngram_len);
                bool match = false;
                // if (best_pattern == vector_pattern) {
                if (std::equal(best_pattern.cbegin(), best_pattern.cend(), source_pattern.cbegin() + start_idx)) { // cbegin() and cend() or just begin() and end()?
                    if (verbose) {
                        std::cout << "source_label: " << ket_map.get_str(source_label_idx) << ", start_idx: " << start_idx << std::endl;
                    }
                    final_pattern.push_back(ket_label_sp);
                    start_idx += working_ngram_len - 1;
                    match = true;
                }
                if (!match) {
                    final_pattern.push_back(source_pattern[start_idx]);
                }
                final_idx = start_idx;
            }
            final_idx++;
            for (; final_idx < len; final_idx++) {
                final_pattern.push_back(source_pattern[final_idx]);
            }
            new_source_pattern_lengths.push_back(final_pattern.size());
            new_source_patterns.push_back(std::move(final_pattern));
            new_source_pattern_labels.push_back(source_label_idx);
            pos++;
        }
        new_source_patterns.push_back(best_pattern);
        new_source_pattern_labels.push_back(ket_label_idx);
        new_source_pattern_lengths.push_back(best_pattern.size());

        source_patterns = std::move(new_source_patterns);
        source_pattern_labels = std::move(new_source_pattern_labels);
        source_pattern_lengths = std::move(new_source_pattern_lengths);
        compress_count++;
    }

    // Now learn the final patterns:
    unsigned int pos = 0;
    for (const auto& pattern : source_patterns) {
        std::shared_ptr<BaseSequence> bSeq = std::make_shared<Sequence>(pattern);
        context.learn(dest_op, source_pattern_labels[pos], bSeq);
        pos++;
    }
    ulong star_idx = ket_map.get_idx("*");
    std::shared_ptr<BaseSequence> bSeq = std::make_shared<SelfKet>();
    context.stored_learn(dest_op, star_idx, bSeq);
    return Ket("scompress");
}

Superposition starts_with(const Ket k, ContextList& context) {
    ulong star_idx = ket_map.get_idx("*");
    std::vector<ulong> rel_ket_vec = context.relevant_kets(star_idx);
    std::string starts_with_text = k.label();
    Superposition result;
    for (const ulong idx : rel_ket_vec) {
        std::string label = ket_map.get_str(idx);
        if (std::equal(starts_with_text.begin(), starts_with_text.end(), label.begin())) {
            result.add(idx);
        }
    }
    return result;
}

Sequence op_inherit(const Sequence& seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    Sequence result;
    if (parameters.size() < 2) { return result; }
    SimpleOperator parent_type = parameters[0]->get_operator();
    SimpleOperator op = parameters[1]->get_operator();
    ulong empty_ket_idx = ket_map.get_idx("");
    ulong parent_type_idx = parent_type.get_idx();
    ulong op_idx = op.get_idx();
    std::vector<ulong> parent_list;
    for (const auto& sp : seq) {
        Sequence tmp_seq;
        for (const auto& k : sp) {
            Sequence tmp_result;
            ulong current_ket_idx = k.label_idx();
            parent_list.push_back(current_ket_idx);
            bool has_parent = true;
            while (has_parent) {
                ulong next_ket_idx = context.recall(parent_type_idx, current_ket_idx)->to_ket().label_idx();  // Maybe use context.recall_type() here.
                if (next_ket_idx == empty_ket_idx) {
                    has_parent = false;
                }
                else {
                    parent_list.push_back(next_ket_idx);
                    current_ket_idx = next_ket_idx;
                }
            }
            for (auto iter = parent_list.rbegin(); iter != parent_list.rend(); ++iter) {
                unsigned int result_type = context.recall_type(op_idx, *iter);
                if (result_type == RULENORMAL) {  // Maybe later permit dynamic rules too, so RULESTORED and RULEMEMOIZE.
                    tmp_result = context.recall(op_idx, *iter)->to_seq();
                }
            }
            tmp_result.multiply(k.value());
            tmp_seq.add(tmp_result);
            parent_list.clear();
        }
        result.append(tmp_seq);
    }
    return result;
}

Sequence op_inherit_path(const Sequence& seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    Sequence result;
    if (parameters.empty()) { return result; }
    SimpleOperator parent_type = parameters[0]->get_operator();
    ulong empty_ket_idx = ket_map.get_idx("");
    ulong parent_type_idx = parent_type.get_idx();
    for (const auto& sp : seq) {
        Sequence tmp_seq;
        for (const auto& k : sp) {
            ulong current_ket_idx = k.label_idx();
            std::string inherit_path = k.label();
            bool has_parent = true;
            while (has_parent) {
                ulong next_ket_idx = context.recall(parent_type_idx, current_ket_idx)->to_ket().label_idx();  // Maybe use context.recall_type() here.
                if (next_ket_idx == empty_ket_idx) {
                    has_parent = false;
                }
                else {
                    inherit_path = ket_map.get_str(next_ket_idx) + ": " + inherit_path;
                    current_ket_idx = next_ket_idx;
                }
            }
            Ket tmp_result(inherit_path, k.value());
            tmp_seq.add(tmp_result);
        }
        result.append(tmp_seq);
    }
    return result;
}

Sequence op_sprint(const Sequence& seq) {
    std::cout << seq.to_string() << "\n";
    return seq;
}

Sequence op_sprint1(const Sequence& seq, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) {
        std::cout << seq.to_string() << "\n";
    }
    else if (parameters.size() == 1) {
        std::cout << parameters[0]->get_string() << seq.to_string() << "\n";
    }
    else if (parameters.size() == 2) {
        std::cout << parameters[0]->get_string() << seq.to_string() << parameters[1]->get_string() << "\n";
    }
    return seq;
}

Sequence op_compile(const Sequence& seq, ContextList& context) {
    if (seq.size() < 3 || seq.size() > 6) { return Sequence(""); }
    auto op_split_idx = seq.get(0).to_ket().label_split_idx();
    if (op_split_idx.size() < 2 || op_split_idx[0] != ket_map.get_idx("op")) { return Sequence(""); }
    ulong op_idx = op_split_idx[1];
    Sequence input_seq = seq.get(1).to_seq();
    std::vector<std::shared_ptr<BaseSequence>> params;
    for (auto iter = seq.cbegin() + 2; iter < seq.cend(); ++iter) {
        std::shared_ptr<BaseSequence> tmp_BSeq = std::make_shared<Superposition>(*iter);  // Should it be Superposition, or Sequence?
        params.push_back(tmp_BSeq);
    }
    FunctionOperator fn(op_idx, params);
    return fn.Compile(context, input_seq);
}

Ket op_hash(const Ket k, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return k; }
    unsigned int hash_size = parameters[0]->get_int();
    std::hash<std::string> str_hash;
    size_t ket_hash = str_hash(k.label());
    size_t new_ket_hash = ket_hash % (static_cast<size_t>(1) << hash_size);
    return Ket(std::to_string(new_ket_hash), k.value());
}

Sequence op_common(const Sequence& seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty() || (seq.size() == 0)) { return seq; }
    SimpleOperator op = parameters[0]->get_operator();

    Sequence result, empty;
    for (const auto& sp : seq) {
        if (sp.size() == 0) {
            continue;
        }
        Sequence r = op.Compile(context, sp.get(0).to_seq());
        bool first_pass = true;
        for (const auto& k : sp) {
            if (first_pass) {
                first_pass = false;
                continue;
            }
            Sequence tmp_seq = op.Compile(context, k.to_seq());
            r = op_intersection2(empty, r, tmp_seq);
        }
        result.append(r);
    }
    return result;
}

Sequence op_compound_union(const Sequence& seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty() || (seq.size() == 0)) { return seq; }
    SimpleOperator op = parameters[0]->get_operator();

    Sequence result, empty;
    for (const auto& sp : seq) {
        if (sp.size() == 0) {
            continue;
        }
        Sequence r = op.Compile(context, sp.get(0).to_seq());
        bool first_pass = true;
        for (const auto& k : sp) {
            if (first_pass) {
                first_pass = false;
                continue;
            }
            Sequence tmp_seq = op.Compile(context, k.to_seq());
            r = op_union2(empty, r, tmp_seq);
        }
        result.append(r);
    }
    return result;
}

Sequence op_compound_sum(const Sequence& seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty() || (seq.size() == 0)) { return seq; }
    SimpleOperator op = parameters[0]->get_operator();

    Sequence result, empty;
    for (const auto& sp : seq) {
        if (sp.size() == 0) {
            continue;
        }
        Sequence r = op.Compile(context, sp.get(0).to_seq());
        bool first_pass = true;
        for (const auto& k : sp) {
            if (first_pass) {
                first_pass = false;
                continue;
            }
            Sequence tmp_seq = op.Compile(context, k.to_seq());
            r = op_sum2(empty, r, tmp_seq);
        }
        result.append(r);
    }
    return result;
}

Sequence op_spike_merge(const Sequence& seq, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {  // Not 100% sure it is correct. There might be edge cases where it is wrong.
    if (parameters.empty()) { return seq; }
    unsigned int time_width = parameters[0]->get_int();
    Sequence result;
    unsigned int k = 0;
    Superposition sp_bucket;
    for (const auto& sp : seq) {
        if (k < time_width) {
            sp_bucket.add(sp);
            k++;
        }
        else {
            result.append(sp_bucket);
            sp_bucket = sp;
            k = 1;
        }
    }
    result.append(sp_bucket);
    return result;
}

Sequence op_random(const Sequence& seq, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.size() < 2) { return seq; }
    double mu = parameters[0]->get_float();
    double sigma = parameters[1]->get_float();
    unsigned int seed = (unsigned int)(std::chrono::system_clock::now().time_since_epoch().count());
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(mu, sigma);
    Sequence result;
    for (const auto& sp : seq) {
        Superposition tmp_sp;
        for (const auto& k : sp) {
            double rand_value = distribution(generator);
            tmp_sp.add(k.label_idx(), k.value() * rand_value);
        }
        result.append(tmp_sp);
    }
    return result;
}

Sequence op_sleep_ms(const Sequence& seq, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.empty()) { return seq; }
    int sleep_for = parameters[0]->get_int();
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_for));
    return seq;
}

Ket op_save_as_dot(const Superposition& sp, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters) {
    if (parameters.size() < 2 || sp.size() == 0) { return Ket(); }
    std::string filename = parameters[0]->get_string();
    ulong star_idx = ket_map.get_idx("*");
    std::set<ulong> operators;
    if (parameters.size() == 2 && (parameters[1]->get_operator().get_idx() == star_idx)) {  // save everything.
        for (const auto& k : sp) {
            ulong label_idx = k.label_idx();
            std::vector<ulong> supported_ops = context.supported_ops(label_idx);
            operators.insert(std::begin(supported_ops), std::end(supported_ops));
        }
    }
    else {
        bool first_pass = true;
        for (const auto& param : parameters) {
            if (first_pass) {
                first_pass = false;
                continue;
            }
            ulong op_idx = param->get_operator().get_idx();
            operators.insert(op_idx);
        }
    }
    std::string dot_file = "digraph G {\n  node [ shape=Mrecord ]\n";
    unsigned int cluster_idx = 0;
    unsigned int node_idx = 0;
    std::map<std::string, unsigned int> node_label_idx_map;
    for (ulong op_idx : operators) {
        std::string op_str = ket_map.get_str(op_idx);
        for (const auto& k : sp) {
            if (node_label_idx_map.find(k.label()) == node_label_idx_map.end()) {
                node_idx++;
                node_label_idx_map[k.label()] = node_idx;
                dot_file += "  " + std::to_string(node_idx) + " [ label=\"" + k.label() + "\" ]\n";
            }
            ulong label_idx = k.label_idx();
            Sequence RHS = context.recall(op_idx, label_idx)->to_seq();
            if (RHS.size() <= 1) {
                for (const auto& k2 : RHS.to_sp()) {
                    if (node_label_idx_map.find(k2.label()) == node_label_idx_map.end()) {
                        node_idx++;
                        node_label_idx_map[k2.label()] = node_idx;
                        dot_file += "  " + std::to_string(node_idx) + " [ label=\"" + k2.label() + "\" ]\n";
                    }
                    dot_file += "  " + std::to_string(node_label_idx_map[k.label()]) + " -> " + std::to_string(node_label_idx_map[k2.label()]) + " [ label=\"" + op_str + "\" ]\n";
                }
            }
            else {
                dot_file += "\n  subgraph cluster_" + std::to_string(cluster_idx) + " {\n  rankdir=\"LR\"\n  ranksep=\"0.05\"\n";
                cluster_idx++;
                std::string first_element;
                unsigned int current_node_idx = node_idx;
                for (const auto& sp2 : RHS) {
                    std::string current_element = sp2.readable_display();
                    node_idx++;
                    dot_file += "  " + std::to_string(node_idx) + " [ label=\"" + current_element + "\" ]\n";
                }
                node_idx = current_node_idx;
                unsigned int first_element_idx = current_node_idx;
                bool first_pass = true;
                for (const auto& sp2 : RHS) {
                    node_idx++;
                    if (first_pass) {
                        first_pass = false;
                        first_element_idx = node_idx;
                        dot_file += "  " + std::to_string(first_element_idx);
                    }
                    else {
                        dot_file += " -> " + std::to_string(node_idx);
                    }
                }
                dot_file += " [ arrowhead=dot ]\n  }\n  " + std::to_string(node_label_idx_map[k.label()]) + " -> " + std::to_string(first_element_idx) +
                    "  [ label=\"" + op_str + "\" ] \n";
            }
        }
    }
    dot_file += "}\n";
    std::string cleaned_filename = std::filesystem::path(filename).filename().string();  // Hopefully this reduces the chance of a security risk from saving files.
    std::cout << "filename: " << cleaned_filename << "\n";  // Probably comment out these two cout lines later, when finished with testing.
    std::cout << dot_file;
    std::ofstream myfile;
    myfile.open(cleaned_filename);
    if (myfile.is_open()) {  // Is this a security risk??
        myfile << dot_file;
        myfile.close();
        return Ket("saved dot file");
    }
    else {
        std::cout << "Unable to open file: " << cleaned_filename << std::endl;
        return Ket("failed to save dot file");
    }
    return Ket("We shouldn't be here in save-as-dot.");
}

std::string context_to_dot(ContextList& context)  // Need to test it is correct!
{
    std::set<ulong> operators;
    ulong star_idx = ket_map.get_idx("*");
    std::vector<ulong> known_kets = context.relevant_kets(star_idx);
    for (ulong idx : known_kets)
    {
        std::vector<ulong> supported_ops = context.supported_ops(idx);
        operators.insert(std::begin(supported_ops), std::end(supported_ops));
    }
    // std::string dot_file = "digraph G {\n  node [ shape=Mrecord ]\n";
    std::string dot_file = "digraph G {\n";
    dot_file += "  labelloc=\"t\";\n";
    // dot_file += "  label=\"" + context.get_context_name() + "\";\n";
    dot_file += "  label=<<font point-size=\"30\"><u>" + context.get_context_name() + "</u></font>>;\n";
    dot_file += "  node [ shape=Mrecord ]\n";
    unsigned int cluster_idx = 0;
    unsigned int node_idx = 0;
    std::map<std::string, unsigned int> node_label_idx_map;
    for (ulong op_idx : operators) {
        std::string op_str = ket_map.get_str(op_idx);
        for (ulong ket_idx : known_kets) {
            std::string k_label = ket_map.get_str(ket_idx);
            if (node_label_idx_map.find(k_label) == node_label_idx_map.end()) {
                node_idx++;
                node_label_idx_map[k_label] = node_idx;
                dot_file += "  " + std::to_string(node_idx) + " [ label=\"" + k_label + "\" ]\n";
            }
            unsigned int rule_type = context.recall_type(op_idx, ket_idx);
            if (rule_type == RULESTORED)  // Handle stored rules branch:
            {
                std::string stored_RHS = context.recall(op_idx, ket_idx)->to_string();
                string_replace_all(stored_RHS, "|", "\\|");
                string_replace_all(stored_RHS, ">", "&gt;");
                // string_replace_all(stored_RHS, "\n", "\\n");
                string_replace_all(stored_RHS, "\n", "\\l");
                string_replace_all(stored_RHS, "\"", "\\\"");
                if (node_label_idx_map.find(stored_RHS) == node_label_idx_map.end())
                {
                    node_idx++;
                    node_label_idx_map[stored_RHS] = node_idx;
                    dot_file += "  " + std::to_string(node_idx) + " [ shape=box label=\"" + stored_RHS + "\" ]\n";
                }
                dot_file += "  " + std::to_string(node_label_idx_map[k_label]) + " -> " + std::to_string(node_label_idx_map[stored_RHS]) + " [ arrowhead=box, label=\"" + op_str + "\" ]\n";
            }
            if (rule_type == RULEMEMOIZE)  // Handle memoizing rules branch:
            {
                std::string stored_RHS = context.recall(op_idx, ket_idx)->to_string();
                string_replace_all(stored_RHS, "|", "\\|");
                // string_replace_all(stored_RHS, "|", "&pipe;");
                string_replace_all(stored_RHS, ">", "&gt;");
                // string_replace_all(stored_RHS, "\n", "\\n");
                string_replace_all(stored_RHS, "\n", "\\l");
                string_replace_all(stored_RHS, "\"", "\\\"");
                if (node_label_idx_map.find(stored_RHS) == node_label_idx_map.end())
                {
                    node_idx++;
                    node_label_idx_map[stored_RHS] = node_idx;
                    dot_file += "  " + std::to_string(node_idx) + " [ shape=box label=\"" + stored_RHS + "\" ]\n";
                    // dot_file += "  " + std::to_string(node_idx) + " [ shape=box label=\"<<pre>" + stored_RHS + "</pre>>\" ]\n";
                }
                dot_file += "  " + std::to_string(node_label_idx_map[k_label]) + " -> " + std::to_string(node_label_idx_map[stored_RHS]) + " [ arrowhead=tee, label=\"" + op_str + "\" ]\n";
            }
            Sequence RHS = context.recall(op_idx, ket_idx)->to_seq();
            if (RHS.size() <= 1) {
                for (const auto& k2 : RHS.to_sp()) {
                    if (node_label_idx_map.find(k2.label()) == node_label_idx_map.end()) {
                        node_idx++;
                        node_label_idx_map[k2.label()] = node_idx;
                        dot_file += "  " + std::to_string(node_idx) + " [ label=\"" + k2.label() + "\" ]\n";
                    }
                    dot_file += "  " + std::to_string(node_label_idx_map[k_label]) + " -> " + std::to_string(node_label_idx_map[k2.label()]) + " [ label=\"" + op_str + "\" ]\n";
                }
            }
            else {
                dot_file += "\n  subgraph cluster_" + std::to_string(cluster_idx) + " {\n  rankdir=\"LR\"\n  ranksep=\"0.05\"\n";
                cluster_idx++;
                std::string first_element;
                unsigned int current_node_idx = node_idx;
                for (const auto& sp2 : RHS) {
                    std::string current_element = sp2.readable_display();
                    node_idx++;
                    dot_file += "  " + std::to_string(node_idx) + " [ label=\"" + current_element + "\" ]\n";
                }
                node_idx = current_node_idx;
                unsigned int first_element_idx = current_node_idx;
                bool first_pass = true;
                for (const auto& sp2 : RHS) {
                    node_idx++;
                    if (first_pass) {
                        first_pass = false;
                        first_element_idx = node_idx;
                        dot_file += "  " + std::to_string(first_element_idx);
                    }
                    else {
                        dot_file += " -> " + std::to_string(node_idx);
                    }
                }
                dot_file += " [ arrowhead=dot ]\n  }\n  " + std::to_string(node_label_idx_map[k_label]) + " -> " + std::to_string(first_element_idx) +
                    "  [ label=\"" + op_str + "\" ] \n";
            }
        }
    }
    dot_file += "}\n";
    return dot_file;
}

std::string dump(const Superposition& input_sp, ContextList& context, const std::vector<ulong>& operators, const std::vector<ulong>& general_operators)
{
    std::string s;
    ulong star_idx = ket_map.get_idx("*");
    for (const auto& k : input_sp)
    {
        bool has_line_added = false;
        if (operators.size() == 1 && operators[0] == star_idx)
        {
            for (ulong op_idx : context.supported_ops(k.label_idx()))
            {
                std::string op_label = ket_map.get_str(op_idx);
                unsigned int rhs_type = context.recall_type(op_idx, k.label_idx());
                if (rhs_type == RULEUNDEFINED) {
                    continue;
                }
                has_line_added = true;
                std::string rhs = context.recall(op_idx, k.label_idx())->to_string();
                std::string rule_type_str;
                switch (rhs_type) {
                case RULESTORED: {
                    rule_type_str = "#";
                    break;
                }
                case RULEMEMOIZE: {
                    rule_type_str = "!";
                    break;
                }
                }
                s += op_label + ' ' + k.to_string() + ' ' + rule_type_str + "=> " + rhs;
                s += "\n";
            }
            for (ulong op_idx : general_operators)
            {
                std::string op_label = ket_map.get_str(op_idx);
                Sequence seq = context.active_recall(op_idx, k.label_idx());
                s += op_label + ' ' + k.to_string() + " => " + seq.to_string() + "\n";
                has_line_added = true;
            }
        }
        else
        {
            for (ulong op_idx : operators)
            {
                std::string op_label = ket_map.get_str(op_idx);
                unsigned int rhs_type = context.recall_type(op_idx, k.label_idx());
                if (rhs_type == RULEUNDEFINED) {
                    continue;
                }
                has_line_added = true;
                std::string rhs = context.recall(op_idx, k.label_idx())->to_string();
                std::string rule_type_str;
                switch (rhs_type) {
                case RULESTORED: {
                    rule_type_str = "#";
                    break;
                }
                case RULEMEMOIZE: {
                    rule_type_str = "!";
                    break;
                }
                }
                s += op_label + ' ' + k.to_string() + ' ' + rule_type_str + "=> " + rhs;
                s += "\n";
            }
            for (ulong op_idx : general_operators)
            {
                std::string op_label = ket_map.get_str(op_idx);
                Sequence seq = context.active_recall(op_idx, k.label_idx());
                s += op_label + ' ' + k.to_string() + " => " + seq.to_string() + "\n";
                has_line_added = true;
            }
        }
        if (has_line_added)
        {
            s += "\n";
        }
    }
    return s;
}


Superposition op_transitive(const Sequence& input_seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters)
{
    if (parameters.empty()) { return Ket(); }
    Superposition full_sp;
    if (parameters.size() == 1)
    {
        if (parameters[0]->type() != COPERATOR) { return Ket(); }
        SimpleOperator op = parameters[0]->get_operator();
        Superposition working_sp = op.Compile(context, input_seq).to_sp();
        if (working_sp.is_empty_ket()) { return working_sp; }
        full_sp = working_sp;
        Superposition previous_sp = full_sp;
        size_t previous_len = 0;
        size_t current_len = working_sp.size();
        while (true)
        {
            working_sp = op.Compile(context, working_sp).to_sp();
            if (working_sp.is_empty_ket()) { /* std::cout << "empty\n" */; return full_sp; }
            full_sp.add(working_sp);
            current_len = full_sp.size();
            if (previous_len == current_len) { std::cout << "equal\n"; return previous_sp; }  // Prevent infinite loop if graph has a loop.
            previous_sp = full_sp;
            previous_len = current_len;
        }
    }
    if (parameters.size() == 2)
    {
        if (parameters[0]->type() != COPERATOR || parameters[1]->type() != CINT) { return Ket(); }
        SimpleOperator op = parameters[0]->get_operator();
        int max_steps = parameters[1]->get_int();
        if (max_steps < 1) { return Ket(); }
        int steps = 0;
        Superposition working_sp = op.Compile(context, input_seq).to_sp();
        if (working_sp.is_empty_ket()) { return working_sp; }
        full_sp = working_sp;
        Superposition previous_sp = full_sp;
        steps++;
        if (steps >= max_steps) { return full_sp; }
        size_t previous_len = 0;
        size_t current_len = working_sp.size();
        while (true)
        {
            working_sp = op.Compile(context, working_sp).to_sp();
            if (working_sp.is_empty_ket()) { /* std::cout << "empty\n" */; return full_sp; }
            full_sp.add(working_sp);
            current_len = full_sp.size();
            if (previous_len == current_len) { std::cout << "equal\n"; return previous_sp; }  // Prevent infinite loop if graph has a loop.
            previous_sp = full_sp;
            previous_len = current_len;
            steps++;
            if (steps >= max_steps) { return full_sp; }
        }
    }
    return full_sp;
}

Sequence op_stransitive(const Sequence& input_seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters)
{
    if (parameters.size() != 2) { return Ket(); }
    if (parameters[0]->type() != COPERATOR || parameters[1]->type() != CINT) { return Ket(); }
    SimpleOperator op = parameters[0]->get_operator();
    int max_steps = parameters[1]->get_int();
    if (max_steps < 1) { return Ket(); }
    int steps = 0;
    Sequence working_seq = op.Compile(context, input_seq);
    if (working_seq.is_empty_ket()) { return working_seq; }
    Sequence full_seq = working_seq;
    steps++;
    while (steps < max_steps)  // Convert it into a for loop?
    {
        working_seq = op.Compile(context, working_seq);
        if (working_seq.is_empty_ket()) { return full_seq; }
        full_seq.append(working_seq);
        steps++;
    }
    return full_seq;
}

Sequence op_borrow_from_context(const Sequence& input_seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters)
{
    if (parameters.size() != 2) { return Ket(); }
    if (parameters[0]->type() != CSTRING || parameters[1]->type() != COPERATOR) { return Ket(); }
    std::string context_name = parameters[0]->get_string();
    SimpleOperator op = parameters[1]->get_operator();
    Sequence seq;
    std::string starting_context_name = context.get_context_name();
    bool switch_success = context.switch_context(context_name);
    if (switch_success)
    {
        seq = op.Compile(context, input_seq);
        context.switch_context(starting_context_name);  // Only need to switch back to the original context if it successfully changed.
    }
    return seq;
}

Ket op_sdisplay_patch(const Sequence& input_seq, const std::vector<std::shared_ptr<CompoundConstant> >& parameters)
{
    if (parameters.size() != 1) { return Ket(); }
    if (parameters[0]->type() != CINT) { return Ket(); }
    int seq_len = (int)(input_seq.size());
    int width = parameters[0]->get_int();
    int height = seq_len / width;
    if (seq_len % width != 0) { height++; }
    if (width < 0 || height < 0) { return Ket(); }
    // std::cout << "width:  " << width << "\n";
    // std::cout << "height: " << height << "\n";
    std::vector<std::string> grid_elements;
    size_t max_element_size = 2;  // Set min element length to 2.
    for (const auto& sp : input_seq)
    {
        std::string element = sp.to_ket().label();
        max_element_size = std::max(max_element_size, element.size());
        grid_elements.push_back(element);
    }
    max_element_size++; // Increment max_element_size by 1, so that there is at least one space char between elements.
    std::cout << std::setfill(' ');
    unsigned int k = 0;
    for (const auto& element : grid_elements)
    {
        // std::cout << std::right << std::setw(max_element_size) << element; // Do we want left or right justified?
        std::cout << std::left << std::setw(max_element_size) << element; // Do we want left or right justified? I think left.
        k++;
        if (k % width == 0)
        {
            std::cout << "\n";
        }
    }
    return Ket("patch");
}

Ket op_spatch_map(const Sequence& input_seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters)
{
    int input_width = 0;
    int output_width = 0;
    int output_height = 0;
    int skip_size = 1;
    if (parameters.size() == 4)
    {
        if (parameters[0]->type() != CINT || parameters[1]->type() != CINT || parameters[2]->type() != CINT || parameters[3]->type() != COPERATOR) { return Ket(); }
        input_width = parameters[0]->get_int();
        output_width = parameters[1]->get_int();
        output_height = parameters[2]->get_int();
    }
    else if (parameters.size() == 5)
    {
        if (parameters[0]->type() != CINT || parameters[1]->type() != CINT || parameters[2]->type() != CINT || parameters[3]->type() != CINT || parameters[4]->type() != COPERATOR) { return Ket(); }
        input_width = parameters[0]->get_int();
        skip_size = parameters[1]->get_int();
        output_width = parameters[2]->get_int();
        output_height = parameters[3]->get_int();
    }
    else
    {
        return Ket();
    }
    SimpleOperator op = parameters[parameters.size() - 1]->get_operator();
    int patch_count = 0;
    int seq_len = (int)(input_seq.size());
    int input_height = seq_len / input_width;
    if (seq_len % input_width != 0) { input_height++; }
    if (input_width <= 0 || input_height <= 0 || output_width <= 0 || output_height <= 0 || skip_size < 1) { return Ket(); }
    if (output_width > input_width || output_height > input_height) { return Ket(); }

    // std::cout << "input width:   " << input_width << "\n";
    // std::cout << "input height:  " << input_height << "\n";
    // std::cout << "output width:  " << output_width << "\n";
    // std::cout << "output height: " << output_height << "\n";
    // std::cout << "skip size:     " << skip_size << "\n";
    // std::cout << "operator:      " << op.to_string() << "\n";

    int skip_index = 0;
    for (int y = 0; y <= (input_height - output_height); y++)
    {
        for (int x = 0; x <= (input_width - output_width); x++)
        {
            // std::cout << "x: " << x << " y: " << y << "\n";
            // if (skip_index % skip_size == 0)  // Skip based on total number of patches.
            if (x % skip_size == 0 && y % skip_size == 0)              // Skip based on x and y position. Not yet sure which we want.
            {
                Sequence patch;
                for (int y2 = 0; y2 < output_height; y2++)
                {
                    for (int x2 = 0; x2 < output_width; x2++)
                    {
                        int pos = (y + y2) * input_width + (x + x2);
                        patch.append(input_seq.get(pos));
                    }
                }
                op.Compile(context, patch);
                patch_count++;
            }
            skip_index++;
        }
    }
    return Ket("patches", patch_count);
}

Ket op_display_patch(const Sequence& input_seq, const std::vector<std::shared_ptr<CompoundConstant> >& parameters)
{
    if (parameters.size() != 2) { return Ket(); }
    if (parameters[0]->type() != CINT || parameters[1]->type() != CINT) { return Ket(); }
    int width = parameters[0]->get_int();
    int height = parameters[0]->get_int();
    if (width <= 0 || height <= 0) { return Ket(); }
    Superposition input_sp = input_seq.to_sp();
    if (input_sp.size() == 0) { return Ket(); }
    std::vector<std::string> grid_elements;
    size_t max_element_size = 2;  // Set min element length to 2.
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            ulong pos_idx = ket_map.get_idx(std::to_string(y) + ": " + std::to_string(x));
            double pos_value = input_sp.find_value(pos_idx);
            std::string grid_element;
            if (double_eq(pos_value, 0))  // Do we always want 0 as space char??
            {
                grid_element = " ";
            }
            else
            {
                grid_element = float_to_int(pos_value, default_decimal_places);
            }
            max_element_size = std::max(max_element_size, grid_element.size());
            grid_elements.push_back(grid_element);
        }
    }
    max_element_size++; // Increment max_element_size by 1, so that there is at least one space char between elements.
    std::cout << std::setfill(' ');
    unsigned int k = 0;
    for (const auto& element : grid_elements)
    {
        std::cout << std::left << std::setw(max_element_size) << element;
        k++;
        if (k % width == 0)
        {
            std::cout << "\n";
        }
    }
    return Ket("patch");
}

Ket op_patch_map(const Sequence& input_seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters)
{
    int input_width = 0;
    int input_height = 0;
    int output_width = 0;
    int output_height = 0;
    int skip_size = 1;
    if (parameters.size() == 5)
    {
        if (parameters[0]->type() != CINT || parameters[1]->type() != CINT || parameters[2]->type() != CINT || parameters[3]->type() != CINT || parameters[4]->type() != COPERATOR) { return Ket(); }
        input_width = parameters[0]->get_int();
        input_height = parameters[1]->get_int();
        output_width = parameters[2]->get_int();
        output_height = parameters[3]->get_int();
    }
    else if (parameters.size() == 6)
    {
        if (parameters[0]->type() != CINT || parameters[1]->type() != CINT || parameters[2]->type() != CINT || parameters[3]->type() != CINT || parameters[4]->type() != CINT || parameters[5]->type() != COPERATOR) { return Ket(); }
        input_width = parameters[0]->get_int();
        input_height = parameters[1]->get_int();
        skip_size = parameters[2]->get_int();
        output_width = parameters[3]->get_int();
        output_height = parameters[4]->get_int();
    }
    else
    {
        return Ket();
    }
    SimpleOperator op = parameters[parameters.size() - 1]->get_operator();
    Superposition input_sp = input_seq.to_sp();
    int patch_count = 0;
    if (input_width <= 0 || input_height <= 0 || output_width <= 0 || output_height <= 0 || skip_size < 1) { return Ket(); }
    if (output_width > input_width || output_height > input_height) { return Ket(); }

    for (int y = 0; y <= (input_height - output_height); y++)
    {
        for (int x = 0; x <= (input_width - output_width); x++)
        {
            // std::cout << "x: " << x << " y: " << y << "\n";
            if (x % skip_size == 0 && y % skip_size == 0)              // Skip based on x and y position.
            {
                Superposition patch;
                for (int y2 = 0; y2 < output_height; y2++)
                {
                    for (int x2 = 0; x2 < output_width; x2++)
                    {
                        // int pos = (y + y2) * input_width + (x + x2);
                        ulong pos_idx = ket_map.get_idx(std::to_string(y + y2) + ": " + std::to_string(x + x2));
                        double pos_value = input_sp.find_value(pos_idx);
                        Ket patch_ket(std::to_string(y2) + ": " + std::to_string(x2), pos_value);
                        patch.add(patch_ket);
                    }
                }
                op.Compile(context, patch);
                patch_count++;
            }
        }
    }
    return Ket("patches", patch_count);
}

Sequence op_sequence_arc_encoder(const Sequence& input_seq, const std::vector<std::shared_ptr<CompoundConstant> >& parameters)
{
    if (input_seq.size() != 4 || parameters.size() != 5) { return input_seq; }
    if (parameters[0]->type() != CFLOAT || parameters[1]->type() != CFLOAT || parameters[2]->type() != CFLOAT || parameters[3]->type() != CFLOAT || parameters[4]->type() != CINT )
    {
        return Ket();
    }
    double s1 = parameters[0]->get_float();
    double s2 = parameters[1]->get_float();
    double s3 = parameters[2]->get_float();
    double s4 = parameters[3]->get_float();
    int width = parameters[4]->get_int();
    if (s1 < 0 || s2 < 0 || s3 < 0 || s4 < 0 || width <= 0) { return Ket(); }
    
    // std::cout << "s1: " << std::to_string(s1) << "\n";
    // std::cout << "s2: " << std::to_string(s2) << "\n";
    // std::cout << "s3: " << std::to_string(s3) << "\n";
    // std::cout << "s4: " << std::to_string(s4) << "\n";
    // std::cout << "width: " << std::to_string(width) << "\n";

    Sequence result;
    Superposition tmp;
    for (const Ket k : input_seq.get(0))
    {
        int value = (int)(s1 * std::stod(k.label()));
        for (int i = value - width; i <= value + width; i++)
        {
            tmp.add(std::to_string(i));
        }
    }
    result.append(tmp);
    tmp.clear();

    for (const Ket k : input_seq.get(1))
    {
        int value = (int)(s2 * std::stod(k.label()));
        for (int i = value - width; i <= value + width; i++)
        {
            tmp.add(std::to_string(i));
        }
    }
    result.append(tmp);
    tmp.clear();

    for (const Ket k : input_seq.get(2))
    {
        int value = (int)(s3 * std::stod(k.label()));
        for (int i = value - width; i <= value + width; i++)
        {
            tmp.add(std::to_string(i));
        }
    }
    result.append(tmp);
    tmp.clear();

    for (const Ket k : input_seq.get(3))
    {
        int value = (int)(s4 * std::stod(k.label()));
        for (int i = value - width; i <= value + width; i++)
        {
            double new_value = (float)(i) / s4;
            if (new_value > 180)
            {
                new_value -= 360;
            }
            else if (new_value < -179)
            {
                new_value += 360;
            }
            int int_new_value = (int)(s4 * new_value);
            tmp.add(std::to_string(int_new_value));
        }
    }
    result.append(tmp);

    return result;
}

Ket op_copy(const Sequence& input_seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters)
{
    if (parameters.size() != 2) { return Ket(); }
    if (parameters[0]->type() != COPERATOR || parameters[1]->type() != COPERATOR) { return Ket(); }
    ulong op1_idx = parameters[0]->get_operator().get_head_op_idx();
    ulong op2_idx = parameters[1]->get_operator().get_head_op_idx();
    for (const Ket k : input_seq.to_sp())
    {
        ulong ket_idx = k.label_idx();
        unsigned int rule_type = context.recall_type(op1_idx, ket_idx);
        std::shared_ptr<BaseSequence> bSeq = context.recall(op1_idx, ket_idx);
        if (rule_type == RULENORMAL)
        {
            context.learn(op2_idx, ket_idx, bSeq);
        }
        else if (rule_type == RULESTORED)
        {
            context.stored_learn(op2_idx, ket_idx, bSeq);
        }
        else if (rule_type == RULEMEMOIZE)
        {
            context.memoize_learn(op2_idx, ket_idx, bSeq);
        }
    }
    size_t rule_count = input_seq.to_sp().size();
    return Ket("Copied " + std::to_string(rule_count) + " rules.");
}

Ket op_random_integer(const Sequence& input_seq, const std::vector<std::shared_ptr<CompoundConstant> >& parameters)
{
    if (parameters.size() != 1) { return Ket(); }
    if (parameters[0]->type() != CINT) { return Ket(); }
    int digits = parameters[0]->get_int();
    int max_int = ipower(10, digits);

    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(1, max_int); // guaranteed unbiased

    int random_integer = uni(rng);
    return Ket(std::to_string(random_integer));
}


Superposition op_tensor_product(const Sequence& input_seq, const std::vector<std::shared_ptr<CompoundConstant> >& parameters)
{
    if (parameters.size() != 1) { return Superposition(); }
    if (input_seq.size() <= 1) { return input_seq.to_sp(); }
    std::string merge_str = parameters[0]->get_string();
    Superposition result_sp;
    bool first_loop = true;
    for (const auto& loop_sp : input_seq)
    {
        if (!loop_sp.is_empty_ket())  // If the current vector/superposition is the empty ket, ignore, and proceed with the next vector/superposition.
        {
            if (first_loop)
            {
                result_sp = loop_sp;  // Is there a faster alternative than assign/copy?
                first_loop = false;
            }
            else
            {
                Superposition new_result_sp;
                for (const auto& k1 : result_sp)
                {
                    for (const auto& k2 : loop_sp)
                    {
                        std::string new_label;
                        if (k1.is_empty_ket() || k2.is_empty_ket())
                        {
                            new_label = k1.label() + k2.label();
                        }
                        else
                        {
                            new_label = k1.label() + merge_str + k2.label();
                        }
                        double new_value = k1.value() * k2.value();
                        new_result_sp.add(new_label, new_value);
                    }
                }
                result_sp = new_result_sp;
            }
        }
    }
    return result_sp;
}


