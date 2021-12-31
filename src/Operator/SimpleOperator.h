#pragma once

//
// Created by Garry Morrison on 13/09/2020.
//


#include <string>
#include "../KetMap/KetMap.h"
#include "../Sequence/Sequence.h"
#include "../Context/ContextList.h"
#include "BaseOperator.h"
#include "NumericOperator.h"

class SimpleOperator : public BaseOperator {
private:
    ulong op_idx;

public:
    SimpleOperator(const ulong idx) : op_idx(idx) { };
    SimpleOperator(const std::string& s) { op_idx = ket_map.get_idx(s); };
    SimpleOperator(const Ket k) {
        auto split_idx = ket_map.get_split_idx(k.label_idx());
        if (split_idx.size() != 2) { op_idx = ket_map.get_idx(""); }
        if (split_idx[0] != ket_map.get_idx("op")) { op_idx = ket_map.get_idx(""); }
        op_idx = split_idx[1];
    }

    const int type() const { return OPSIMPLE; }
    const ulong get_head_op_idx() const { return op_idx; }
    const std::shared_ptr<BaseOperator> get_tail_op() const { return std::make_shared<NumericOperator>(1); }
    const std::string to_string() const { return ket_map.get_str(op_idx); };

    ulong get_idx() const { return op_idx; }  // yeah, a duplicate of get_op_idx(). Tidy later!
    std::string get_str() const { return ket_map.get_str(op_idx); }

    Sequence Compile(NewContext& context, const Sequence& seq) const;
    Sequence Compile(ContextList& context, const Sequence& seq) const;
    // Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx) const;
    // Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx, const ulong multi_label_idx) const;
    // Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx, const std::vector<Sequence>& args) const;

    Sequence Compile(ContextList& context, const Sequence& seq, const Ket& label_ket) const;
    Sequence Compile(ContextList& context, const Sequence& seq, const Ket& label_ket, const Ket& multi_label_ket) const;
    Sequence Compile(ContextList& context, const Sequence& seq, const Ket& label_ket, const std::vector<Sequence>& args) const;

};

