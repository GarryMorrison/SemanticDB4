//
// Semantic DB 4
// Created 2021/12/28
// Updated 2021/12/28
// Author Garry Morrison
// License GPL v3
//

#pragma once

#include <set>
#include "../KetMap/KetMap.h"

class FunctionOperatorMap
{
private:
public:
    FunctionOperatorMap();

    std::set<ulong> built_in;
    std::set<ulong> compound_built_in;
    std::set<ulong> compound_context_built_in;
    std::set<ulong> sigmoids;
    std::set<ulong> compound_sigmoids;
    std::set<ulong> ket_fn;
    std::set<ulong> compound_ket_fn;
    std::set<ulong> context_ket_fn;
    std::set<ulong> sp_fn;
    std::set<ulong> compound_sp_fn;
    std::set<ulong> compound_context_sp_fn;
    std::set<ulong> seq_fn;
    std::set<ulong> context_seq_fn;
    std::set<ulong> compound_seq_fn;
    std::set<ulong> compound_context_seq_fn;
    std::set<ulong> whitelist_1;
    std::set<ulong> whitelist_2;
    std::set<ulong> whitelist_3;
    std::set<ulong> whitelist_4;
    std::set<ulong> context_whitelist_1;
    std::set<ulong> context_whitelist_2;
    std::set<ulong> context_whitelist_3;
    std::set<ulong> context_whitelist_4;

    std::set<ulong> simple_operators;
    std::set<ulong> compound_operators;
    std::set<ulong> function_operators;

    std::vector<std::string> list_of_statements;
    std::vector<std::string> list_of_learn_rules;  // We don't want auto sort here.
    std::vector<std::string> list_of_infix_type1;
    std::vector<std::string> list_of_infix_type2;

    std::vector<std::string> list_of_misc_elements;
    std::vector<std::string> list_of_filtered_misc_elements;
    std::vector<std::string> list_of_object_types;
    std::vector<std::string> list_of_operator_types;

    std::set<std::string> list_of_operator_names;  // I think I use set to auto sort.
    std::set<std::string> list_of_operator_and_statement_names;
};

extern FunctionOperatorMap fn_map;