//
// Semantic DB 4
// Created 2023/5/20
// Updated 2023/5/20
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../Sequence/Ket.h"

Ket op_gmessage(const Ket& k);

Ket op_gdump_fn1(ContextList& context, const Sequence& input_seq, const Sequence& one);

Ket op_gtable(const Superposition& sp, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters);
