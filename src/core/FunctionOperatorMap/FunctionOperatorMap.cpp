//
// Semantic DB 4
// Created 2021/12/28
// Updated 2023/6/4
// Author Garry Morrison
// License GPL v3
//

#include "FunctionOperatorMap.h"
#include "../OperatorLibrary/SigmoidLibrary.h"
#include "../OperatorLibrary/OperatorLibrary.h"
#include "../OperatorLibrary/FunctionOperatorLibrary.h"
#include "../OperatorLibrary/TMOperatorLibrary.h"
#include "../OperatorUsageMap/OperatorUsageMap.h"
extern OperatorUsageMap operator_usage_map;


FunctionOperatorMap::FunctionOperatorMap() {
    ulong idx;

    idx = ket_map.get_idx("clean");
    fn_map.sigmoids.emplace(idx, &clean);

    idx = ket_map.get_idx("ReLU");
    fn_map.sigmoids.emplace(idx, &ReLU);

    idx = ket_map.get_idx("sigmoid-inc");
    fn_map.sigmoids.emplace(idx, &sigmoid_inc);

    idx = ket_map.get_idx("sigmoid-dec");
    fn_map.sigmoids.emplace(idx, &sigmoid_dec);

    idx = ket_map.get_idx("shuffle");
    fn_map.built_in.emplace(idx, &Sequence::shuffle);

    idx = ket_map.get_idx("sshuffle");
    fn_map.built_in.emplace(idx, &Sequence::sshuffle);

    idx = ket_map.get_idx("sreverse");
    fn_map.built_in.emplace(idx, &Sequence::sreverse);

    idx = ket_map.get_idx("srotate-left");
    fn_map.built_in.emplace(idx, &Sequence::op_srotate_left);

    idx = ket_map.get_idx("srotate-right");
    fn_map.built_in.emplace(idx, &Sequence::op_srotate_right);

    idx = ket_map.get_idx("srotate-left");
    fn_map.compound_built_in.emplace(idx, &Sequence::op_srotate_left1);

    idx = ket_map.get_idx("srotate-right");
    fn_map.compound_built_in.emplace(idx, &Sequence::op_srotate_right1);

    idx = ket_map.get_idx("rotate-left");
    fn_map.built_in.emplace(idx, &Sequence::op_rotate_left);

    idx = ket_map.get_idx("rotate-right");
    fn_map.built_in.emplace(idx, &Sequence::op_rotate_right);

    idx = ket_map.get_idx("rotate-left");
    fn_map.compound_built_in.emplace(idx, &Sequence::op_rotate_left1);

    idx = ket_map.get_idx("rotate-right");
    fn_map.compound_built_in.emplace(idx, &Sequence::op_rotate_right1);

    idx = ket_map.get_idx("sdrop");
    fn_map.built_in.emplace(idx, &Sequence::sdrop);

    idx = ket_map.get_idx("threshold-filter");
    fn_map.compound_sigmoids.emplace(idx, &op_threshold_filter);

    idx = ket_map.get_idx("not-threshold-filter");
    fn_map.compound_sigmoids.emplace(idx, &op_not_threshold_filter);

    idx = ket_map.get_idx("sigmoid-in-range");
    fn_map.compound_sigmoids.emplace(idx, &op_sigmoid_in_range);

    idx = ket_map.get_idx("sigmoid-min");
    fn_map.compound_sigmoids.emplace(idx, &op_min);

    idx = ket_map.get_idx("sigmoid-max");
    fn_map.compound_sigmoids.emplace(idx, &op_max);

    idx = ket_map.get_idx("random");
    // fn_map.compound_sigmoids.emplace(idx, &op_sigmoid_random);
    fn_map.compound_seq_fn.emplace(idx, &op_random);

    idx = ket_map.get_idx("sleep");
    fn_map.compound_seq_fn.emplace(idx, &op_sleep_ms);

    idx = ket_map.get_idx("split");
    fn_map.ket_fn.emplace(idx, &op_split_ket);
    fn_map.compound_ket_fn.emplace(idx, &op_split);

    idx = ket_map.get_idx("ssplit");
    fn_map.ket_fn.emplace(idx, &op_ssplit_ket);
    fn_map.compound_ket_fn.emplace(idx, &op_ssplit);

    idx = ket_map.get_idx("bar-chart");
    fn_map.compound_sp_fn.emplace(idx, &op_bar_chart);

    idx = ket_map.get_idx("raw-bar-chart");
    fn_map.sp_fn.emplace(idx, &op_raw_bar_chart);

    idx = ket_map.get_idx("print");
    fn_map.ket_fn.emplace(idx, &print_ket);

    
    
    // Old ket based versions of extract-*
    // Deprecated, for now, by the Sequence versions, which are hopefully faster:
    idx = ket_map.get_idx("extract-head");
    fn_map.ket_fn.emplace(idx, &extract_head);
    
    idx = ket_map.get_idx("extract-tail");
    fn_map.ket_fn.emplace(idx, &extract_tail);

    idx = ket_map.get_idx("extract-category");
    fn_map.ket_fn.emplace(idx, &extract_category);

    idx = ket_map.get_idx("extract-value");
    fn_map.ket_fn.emplace(idx, &extract_value);

    idx = ket_map.get_idx("extract-headless");
    fn_map.ket_fn.emplace(idx, &extract_headless);
    

    
    /*  // These are currently broken! There are bugs in the corresponding Superposition:: methods.
    // New sequence based versions of extract-*
    idx = ket_map.get_idx("extract-head");
    fn_map.seq_fn.emplace(idx, &op_extract_head);

    idx = ket_map.get_idx("extract-tail");
    fn_map.seq_fn.emplace(idx, &op_extract_tail);

    idx = ket_map.get_idx("extract-category");
    fn_map.seq_fn.emplace(idx, &op_extract_category);

    idx = ket_map.get_idx("extract-value");
    fn_map.seq_fn.emplace(idx, &op_extract_value);

    idx = ket_map.get_idx("extract-headless");
    fn_map.seq_fn.emplace(idx, &op_extract_headless);
    */


    idx = ket_map.get_idx("floor");
    fn_map.ket_fn.emplace(idx, &op_floor);

    idx = ket_map.get_idx("ceiling");
    fn_map.ket_fn.emplace(idx, &op_ceiling);

    idx = ket_map.get_idx("log");
    fn_map.ket_fn.emplace(idx, &op_log);

    idx = ket_map.get_idx("push-float");
    fn_map.ket_fn.emplace(idx, &push_float);

    idx = ket_map.get_idx("pop-float");
    fn_map.ket_fn.emplace(idx, &pop_float);

    idx = ket_map.get_idx("rank");
    fn_map.sp_fn.emplace(idx, &rank);

    idx = ket_map.get_idx("sp2seq");
    fn_map.sp_fn.emplace(idx, &sp2seq);

    idx = ket_map.get_idx("seq2sp");
    fn_map.seq_fn.emplace(idx, &seq2sp);

    /*
    // double find_min_coeff() const;
    // double find_max_coeff() const;
    Sequence drop_below(const double t) const;
    Sequence drop_above(const double t) const;
    Sequence pick(const ulong n) const;
    */

    idx = ket_map.get_idx("do-you-know");
    fn_map.built_in.emplace(idx, &Sequence::do_you_know);

    idx = ket_map.get_idx("how-many");
    fn_map.built_in.emplace(idx, &Sequence::how_many);

    idx = ket_map.get_idx("measure-currency");
    fn_map.built_in.emplace(idx, &Sequence::measure_currency);

    idx = ket_map.get_idx("show-many");
    fn_map.built_in.emplace(idx, &Sequence::show_many);

    idx = ket_map.get_idx("sidx");
    fn_map.built_in.emplace(idx, &Sequence::sidx);

    idx = ket_map.get_idx("rescale");
    fn_map.built_in.emplace(idx, &Sequence::op_rescale0);
    fn_map.compound_built_in.emplace(idx, &Sequence::op_rescale1);

    idx = ket_map.get_idx("normalize");
    fn_map.built_in.emplace(idx, &Sequence::op_normalize0);
    fn_map.compound_built_in.emplace(idx, &Sequence::op_normalize1);

    idx = ket_map.get_idx("reverse");
    fn_map.built_in.emplace(idx, &Sequence::reverse);

    idx = ket_map.get_idx("drop");
    fn_map.built_in.emplace(idx, &Sequence::drop);

    idx = ket_map.get_idx("pick-elt");
    fn_map.built_in.emplace(idx, &Sequence::pick_elt);

    idx = ket_map.get_idx("weighted-pick-elt");
    fn_map.built_in.emplace(idx, &Sequence::weighted_pick_elt);

    idx = ket_map.get_idx("drop-below");
    fn_map.compound_built_in.emplace(idx, &Sequence::op_drop_below1);

    idx = ket_map.get_idx("drop-above");
    fn_map.compound_built_in.emplace(idx, &Sequence::op_drop_above1);

    idx = ket_map.get_idx("pick");
    fn_map.compound_built_in.emplace(idx, &Sequence::op_pick1);
    fn_map.whitelist_1.emplace(idx, &op_pick_fn1);

    idx = ket_map.get_idx("ket-sort");
    fn_map.built_in.emplace(idx, &Sequence::ket_sort);

    idx = ket_map.get_idx("coeff-sort");
    fn_map.built_in.emplace(idx, &Sequence::coeff_sort);

    idx = ket_map.get_idx("natural-sort");
    fn_map.built_in.emplace(idx, &Sequence::natural_sort);

    idx = ket_map.get_idx("sort-by");
    fn_map.compound_context_built_in.emplace(idx, &Sequence::sort_by);

    idx = ket_map.get_idx("srange");
    fn_map.whitelist_2.emplace(idx, &op_srange2);
    fn_map.whitelist_3.emplace(idx, &op_srange3);

    idx = ket_map.get_idx("range");
    fn_map.whitelist_2.emplace(idx, &op_range2);
    fn_map.whitelist_3.emplace(idx, &op_range3);

    idx = ket_map.get_idx("arithmetic");
    fn_map.whitelist_3.emplace(idx, &op_arithmetic3);

    idx = ket_map.get_idx("simm");
    fn_map.whitelist_2.emplace(idx, &op_simm2);

    idx = ket_map.get_idx("strict-simm");
    fn_map.whitelist_2.emplace(idx, &op_strict_simm2);

    idx = ket_map.get_idx("natural-simm");
    fn_map.whitelist_2.emplace(idx, &op_natural_simm2);

    idx = ket_map.get_idx("unscaled-simm");
    fn_map.whitelist_2.emplace(idx, &op_unscaled_simm2);

    idx = ket_map.get_idx("grid-simm");
    fn_map.context_whitelist_2.emplace(idx, &op_grid_simm2);

    idx = ket_map.get_idx("similar-grid");
    fn_map.context_whitelist_1.emplace(idx, &op_similar_grid);

    idx = ket_map.get_idx("intersection");
    fn_map.whitelist_2.emplace(idx, &op_intersection2);

    idx = ket_map.get_idx("union");
    fn_map.whitelist_2.emplace(idx, &op_union2);

    idx = ket_map.get_idx("sum");
    fn_map.whitelist_2.emplace(idx, &op_sum2);

    idx = ket_map.get_idx("select");
    fn_map.compound_built_in.emplace(idx, &Sequence::op_select2);

    idx = ket_map.get_idx("sselect");
    fn_map.compound_built_in.emplace(idx, &Sequence::op_sselect2);

    idx = ket_map.get_idx("rel-kets");
    fn_map.compound_context_seq_fn.emplace(idx, &op_relevant_kets);

    idx = ket_map.get_idx("similar-input");
    fn_map.compound_context_seq_fn.emplace(idx, &op_similar_input);

    idx = ket_map.get_idx("strict-similar-input");
    fn_map.compound_context_seq_fn.emplace(idx, &op_strict_similar_input);

    idx = ket_map.get_idx("natural-similar-input");
    fn_map.compound_context_seq_fn.emplace(idx, &op_natural_similar_input);

    idx = ket_map.get_idx("unscaled-similar-input");
    fn_map.compound_context_seq_fn.emplace(idx, &op_unscaled_similar_input);

    idx = ket_map.get_idx("equal-input");
    fn_map.compound_context_seq_fn.emplace(idx, &op_equal_input);

    idx = ket_map.get_idx("star-equal-input");
    fn_map.compound_context_seq_fn.emplace(idx, &op_star_equal_input);

    idx = ket_map.get_idx("minus");
    fn_map.compound_ket_fn.emplace(idx, &op_minus);

    idx = ket_map.get_idx("plus");
    fn_map.compound_ket_fn.emplace(idx, &op_plus);

    idx = ket_map.get_idx("times-by");
    fn_map.compound_ket_fn.emplace(idx, &op_times_by);

    idx = ket_map.get_idx("divide-by");
    fn_map.compound_ket_fn.emplace(idx, &op_divide_by);

    idx = ket_map.get_idx("int-divide-by");
    fn_map.compound_ket_fn.emplace(idx, &op_int_divide_by);

    idx = ket_map.get_idx("round");
    fn_map.compound_ket_fn.emplace(idx, &op_round);

    idx = ket_map.get_idx("mod");
    fn_map.compound_ket_fn.emplace(idx, &op_modulus);

    idx = ket_map.get_idx("to-upper");
    fn_map.ket_fn.emplace(idx, &toupperket);
    fn_map.compound_ket_fn.emplace(idx, &op_toupper);

    idx = ket_map.get_idx("to-lower");
    fn_map.ket_fn.emplace(idx, &tolowerket);
    fn_map.compound_ket_fn.emplace(idx, &op_tolower);

    idx = ket_map.get_idx("table");
    fn_map.compound_context_sp_fn.emplace(idx, &op_table);

    idx = ket_map.get_idx("tidy-table");
    fn_map.compound_context_sp_fn.emplace(idx, &op_tidy_table);

    idx = ket_map.get_idx("transpose-table");
    fn_map.compound_context_sp_fn.emplace(idx, &op_transpose_table);

    idx = ket_map.get_idx("filter");
    fn_map.context_whitelist_2.emplace(idx, &op_filter);

    idx = ket_map.get_idx("not-filter");
    fn_map.context_whitelist_2.emplace(idx, &op_not_filter);

    idx = ket_map.get_idx("apply");
    fn_map.context_whitelist_2.emplace(idx, &op_apply);

    idx = ket_map.get_idx("learn");
    fn_map.context_whitelist_3.emplace(idx, &op_learn);

    idx = ket_map.get_idx("add-learn");
    fn_map.context_whitelist_3.emplace(idx, &op_add_learn);

    idx = ket_map.get_idx("seq-learn");
    fn_map.context_whitelist_3.emplace(idx, &op_seq_learn);

    idx = ket_map.get_idx("smerge");
    fn_map.seq_fn.emplace(idx, &op_smerge);
    fn_map.compound_seq_fn.emplace(idx, &op_smerge1);

    idx = ket_map.get_idx("learn-grid");
    fn_map.compound_context_sp_fn.emplace(idx, &op_learn_grid);

    idx = ket_map.get_idx("display-grid");
    fn_map.compound_context_sp_fn.emplace(idx, &op_display_grid);

    idx = ket_map.get_idx("op-zip");
    fn_map.context_whitelist_1.emplace(idx, &op_zip);

    idx = ket_map.get_idx("op-if");
    fn_map.context_whitelist_3.emplace(idx, &op_if);

    idx = ket_map.get_idx("value-if");
    fn_map.whitelist_3.emplace(idx, &op_value_if);

    idx = ket_map.get_idx("is-less-than");
    fn_map.compound_ket_fn.emplace(idx, &op_is_less_than);

    idx = ket_map.get_idx("is-less-equal-than");
    fn_map.compound_ket_fn.emplace(idx, &op_is_less_equal_than);

    idx = ket_map.get_idx("is-equal");
    fn_map.compound_ket_fn.emplace(idx, &op_is_equal);
    fn_map.whitelist_2.emplace(idx, &op_is_equal2);

    idx = ket_map.get_idx("is-greater-than");
    fn_map.compound_ket_fn.emplace(idx, &op_is_greater_than);

    idx = ket_map.get_idx("is-greater-equal-than");
    fn_map.compound_ket_fn.emplace(idx, &op_is_greater_equal_than);

    idx = ket_map.get_idx("is-in-range");
    fn_map.compound_ket_fn.emplace(idx, &op_is_in_range);

    idx = ket_map.get_idx("is-prime");
    fn_map.ket_fn.emplace(idx, &op_is_prime);

    idx = ket_map.get_idx("prime-factors");
    fn_map.ket_fn.emplace(idx, &op_prime_factors);

    idx = ket_map.get_idx("such-that");
    fn_map.compound_context_seq_fn.emplace(idx, &op_such_that);

    idx = ket_map.get_idx("is-mbr");
    fn_map.whitelist_1.emplace(idx, &op_is_mbr);

    idx = ket_map.get_idx("mbr");
    fn_map.whitelist_1.emplace(idx, &op_mbr);

    idx = ket_map.get_idx("is-subset");
    fn_map.whitelist_1.emplace(idx, &op_is_subset);

    idx = ket_map.get_idx("smap");
    fn_map.compound_context_seq_fn.emplace(idx, &op_smap);
    fn_map.context_whitelist_3.emplace(idx, &op_smap3);

    idx = ket_map.get_idx("Gaussian");
    fn_map.compound_ket_fn.emplace(idx, &op_Gaussian);

    idx = ket_map.get_idx("and");
    fn_map.whitelist_1.emplace(idx, &op_and1);
    fn_map.whitelist_2.emplace(idx, &op_and2);

    idx = ket_map.get_idx("or");
    fn_map.whitelist_1.emplace(idx, &op_or1);
    fn_map.whitelist_2.emplace(idx, &op_or2);

    idx = ket_map.get_idx("xor");
    fn_map.whitelist_1.emplace(idx, &op_xor1);
    fn_map.whitelist_2.emplace(idx, &op_xor2);

    idx = ket_map.get_idx("find-inverse");
    fn_map.compound_context_seq_fn.emplace(idx, &op_find_inverse);

    idx = ket_map.get_idx("remove-suffix");
    fn_map.compound_ket_fn.emplace(idx, &op_remove_suffix);

    idx = ket_map.get_idx("has-suffix");
    fn_map.compound_ket_fn.emplace(idx, &op_has_suffix);

    idx = ket_map.get_idx("remove-prefix");
    fn_map.compound_ket_fn.emplace(idx, &op_remove_prefix);

    idx = ket_map.get_idx("has-prefix");
    fn_map.compound_ket_fn.emplace(idx, &op_has_prefix);

    idx = ket_map.get_idx("to-comma-number");
    fn_map.ket_fn.emplace(idx, &op_to_comma_number);

    idx = ket_map.get_idx("find-path-between");
    fn_map.context_whitelist_2.emplace(idx, &op_find_path_between);

    idx = ket_map.get_idx("find-operators-between");
    fn_map.context_whitelist_2.emplace(idx, &op_find_operators_between);

    idx = ket_map.get_idx("digit2sp");
    fn_map.compound_sp_fn.emplace(idx, &digit2sp);

    idx = ket_map.get_idx("invert");
    fn_map.sigmoids.emplace(idx, &op_invert);

    idx = ket_map.get_idx("unlearn");
    fn_map.compound_context_sp_fn.emplace(idx, &op_unlearn);
    fn_map.context_whitelist_1.emplace(idx, &op_unlearn_fn);

    idx = ket_map.get_idx("sread");
    fn_map.whitelist_1.emplace(idx, &op_sread);

    idx = ket_map.get_idx("not-sread");
    fn_map.whitelist_1.emplace(idx, &op_not_sread);

    idx = ket_map.get_idx("read");
    fn_map.whitelist_1.emplace(idx, &op_read);

    idx = ket_map.get_idx("not-read");
    fn_map.whitelist_1.emplace(idx, &op_not_read);

    idx = ket_map.get_idx("swrite");
    fn_map.whitelist_2.emplace(idx, &op_swrite);

    idx = ket_map.get_idx("write");
    fn_map.whitelist_2.emplace(idx, &op_write);

    idx = ket_map.get_idx("scompress");
    fn_map.compound_context_seq_fn.emplace(idx, &op_scompress);

    idx = ket_map.get_idx("starts-with");
    fn_map.context_ket_fn.emplace(idx, &starts_with);

    idx = ket_map.get_idx("string-replace");
    fn_map.whitelist_2.emplace(idx, &op_string_replace);

    idx = ket_map.get_idx("inherit");
    fn_map.compound_context_seq_fn.emplace(idx, &op_inherit);

    idx = ket_map.get_idx("inherit-path");
    fn_map.compound_context_seq_fn.emplace(idx, &op_inherit_path);

    idx = ket_map.get_idx("sprint");
    fn_map.seq_fn.emplace(idx, &op_sprint);
    fn_map.compound_seq_fn.emplace(idx, &op_sprint1);
    fn_map.whitelist_1.emplace(idx, &op_sprint_fn1);
    fn_map.whitelist_2.emplace(idx, &op_sprint_fn2);

    idx = ket_map.get_idx("ket-length");
    fn_map.ket_fn.emplace(idx, &ket_length);

    idx = ket_map.get_idx("compile");
    fn_map.context_seq_fn.emplace(idx, &op_compile);

    idx = ket_map.get_idx("op-for");
    fn_map.context_whitelist_2.emplace(idx, &op_for2);
    fn_map.context_whitelist_3.emplace(idx, &op_for3);
    fn_map.context_whitelist_4.emplace(idx, &op_for4);

    idx = ket_map.get_idx("op-sfor");
    fn_map.context_whitelist_2.emplace(idx, &op_sfor2);
    fn_map.context_whitelist_3.emplace(idx, &op_sfor3);
    fn_map.context_whitelist_4.emplace(idx, &op_sfor4);

    idx = ket_map.get_idx("hash");
    fn_map.compound_ket_fn.emplace(idx, &op_hash);

    idx = ket_map.get_idx("common");
    fn_map.compound_context_seq_fn.emplace(idx, &op_common);

    idx = ket_map.get_idx("op-union");
    fn_map.compound_context_seq_fn.emplace(idx, &op_compound_union);

    idx = ket_map.get_idx("op-sum");
    fn_map.compound_context_seq_fn.emplace(idx, &op_compound_sum);

    idx = ket_map.get_idx("spike-merge");
    fn_map.compound_seq_fn.emplace(idx, &op_spike_merge);

    idx = ket_map.get_idx("transform");
    fn_map.whitelist_2.emplace(idx, &op_transform);

    idx = ket_map.get_idx("save-as-dot");
    fn_map.compound_context_sp_fn.emplace(idx, &op_save_as_dot);

    idx = ket_map.get_idx("transitive");
    fn_map.compound_context_seq_fn.emplace(idx, &op_transitive);

    idx = ket_map.get_idx("stransitive");
    fn_map.compound_context_seq_fn.emplace(idx, &op_stransitive);

    idx = ket_map.get_idx("borrow-from-context");
    fn_map.compound_context_seq_fn.emplace(idx, &op_borrow_from_context);

    idx = ket_map.get_idx("parallel-sum-sequences");
    fn_map.whitelist_1.emplace(idx, &op_parallel_sum);

    idx = ket_map.get_idx("sdisplay-patch");
    fn_map.compound_seq_fn.emplace(idx, &op_sdisplay_patch);

    idx = ket_map.get_idx("spatch-map");
    fn_map.compound_context_seq_fn.emplace(idx, &op_spatch_map);

    idx = ket_map.get_idx("display-patch");
    fn_map.compound_seq_fn.emplace(idx, &op_display_patch);

    idx = ket_map.get_idx("patch-map");
    fn_map.compound_context_seq_fn.emplace(idx, &op_patch_map);

    idx = ket_map.get_idx("seq-arc-encoder");
    fn_map.compound_seq_fn.emplace(idx, &op_sequence_arc_encoder);

    idx = ket_map.get_idx("copy");
    fn_map.compound_context_seq_fn.emplace(idx, &op_copy);

    idx = ket_map.get_idx("random-int");
    fn_map.compound_ket_fn.emplace(idx, &op_random_integer);

    idx = ket_map.get_idx("dump");
    fn_map.context_whitelist_1.emplace(idx, &op_dump_fn1);

    idx = ket_map.get_idx("recursive-dump");
    fn_map.context_whitelist_1.emplace(idx, &op_recursive_dump_fn1);

    idx = ket_map.get_idx("substring-position");
    fn_map.whitelist_1.emplace(idx, &op_substring_index);

    idx = ket_map.get_idx("print-dot");
    fn_map.context_whitelist_1.emplace(idx, &op_print_dot_fn1);

    idx = ket_map.get_idx("tensor-product");
    fn_map.compound_seq_fn.emplace(idx, &op_tensor_product);

    idx = ket_map.get_idx("random-int");
    fn_map.whitelist_2.emplace(idx, &op_random_int_fn2);

    idx = ket_map.get_idx("XOR");
    fn_map.whitelist_1.emplace(idx, &op_xor_fn1);


    // Template machine related operators and functions:
    idx = ket_map.get_idx("TM-ngram-partition");
    fn_map.compound_context_seq_fn.emplace(idx, &op_TM_ngram_partition);

    idx = ket_map.get_idx("TM-sequence-hash");
    fn_map.seq_fn.emplace(idx, &op_TM_sequence_hash);

    idx = ket_map.get_idx("TM-ket-hash");
    fn_map.ket_fn.emplace(idx, &op_TM_ket_hash);

    idx = ket_map.get_idx("TM-extract-text");
    fn_map.whitelist_1.emplace(idx, &op_TM_extract_text);

    idx = ket_map.get_idx("TM-learn-sentences");
    fn_map.compound_context_seq_fn.emplace(idx, &op_TM_learn_sentences);

    idx = ket_map.get_idx("TM-compress-stars");
    fn_map.ket_fn.emplace(idx, &op_TM_compress_stars);

    idx = ket_map.get_idx("TM-generate");
    fn_map.context_seq_fn.emplace(idx, &op_TM_generate);
 
    idx = ket_map.get_idx("TM-learn-patches");
    fn_map.context_seq_fn.emplace(idx, &op_TM_learn_patches);

}


