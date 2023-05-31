#pragma once

//
// Created by Garry Morrison on 13/09/2020.
//

#include <string>
#include "../Sequence/Sequence.h"
#include "../Context/ContextList.h"
#include "BaseOperator.h"


class NumericOperator : public BaseOperator {
private:
    double value;

public:
    NumericOperator(const double d) { value = d; };
    Sequence Compile(NewContext& context, const Sequence& seq) const;
    Sequence Compile(ContextList& context, const Sequence& seq) const;
    // Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx) const;
    // Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx, const ulong multi_label_idx) const;
    // Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx, const std::vector<Sequence>& args) const;

    Sequence Compile(ContextList& context, const Sequence& seq, const Ket& label_ket) const;
    Sequence Compile(ContextList& context, const Sequence& seq, const Ket& label_ket, const Ket& multi_label_ket) const;
    Sequence Compile(ContextList& context, const Sequence& seq, const Ket& label_ket, const std::vector<Sequence>& args) const;

    const int type() const { return OPNUMERIC; }
    const ulong get_head_op_idx() const { return 0; }
    const std::shared_ptr<BaseOperator> get_tail_op() const { return std::make_shared<NumericOperator>(1); }
    const std::string to_string() const;
};
