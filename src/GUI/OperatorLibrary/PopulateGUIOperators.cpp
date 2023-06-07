//
// Semantic DB 4
// Created 2023/5/31
// Updated 2023/5/31
// Author Garry Morrison
// License GPL v3
//

#include "PopulateGUIOperators.h"

void PopulateGUIOperators(FunctionOperatorMap& map)
{
	ulong idx = 0;

	// GUI operators and functions:
	idx = ket_map.get_idx("gmessage");
	map.ket_fn.emplace(idx, &op_gmessage);

	idx = ket_map.get_idx("gdump");
	map.context_whitelist_1.emplace(idx, &op_gdump_fn1);

	idx = ket_map.get_idx("gtable");
	map.compound_context_sp_fn.emplace(idx, &op_gtable);

	idx = ket_map.get_idx("ggraph");
	map.context_whitelist_1.emplace(idx, &op_ggraph_fn1);
}