template <class T>
void learn_set(std::set<ulong>& the_set, T& our_map) {
    for (const auto& iter : our_map) {
        the_set.insert(iter.first);
    }
}

void FunctionOperatorMap::PopulateOperatorSets() {

    learn_set(set_built_in, built_in);
    learn_set(set_compound_built_in, compound_built_in);
    learn_set(set_compound_context_built_in, compound_context_built_in);
    learn_set(set_sigmoids, sigmoids);
    learn_set(set_compound_sigmoids, compound_sigmoids);
    learn_set(set_ket_fn, ket_fn);
    learn_set(set_compound_ket_fn, compound_ket_fn);
    learn_set(set_context_ket_fn, context_ket_fn);
    learn_set(set_sp_fn, sp_fn);
    learn_set(set_compound_sp_fn, compound_sp_fn);
    learn_set(set_compound_context_sp_fn, compound_context_sp_fn);
    learn_set(set_seq_fn, seq_fn);
    learn_set(set_context_seq_fn, context_seq_fn);
    learn_set(set_compound_seq_fn, compound_seq_fn);
    learn_set(set_compound_context_seq_fn, compound_context_seq_fn);
    learn_set(set_whitelist_1, whitelist_1);
    learn_set(set_whitelist_2, whitelist_2);
    learn_set(set_whitelist_3, whitelist_3);
    learn_set(set_whitelist_4, whitelist_4);
    learn_set(set_context_whitelist_1, context_whitelist_1);
    learn_set(set_context_whitelist_2, context_whitelist_2);
    learn_set(set_context_whitelist_3, context_whitelist_3);
    learn_set(set_context_whitelist_4, context_whitelist_4);

    // Now some other set up:
    set_simple_operators.insert(set_built_in.begin(), set_built_in.end());
    set_simple_operators.insert(set_sigmoids.begin(), set_sigmoids.end());
    set_simple_operators.insert(set_ket_fn.begin(), set_ket_fn.end());
    set_simple_operators.insert(set_context_ket_fn.begin(), set_context_ket_fn.end());
    set_simple_operators.insert(set_sp_fn.begin(), set_sp_fn.end());
    set_simple_operators.insert(set_seq_fn.begin(), set_seq_fn.end());
    set_simple_operators.insert(set_context_seq_fn.begin(), set_context_seq_fn.end());

    set_compound_operators.insert(set_compound_built_in.begin(), set_compound_built_in.end());
    set_compound_operators.insert(set_compound_context_built_in.begin(), set_compound_context_built_in.end());
    set_compound_operators.insert(set_compound_sigmoids.begin(), set_compound_sigmoids.end());
    set_compound_operators.insert(set_compound_ket_fn.begin(), set_compound_ket_fn.end());
    set_compound_operators.insert(set_compound_sp_fn.begin(), set_compound_sp_fn.end());
    set_compound_operators.insert(set_compound_context_sp_fn.begin(), set_compound_context_sp_fn.end());
    set_compound_operators.insert(set_compound_seq_fn.begin(), set_compound_seq_fn.end());
    set_compound_operators.insert(set_compound_context_seq_fn.begin(), set_compound_context_seq_fn.end());

    set_function_operators.insert(set_whitelist_1.begin(), set_whitelist_1.end());
    set_function_operators.insert(set_whitelist_2.begin(), set_whitelist_2.end());
    set_function_operators.insert(set_whitelist_3.begin(), set_whitelist_3.end());
    set_function_operators.insert(set_whitelist_4.begin(), set_whitelist_4.end());
    set_function_operators.insert(set_context_whitelist_1.begin(), set_context_whitelist_1.end());
    set_function_operators.insert(set_context_whitelist_2.begin(), set_context_whitelist_2.end());
    set_function_operators.insert(set_context_whitelist_3.begin(), set_context_whitelist_3.end());
    set_function_operators.insert(set_context_whitelist_4.begin(), set_context_whitelist_4.end());


    for (ulong idx : set_simple_operators)
    {
        std::string s = ket_map.get_str(idx);
        list_of_operator_names.insert(s);
    }
    for (ulong idx : set_compound_operators)
    {
        std::string s = ket_map.get_str(idx);
        list_of_operator_names.insert(s);
    }
    for (ulong idx : set_function_operators)
    {
        std::string s = ket_map.get_str(idx);
        list_of_operator_names.insert(s);
    }

    
    list_of_statements = { "if", "if-else", "for", "sfor", "while" };
    list_of_learn_rules = { "=>", "_=>", "+=>", ".=>", "#=>", "!=>" };
    list_of_infix_type1 = { "+", "-", ".", "_", "__", ":_" };
    list_of_infix_type2 = { "==", "!=", ">=", ">", "<=", "<", "&&", "||", "++", "--", "**", "//", "%%", "^^", ".." };

    list_of_learn_rules_spaces = { " => ", " _=> ", " +=> ", " .=> ", " #=> ", " !=> " };
    list_of_infix_type1_spaces = { " + ", " - ", " . ", " _ ", " __ ", " :_ " };
    list_of_infix_type2_spaces = { " == ", " != ", " >= ", " > ", " <= ", " < ", " && ", " || ", " ++ ", " -- ", " ** ", " // ", " %% ", " ^^ ", " .. " };

    list_of_misc_elements = { "|>", "comment", "label descent", "|*>", "|category: *>", "|_self>", "(*,*)", "|__self>", "|context>", "supported-ops", "dump", "if-then machine", "if-then operator" };
    list_of_filtered_misc_elements = { "|>", "comment", "|*>", "|category: *>", "|_self>", "(*,*)", "|__self>", "|context>", "if-then machine", "if-then operator" };
    list_of_object_types = { "ket", "superposition", "sequence" };
    list_of_operator_types = { "sigmoid", "numeric", "simple", "compound", "function", "bracket", "powered", "op-sequence" };

    list_of_operator_and_statement_names.insert(list_of_operator_names.begin(), list_of_operator_names.end());
    for (const auto& statement : list_of_statements)
    {
        list_of_operator_and_statement_names.insert(statement);
    }
}

