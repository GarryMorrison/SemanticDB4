#pragma once

//
// Created by Garry Morrison on 21/09/2020.
//


#include "../Sequence/Sequence.h"
#include "../OperatorLibrary/SigmoidLibrary.h"

Superposition range2(ulong start_idx, ulong stop_idx);
Sequence op_srange2(const Sequence& input_seq, const Sequence& start, const Sequence& stop);
Sequence op_srange3(const Sequence& input_seq, const Sequence& start, const Sequence& stop, const Sequence& step);
Superposition op_range2(const Sequence& input_seq, const Sequence& start, const Sequence& stop);
Superposition op_range3(const Sequence& input_seq, const Sequence& start, const Sequence& stop, const Sequence& step);
Sequence op_arithmetic3(const Sequence& input_seq, const Sequence& one, const Sequence& symbol_ket, const Sequence& two);
double simm(const Superposition& sp1, const Superposition& sp2);
double scaled_simm(const Superposition& sp1, const Superposition& sp2);
double natural_simm(const Superposition& sp1, const Superposition& sp2);
double simm(const Sequence& seq1, const Sequence& seq2);
double strict_simm(const Sequence& seq1, const Sequence& seq2);
double natural_simm(const Sequence& seq1, const Sequence& seq2);
double unscaled_simm(const Sequence& seq1, const Sequence& seq2);
Sequence op_simm2(const Sequence& input_seq, const Sequence& seq1, const Sequence& seq2);
Sequence op_strict_simm2(const Sequence& input_seq, const Sequence& seq1, const Sequence& seq2);
Sequence op_natural_simm2(const Sequence& input_seq, const Sequence& seq1, const Sequence& seq2);
Sequence op_unscaled_simm2(const Sequence& input_seq, const Sequence& seq1, const Sequence& seq2);
Superposition sp_intersection(const Superposition& sp1, const Superposition& sp2);
Sequence op_intersection2(const Sequence& input_seq, const Sequence& one, const Sequence& two);
Superposition sp_union(const Superposition& sp1, const Superposition& sp2);
Sequence op_union2(const Sequence& input_seq, const Sequence& one, const Sequence& two);
Superposition sp_sum(const Superposition& sp1, const Superposition& sp2);
Sequence op_sum2(const Sequence& input_seq, const Sequence& one, const Sequence& two);
Sequence op_filter(ContextList& context, const Sequence& input_seq, const Sequence& one, const Sequence& two);
Sequence op_not_filter(ContextList& context, const Sequence& input_seq, const Sequence& one, const Sequence& two);
Sequence op_apply(ContextList& context, const Sequence& input_seq, const Sequence& one, const Sequence& two);
Sequence op_learn(ContextList& context, const Sequence& input_seq, const Sequence& one, const Sequence& two, const Sequence& three);
Sequence op_add_learn(ContextList& context, const Sequence& input_seq, const Sequence& one, const Sequence& two, const Sequence& three);
Sequence op_seq_learn(ContextList& context, const Sequence& input_seq, const Sequence& one, const Sequence& two, const Sequence& three);
Sequence op_zip(ContextList& context, const Sequence& input_seq, const Sequence& one);
Sequence op_if(ContextList& context, const Sequence& input_seq, const Sequence& one, const Sequence& two, const Sequence& three);
Sequence op_value_if(const Sequence& input_seq, const Sequence& one, const Sequence& two, const Sequence& three);
Ket op_is_mbr(const Sequence& input_seq, const Sequence& one);
Ket op_mbr(const Sequence& input_seq, const Sequence& one);
Ket op_is_subset(const Sequence& input_seq, const Sequence& one);
Sequence op_and1(const Sequence& input_seq, const Sequence& one);
Sequence op_or1(const Sequence& input_seq, const Sequence& one);
Sequence op_xor1(const Sequence& input_seq, const Sequence& one);
Sequence op_and2(const Sequence& input_seq, const Sequence& one, const Sequence& two);
Sequence op_or2(const Sequence& input_seq, const Sequence& one, const Sequence& two);
Sequence op_xor2(const Sequence& input_seq, const Sequence& one, const Sequence& two);
Sequence op_smap3(ContextList& context, const Sequence& input_seq, const Sequence& one, const Sequence& two, const Sequence& three);
Sequence op_is_equal2(const Sequence& input_seq, const Sequence& seq1, const Sequence& seq2);
Sequence op_find_path_between(ContextList& context, const Sequence& input_seq, const Sequence& seq1, const Sequence& seq2);
Sequence op_find_operators_between(ContextList& context, const Sequence& input_seq, const Sequence& seq1, const Sequence& seq2);
Sequence op_sread(const Sequence& input_seq, const Sequence& one);
Sequence op_not_sread(const Sequence& input_seq, const Sequence& one);
Sequence op_read(const Sequence& input_seq, const Sequence& one);
Sequence op_not_read(const Sequence& input_seq, const Sequence& one);
Sequence op_swrite(const Sequence& input_seq, const Sequence& one, const Sequence& two);
Sequence op_write(const Sequence& input_seq, const Sequence& one, const Sequence& two);
Sequence op_string_replace(const Sequence& input_seq, const Sequence& one, const Sequence& two);
Sequence op_for2(ContextList& context, const Sequence& input_seq, const Sequence& one, const Sequence& two);
Sequence op_for3(ContextList& context, const Sequence& input_seq, const Sequence& one, const Sequence& two, const Sequence& three);
Sequence op_for4(ContextList& context, const Sequence& input_seq, const Sequence& one, const Sequence& two, const Sequence& three, const Sequence& four);
Sequence op_sfor2(ContextList& context, const Sequence& input_seq, const Sequence& one, const Sequence& two);
Sequence op_sfor3(ContextList& context, const Sequence& input_seq, const Sequence& one, const Sequence& two, const Sequence& three);
Sequence op_sfor4(ContextList& context, const Sequence& input_seq, const Sequence& one, const Sequence& two, const Sequence& three, const Sequence& four);
Sequence op_unlearn_fn(ContextList& context, const Sequence& input_seq, const Sequence& one);
Sequence op_grid_simm2(ContextList& context, const Sequence& input_seq, const Sequence& one, const Sequence& two);
Superposition op_similar_grid(ContextList& context, const Sequence& input_seq, const Sequence& one);
Superposition op_transform(const Sequence& input_seq, const Sequence& one, const Sequence& two);
Sequence op_parallel_sum(const Sequence& input_seq, const Sequence& one);
Sequence op_sprint_fn1(const Sequence& input_seq, const Sequence& one);
Sequence op_sprint_fn2(const Sequence& input_seq, const Sequence& one, const Sequence& two);
Ket op_dump_fn1(ContextList& context, const Sequence& input_seq, const Sequence& one);
Ket op_recursive_dump_fn1(ContextList& context, const Sequence& input_seq, const Sequence& one);
Sequence op_substring_index(const Sequence& input_seq, const Sequence& one);
std::string generate_dot_string(ContextList& context, const Sequence& input_seq, const Sequence& one);
Ket op_print_dot_fn1(ContextList& context, const Sequence& input_seq, const Sequence& one);
Sequence op_pick_fn1(const Sequence& input_seq, const Sequence& one);
Ket op_random_int_fn2(const Sequence& input_seq, const Sequence& one, const Sequence& two);
Sequence op_xor_fn1(const Sequence& input_seq, const Sequence& one);

