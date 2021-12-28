//
// Semantic DB 4
// Created 2021/12/28
// Updated 2021/12/28
// Author Garry Morrison
// License GPL v3
//

#include "FunctionOperatorMap.h"

FunctionOperatorMap::FunctionOperatorMap() {
    ulong idx;

    idx = ket_map.get_idx("clean");
    fn_map.sigmoids.insert(idx);

    idx = ket_map.get_idx("ReLU");
    fn_map.sigmoids.insert(idx);

    idx = ket_map.get_idx("shuffle");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("sshuffle");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("sreverse");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("srotate-left");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("srotate-right");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("srotate-left");
    fn_map.compound_built_in.insert(idx);

    idx = ket_map.get_idx("srotate-right");
    fn_map.compound_built_in.insert(idx);

    idx = ket_map.get_idx("rotate-left");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("rotate-right");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("rotate-left");
    fn_map.compound_built_in.insert(idx);

    idx = ket_map.get_idx("rotate-right");
    fn_map.compound_built_in.insert(idx);

    idx = ket_map.get_idx("sdrop");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("threshold-filter");
    fn_map.compound_sigmoids.insert(idx);

    idx = ket_map.get_idx("not-threshold-filter");
    fn_map.compound_sigmoids.insert(idx);

    idx = ket_map.get_idx("sigmoid-in-range");
    fn_map.compound_sigmoids.insert(idx);

    idx = ket_map.get_idx("sigmoid-min");
    fn_map.compound_sigmoids.insert(idx);

    idx = ket_map.get_idx("sigmoid-max");
    fn_map.compound_sigmoids.insert(idx);

    idx = ket_map.get_idx("random");
    // fn_map.compound_sigmoids.insert(idx, &op_sigmoid_random);
    fn_map.compound_seq_fn.insert(idx);

    idx = ket_map.get_idx("sleep");
    fn_map.compound_seq_fn.insert(idx);

    idx = ket_map.get_idx("split");
    fn_map.ket_fn.insert(idx);
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("ssplit");
    fn_map.ket_fn.insert(idx);
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("bar-chart");
    fn_map.compound_sp_fn.insert(idx);

    idx = ket_map.get_idx("print");
    fn_map.ket_fn.insert(idx);

    idx = ket_map.get_idx("extract-head");
    fn_map.ket_fn.insert(idx);

    idx = ket_map.get_idx("extract-tail");
    fn_map.ket_fn.insert(idx);

    idx = ket_map.get_idx("extract-category");
    fn_map.ket_fn.insert(idx);

    idx = ket_map.get_idx("extract-value");
    fn_map.ket_fn.insert(idx);

    idx = ket_map.get_idx("floor");
    fn_map.ket_fn.insert(idx);

    idx = ket_map.get_idx("ceiling");
    fn_map.ket_fn.insert(idx);

    idx = ket_map.get_idx("log");
    fn_map.ket_fn.insert(idx);

    idx = ket_map.get_idx("push-float");
    fn_map.ket_fn.insert(idx);

    idx = ket_map.get_idx("pop-float");
    fn_map.ket_fn.insert(idx);

    idx = ket_map.get_idx("rank");
    fn_map.sp_fn.insert(idx);

    idx = ket_map.get_idx("sp2seq");
    fn_map.sp_fn.insert(idx);

    idx = ket_map.get_idx("seq2sp");
    fn_map.seq_fn.insert(idx);

    idx = ket_map.get_idx("do-you-know");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("how-many");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("measure-currency");
    fn_map.built_in.insert(idx);


    idx = ket_map.get_idx("show-many");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("sidx");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("rescale");
    fn_map.built_in.insert(idx);
    fn_map.compound_built_in.insert(idx);

    idx = ket_map.get_idx("normalize");
    fn_map.built_in.insert(idx);
    fn_map.compound_built_in.insert(idx);

    idx = ket_map.get_idx("reverse");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("drop");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("pick-elt");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("weighted-pick-elt");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("drop-below");
    fn_map.compound_built_in.insert(idx);

    idx = ket_map.get_idx("drop-above");
    fn_map.compound_built_in.insert(idx);

    idx = ket_map.get_idx("pick");
    fn_map.compound_built_in.insert(idx);

    idx = ket_map.get_idx("ket-sort");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("coeff-sort");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("natural-sort");
    fn_map.built_in.insert(idx);

    idx = ket_map.get_idx("sort-by");
    fn_map.compound_context_built_in.insert(idx);

    idx = ket_map.get_idx("srange");
    fn_map.whitelist_2.insert(idx);
    fn_map.whitelist_3.insert(idx);

    idx = ket_map.get_idx("range");
    fn_map.whitelist_2.insert(idx);
    fn_map.whitelist_3.insert(idx);

    idx = ket_map.get_idx("arithmetic");
    fn_map.whitelist_3.insert(idx);

    idx = ket_map.get_idx("simm");
    fn_map.whitelist_2.insert(idx);

    idx = ket_map.get_idx("strict-simm");
    fn_map.whitelist_2.insert(idx);

    idx = ket_map.get_idx("grid-simm");
    fn_map.context_whitelist_2.insert(idx);

    idx = ket_map.get_idx("similar-grid");
    fn_map.context_whitelist_1.insert(idx);

    idx = ket_map.get_idx("intersection");
    fn_map.whitelist_2.insert(idx);

    idx = ket_map.get_idx("union");
    fn_map.whitelist_2.insert(idx);

    idx = ket_map.get_idx("sum");
    fn_map.whitelist_2.insert(idx);

    idx = ket_map.get_idx("select");
    fn_map.compound_built_in.insert(idx);

    idx = ket_map.get_idx("sselect");
    fn_map.compound_built_in.insert(idx);

    idx = ket_map.get_idx("rel-kets");
    fn_map.compound_context_seq_fn.insert(idx);

    idx = ket_map.get_idx("similar-input");
    fn_map.compound_context_seq_fn.insert(idx);

    idx = ket_map.get_idx("strict-similar-input");
    fn_map.compound_context_seq_fn.insert(idx);

    idx = ket_map.get_idx("equal-input");
    fn_map.compound_context_seq_fn.insert(idx);

    idx = ket_map.get_idx("minus");
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("plus");
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("times-by");
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("divide-by");
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("int-divide-by");
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("round");
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("mod");
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("to-upper");
    fn_map.ket_fn.insert(idx);
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("to-lower");
    fn_map.ket_fn.insert(idx);
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("table");
    fn_map.compound_context_sp_fn.insert(idx);

    idx = ket_map.get_idx("transpose-table");
    fn_map.compound_context_sp_fn.insert(idx);

    idx = ket_map.get_idx("filter");
    fn_map.context_whitelist_2.insert(idx);

    idx = ket_map.get_idx("not-filter");
    fn_map.context_whitelist_2.insert(idx);

    idx = ket_map.get_idx("apply");
    fn_map.context_whitelist_2.insert(idx);

    idx = ket_map.get_idx("learn");
    fn_map.context_whitelist_3.insert(idx);

    idx = ket_map.get_idx("add-learn");
    fn_map.context_whitelist_3.insert(idx);

    idx = ket_map.get_idx("seq-learn");
    fn_map.context_whitelist_3.insert(idx);

    idx = ket_map.get_idx("smerge");
    fn_map.seq_fn.insert(idx);
    fn_map.compound_seq_fn.insert(idx);


    idx = ket_map.get_idx("learn-grid");
    fn_map.compound_context_sp_fn.insert(idx);

    idx = ket_map.get_idx("display-grid");
    fn_map.compound_context_sp_fn.insert(idx);

    idx = ket_map.get_idx("op-zip");
    fn_map.context_whitelist_1.insert(idx);

    idx = ket_map.get_idx("op-if");
    fn_map.context_whitelist_3.insert(idx);

    idx = ket_map.get_idx("value-if");
    fn_map.whitelist_3.insert(idx);

    idx = ket_map.get_idx("is-less-than");
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("is-less-equal-than");
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("is-equal");
    fn_map.compound_ket_fn.insert(idx);
    fn_map.whitelist_2.insert(idx);

    idx = ket_map.get_idx("is-greater-than");
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("is-greater-equal-than");
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("is-in-range");
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("is-prime");
    fn_map.ket_fn.insert(idx);

    idx = ket_map.get_idx("prime-factors");
    fn_map.ket_fn.insert(idx);

    idx = ket_map.get_idx("such-that");
    fn_map.compound_context_seq_fn.insert(idx);

    idx = ket_map.get_idx("is-mbr");
    fn_map.whitelist_1.insert(idx);

    idx = ket_map.get_idx("mbr");
    fn_map.whitelist_1.insert(idx);

    idx = ket_map.get_idx("is-subset");
    fn_map.whitelist_1.insert(idx);

    idx = ket_map.get_idx("smap");
    fn_map.compound_context_seq_fn.insert(idx);
    fn_map.context_whitelist_3.insert(idx);

    idx = ket_map.get_idx("Gaussian");
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("and");
    fn_map.whitelist_1.insert(idx);
    fn_map.whitelist_2.insert(idx);

    idx = ket_map.get_idx("or");
    fn_map.whitelist_1.insert(idx);
    fn_map.whitelist_2.insert(idx);

    idx = ket_map.get_idx("xor");
    fn_map.whitelist_1.insert(idx);
    fn_map.whitelist_2.insert(idx);

    idx = ket_map.get_idx("find-inverse");
    fn_map.compound_context_seq_fn.insert(idx);

    idx = ket_map.get_idx("remove-suffix");
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("has-suffix");
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("remove-prefix");
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("has-prefix");
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("to-comma-number");
    fn_map.ket_fn.insert(idx);

    idx = ket_map.get_idx("find-path-between");
    fn_map.context_whitelist_2.insert(idx);

    idx = ket_map.get_idx("find-operators-between");
    fn_map.context_whitelist_2.insert(idx);

    idx = ket_map.get_idx("digit2sp");
    fn_map.compound_sp_fn.insert(idx);

    idx = ket_map.get_idx("invert");
    fn_map.sigmoids.insert(idx);

    idx = ket_map.get_idx("unlearn");
    fn_map.compound_context_sp_fn.insert(idx);
    fn_map.context_whitelist_1.insert(idx);

    idx = ket_map.get_idx("sread");
    fn_map.whitelist_1.insert(idx);

    idx = ket_map.get_idx("not-sread");
    fn_map.whitelist_1.insert(idx);

    idx = ket_map.get_idx("read");
    fn_map.whitelist_1.insert(idx);

    idx = ket_map.get_idx("not-read");
    fn_map.whitelist_1.insert(idx);

    idx = ket_map.get_idx("scompress");
    fn_map.compound_context_seq_fn.insert(idx);

    idx = ket_map.get_idx("starts-with");
    fn_map.context_ket_fn.insert(idx);

    idx = ket_map.get_idx("string-replace");
    fn_map.whitelist_2.insert(idx);

    idx = ket_map.get_idx("inherit");
    fn_map.compound_context_seq_fn.insert(idx);

    idx = ket_map.get_idx("inherit-path");
    fn_map.compound_context_seq_fn.insert(idx);

    idx = ket_map.get_idx("sprint");
    fn_map.seq_fn.insert(idx);
    fn_map.compound_seq_fn.insert(idx);

    idx = ket_map.get_idx("ket-length");
    fn_map.ket_fn.insert(idx);

    idx = ket_map.get_idx("compile");
    fn_map.context_seq_fn.insert(idx);

    idx = ket_map.get_idx("op-for");
    fn_map.context_whitelist_2.insert(idx);
    fn_map.context_whitelist_3.insert(idx);
    fn_map.context_whitelist_4.insert(idx);

    idx = ket_map.get_idx("op-sfor");
    fn_map.context_whitelist_2.insert(idx);
    fn_map.context_whitelist_3.insert(idx);
    fn_map.context_whitelist_4.insert(idx);

    idx = ket_map.get_idx("hash");
    fn_map.compound_ket_fn.insert(idx);

    idx = ket_map.get_idx("common");
    fn_map.compound_context_seq_fn.insert(idx);

    idx = ket_map.get_idx("op-union");
    fn_map.compound_context_seq_fn.insert(idx);

    idx = ket_map.get_idx("op-sum");
    fn_map.compound_context_seq_fn.insert(idx);

    idx = ket_map.get_idx("spike-merge");
    fn_map.compound_seq_fn.insert(idx);

    idx = ket_map.get_idx("transform");
    fn_map.whitelist_2.insert(idx);

    idx = ket_map.get_idx("save-as-dot");
    fn_map.compound_context_sp_fn.insert(idx);



    // Now some other set up:
    simple_operators.insert(built_in.begin(), built_in.end());
    simple_operators.insert(sigmoids.begin(), sigmoids.end());
    simple_operators.insert(ket_fn.begin(), ket_fn.end());
    simple_operators.insert(context_ket_fn.begin(), context_ket_fn.end());
    simple_operators.insert(sp_fn.begin(), sp_fn.end());
    simple_operators.insert(seq_fn.begin(), seq_fn.end());
    simple_operators.insert(context_seq_fn.begin(), context_seq_fn.end());

    compound_operators.insert(compound_built_in.begin(), compound_built_in.end());
    compound_operators.insert(compound_context_built_in.begin(), compound_context_built_in.end());
    compound_operators.insert(compound_sigmoids.begin(), compound_sigmoids.end());
    compound_operators.insert(compound_ket_fn.begin(), compound_ket_fn.end());
    compound_operators.insert(compound_sp_fn.begin(), compound_sp_fn.end());
    compound_operators.insert(compound_context_sp_fn.begin(), compound_context_sp_fn.end());
    compound_operators.insert(compound_seq_fn.begin(), compound_seq_fn.end());
    compound_operators.insert(compound_context_seq_fn.begin(), compound_context_seq_fn.end());

    function_operators.insert(whitelist_1.begin(), whitelist_1.end());
    function_operators.insert(whitelist_2.begin(), whitelist_2.end());
    function_operators.insert(whitelist_3.begin(), whitelist_3.end());
    function_operators.insert(whitelist_4.begin(), whitelist_4.end());
    function_operators.insert(context_whitelist_1.begin(), context_whitelist_1.end());
    function_operators.insert(context_whitelist_2.begin(), context_whitelist_2.end());
    function_operators.insert(context_whitelist_3.begin(), context_whitelist_3.end());
    function_operators.insert(context_whitelist_4.begin(), context_whitelist_4.end());


    for (ulong idx : simple_operators)
    {
        std::string s = ket_map.get_str(idx);
        list_of_operator_names.insert(s);
    }
    for (ulong idx : compound_operators)
    {
        std::string s = ket_map.get_str(idx);
        list_of_operator_names.insert(s);
    }
    for (ulong idx : function_operators)
    {
        std::string s = ket_map.get_str(idx);
        list_of_operator_names.insert(s);
    }

    
    list_of_statements = { "if", "if-else", "for", "sfor", "while" };
    list_of_learn_rules = { "=>", "+=>", ".=>", "#=>", "!=>" };
    list_of_infix_type1 = { "+", "-", ".", "_", "__", ":_" };
    list_of_infix_type2 = { "==", "!=", ">=", ">", "<=", "<", "&&", "||", "++", "--", "**", "//", "%%", "^^", ".." };
    list_of_misc_elements = { "|>", "comment", "label descent", "|*>", "|category: *>", "|_self>", "(*,*)", "|__self>", "|context>", "supported-ops", "dump", "if-then machine" };
    list_of_filtered_misc_elements = { "|>", "comment", "|*>", "|category: *>", "|_self>", "(*,*)", "|__self>", "|context>", "if-then machine" };
    list_of_object_types = { "ket", "superposition", "sequence" };
    list_of_operator_types = { "sigmoid", "numeric", "simple", "compound", "function", "bracket", "powered", "op-sequence" };

    list_of_operator_and_statement_names.insert(list_of_operator_names.begin(), list_of_operator_names.end());
    for (const auto& statement : list_of_statements)
    {
        list_of_operator_and_statement_names.insert(statement);
    }
}