std::vector<std::string> FunctionOperatorMap::get_operator_types(const std::string operator_name)
{
    std::vector<std::string> result;

    std::vector<std::string> v;
    v = list_of_statements;
    if (std::find(v.begin(), v.end(), operator_name) != v.end())
    {
        result.push_back("statement");
    }

    v = list_of_learn_rules_spaces;
    if (std::find(v.begin(), v.end(), operator_name) != v.end())
    {
        result.push_back("learn rule");
    }
    v = list_of_infix_type1_spaces;
    if (std::find(v.begin(), v.end(), operator_name) != v.end())
    {
        result.push_back("infix type 1");
    }
    v = list_of_infix_type2_spaces;
    if (std::find(v.begin(), v.end(), operator_name) != v.end())
    {
        result.push_back("infix type 2");
    }

    v = list_of_misc_elements;
    if (std::find(v.begin(), v.end(), operator_name) != v.end())
    {
        result.push_back("miscellaneous element");
    }
    v = list_of_object_types;
    if (std::find(v.begin(), v.end(), operator_name) != v.end())
    {
        result.push_back("object type");
    }
    v = list_of_operator_types;
    if (std::find(v.begin(), v.end(), operator_name) != v.end())
    {
        result.push_back("operator type");
    }


    ulong op_idx = ket_map.get_idx(operator_name);
    if (set_built_in.find(op_idx) != set_built_in.end())
    {
        result.push_back("core normal");
    }
    if (set_compound_built_in.find(op_idx) != set_compound_built_in.end())
    {
        result.push_back("core compound");
    }
    if (set_compound_context_built_in.find(op_idx) != set_compound_context_built_in.end())
    {
        result.push_back("core compound context");
    }

    if (set_sigmoids.find(op_idx) != set_sigmoids.end())
    {
        result.push_back("sigmoid normal");
    }
    if (set_compound_sigmoids.find(op_idx) != set_compound_sigmoids.end())
    {
        result.push_back("sigmoid compound");
    }

    if (set_ket_fn.find(op_idx) != set_ket_fn.end())
    {
        result.push_back("ket normal");
    }
    if (set_compound_ket_fn.find(op_idx) != set_compound_ket_fn.end())
    {
        result.push_back("ket compound");
    }
    if (set_context_ket_fn.find(op_idx) != set_context_ket_fn.end())
    {
        result.push_back("ket context");
    }

    if (set_sp_fn.find(op_idx) != set_sp_fn.end())
    {
        result.push_back("superposition normal");
    }
    if (set_compound_sp_fn.find(op_idx) != set_compound_sp_fn.end())
    {
        result.push_back("superposition compound");
    }
    if (set_compound_context_sp_fn.find(op_idx) != set_compound_context_sp_fn.end())
    {
        result.push_back("superposition compound context");
    }

    if (set_seq_fn.find(op_idx) != set_seq_fn.end())
    {
        result.push_back("sequence normal");
    }
    if (set_context_seq_fn.find(op_idx) != set_context_seq_fn.end())
    {
        result.push_back("sequence context");
    }
    if (set_compound_seq_fn.find(op_idx) != set_compound_seq_fn.end())
    {
        result.push_back("sequence compound");
    }
    if (set_compound_context_seq_fn.find(op_idx) != set_compound_context_seq_fn.end())
    {
        result.push_back("sequence compound context");
    }


    if (set_whitelist_1.find(op_idx) != set_whitelist_1.end())
    {
        result.push_back("function 1");
    }
    if (set_whitelist_2.find(op_idx) != set_whitelist_2.end())
    {
        result.push_back("function 2");
    }
    if (set_whitelist_3.find(op_idx) != set_whitelist_3.end())
    {
        result.push_back("function 3");
    }
    if (set_whitelist_4.find(op_idx) != set_whitelist_4.end())
    {
        result.push_back("function 4");
    }

    if (set_context_whitelist_1.find(op_idx) != set_context_whitelist_1.end())
    {
        result.push_back("context function 1");
    }
    if (set_context_whitelist_2.find(op_idx) != set_context_whitelist_2.end())
    {
        result.push_back("context function 2");
    }
    if (set_context_whitelist_3.find(op_idx) != set_context_whitelist_3.end())
    {
        result.push_back("context function 3");
    }
    if (set_context_whitelist_4.find(op_idx) != set_context_whitelist_4.end())
    {
        result.push_back("context function 4");
    }

    return result;
}


