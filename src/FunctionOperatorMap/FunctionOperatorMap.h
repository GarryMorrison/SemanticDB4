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
#include "../Sequence/Sequence.h"


class FunctionOperatorMap
{
private:
public:
    FunctionOperatorMap();

    // Our map versions:
    std::unordered_map<ulong, std::function<Sequence(const Sequence*)> > built_in;
    std::unordered_map<ulong, std::function<Sequence(const Sequence*, const std::vector<std::shared_ptr<CompoundConstant> >&)> > compound_built_in;
    std::unordered_map<ulong, std::function<Sequence(const Sequence*, ContextList&, const std::vector<std::shared_ptr<CompoundConstant> >&)> > compound_context_built_in;

    std::unordered_map<ulong, std::function<double(const double)> > sigmoids;
    std::unordered_map<ulong, std::function<Sequence(const Ket&)> > ket_fn;
    std::unordered_map<ulong, std::function<Sequence(const Superposition&)> > sp_fn;
    std::unordered_map<ulong, std::function<Sequence(const Sequence&)> > seq_fn;

    std::unordered_map<ulong, std::function<Sequence(const Ket&, ContextList&)> > context_ket_fn;
    std::unordered_map<ulong, std::function<Sequence(const Sequence&, ContextList&)> > context_seq_fn;

    std::unordered_map<ulong, std::function<double(const double, const std::vector<std::shared_ptr<CompoundConstant> >&) > > compound_sigmoids;
    std::unordered_map<ulong, std::function<Sequence(const Ket, const std::vector<std::shared_ptr<CompoundConstant> >&) > > compound_ket_fn;
    std::unordered_map<ulong, std::function<Sequence(const Superposition&, const std::vector<std::shared_ptr<CompoundConstant> >&) > > compound_sp_fn;
    std::unordered_map<ulong, std::function<Sequence(const Sequence&, const std::vector<std::shared_ptr<CompoundConstant> >&) > > compound_seq_fn;

    std::unordered_map<ulong, std::function<Sequence(const Superposition&, ContextList&, const std::vector<std::shared_ptr<CompoundConstant> >&) > > compound_context_sp_fn;
    std::unordered_map<ulong, std::function<Sequence(const Sequence&, ContextList&, const std::vector<std::shared_ptr<CompoundConstant> >&) > > compound_context_seq_fn;

    std::unordered_map<ulong, std::function<Sequence(const Sequence&, const Sequence&)> > whitelist_1;
    std::unordered_map<ulong, std::function<Sequence(const Sequence&, const Sequence&, const Sequence&)> > whitelist_2;
    std::unordered_map<ulong, std::function<Sequence(const Sequence&, const Sequence&, const Sequence&, const Sequence&)> > whitelist_3;
    std::unordered_map<ulong, std::function<Sequence(const Sequence&, const Sequence&, const Sequence&, const Sequence&, const Sequence&)> > whitelist_4;

    std::unordered_map<ulong, std::function<Sequence(ContextList&, const Sequence&, const Sequence&)> > context_whitelist_1;
    std::unordered_map<ulong, std::function<Sequence(ContextList&, const Sequence&, const Sequence&, const Sequence&)> > context_whitelist_2;
    std::unordered_map<ulong, std::function<Sequence(ContextList&, const Sequence&, const Sequence&, const Sequence&, const Sequence&)> > context_whitelist_3;
    std::unordered_map<ulong, std::function<Sequence(ContextList&, const Sequence&, const Sequence&, const Sequence&, const Sequence&, const Sequence&)> > context_whitelist_4;


    // Our set versions:
    std::set<ulong> set_built_in;
    std::set<ulong> set_compound_built_in;
    std::set<ulong> set_compound_context_built_in;
    std::set<ulong> set_sigmoids;
    std::set<ulong> set_compound_sigmoids;
    std::set<ulong> set_ket_fn;
    std::set<ulong> set_compound_ket_fn;
    std::set<ulong> set_context_ket_fn;
    std::set<ulong> set_sp_fn;
    std::set<ulong> set_compound_sp_fn;
    std::set<ulong> set_compound_context_sp_fn;
    std::set<ulong> set_seq_fn;
    std::set<ulong> set_context_seq_fn;
    std::set<ulong> set_compound_seq_fn;
    std::set<ulong> set_compound_context_seq_fn;
    std::set<ulong> set_whitelist_1;
    std::set<ulong> set_whitelist_2;
    std::set<ulong> set_whitelist_3;
    std::set<ulong> set_whitelist_4;
    std::set<ulong> set_context_whitelist_1;
    std::set<ulong> set_context_whitelist_2;
    std::set<ulong> set_context_whitelist_3;
    std::set<ulong> set_context_whitelist_4;

    std::set<ulong> set_simple_operators;
    std::set<ulong> set_compound_operators;
    std::set<ulong> set_function_operators;

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