template <class T>
void print_map(const std::string& s, T& our_map) {
    std::cout << s << std::endl;
    std::vector<std::string> tmp_sorted;
    for (const auto& it : our_map) {
        tmp_sorted.push_back(ket_map.get_str(it.first));
    }
    std::sort(tmp_sorted.begin(), tmp_sorted.end());
    for (const auto& str : tmp_sorted) {
        std::string star;
        if (operator_usage_map.usage_is_defined(str)) {
            star = " * ";
        }
        std::cout << "    " << str << star << std::endl;
    }
}

void FunctionOperatorMap::print() const { // Doesn't need to be optimized at all.
    print_map("built_in:", built_in);
    print_map("compound_built_in:", compound_built_in);
    print_map("compound_context_built_in:", compound_context_built_in);
    print_map("sigmoid:", sigmoids);
    print_map("compound_sigmoid:", compound_sigmoids);
    print_map("ket_fn:", ket_fn);
    print_map("context_ket_fn:", context_ket_fn);
    print_map("context_seq_fn:", context_seq_fn);
    print_map("compound_ket_fn:", compound_ket_fn);
    print_map("sp_fn:", sp_fn);
    print_map("compound_sp_fn:", compound_sp_fn);
    print_map("seq_fn:", seq_fn);
    print_map("compound_seq_fn:", compound_seq_fn);
    print_map("compound_context_sp_fn:", compound_context_sp_fn);
    print_map("compound_context_seq_fn:", compound_context_seq_fn);
    print_map("function_1:", whitelist_1);
    print_map("function_2:", whitelist_2);
    print_map("function_3:", whitelist_3);
    print_map("function_4:", whitelist_4);
    print_map("context_function_1:", context_whitelist_1);
    print_map("context_function_2:", context_whitelist_2);
    print_map("context_function_3:", context_whitelist_3);
    print_map("context_function_4:", context_whitelist_4);
}
