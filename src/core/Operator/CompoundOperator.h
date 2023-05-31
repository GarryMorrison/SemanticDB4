#pragma once

//
// Created by Garry Morrison on 13/09/2020.
//


#include <string>
#include <vector>
#include <memory>
#include "../KetMap/KetMap.h"
#include "../Sequence/Sequence.h"
#include "../Context/ContextList.h"
#include "../Context/NewContext.h"
#include "BaseOperator.h"
#include "../CompoundConstant/CompoundConstant.h"
#include "NumericOperator.h"

class CompoundOperator : public BaseOperator {
private:
    ulong op_idx;
    // std::vector<CompoundConstant*> const_seq;
    std::vector<std::shared_ptr<CompoundConstant> > const_vec;

public:
    CompoundOperator(const ulong idx) : op_idx(idx) { };
    CompoundOperator(const std::string& s) { op_idx = ket_map.get_idx(s); };  // Is it safe to use ket_map.get_idx() in a header file??
    CompoundOperator(const ulong idx,
        const std::vector<std::shared_ptr<CompoundConstant> >& input_vec) : op_idx(idx), const_vec(input_vec) { };
    CompoundOperator(const std::string& s,
        const std::vector<std::shared_ptr<CompoundConstant> >& input_vec) : const_vec(input_vec) {
        op_idx = ket_map.get_idx(s);
    };
    CompoundOperator(const ulong idx,
        const std::shared_ptr<CompoundConstant> param0) : op_idx(idx) {
        const_vec.push_back(param0);
    }
    CompoundOperator(const ulong idx,
        const std::shared_ptr<CompoundConstant> param0,
        const std::shared_ptr<CompoundConstant> param1) : op_idx(idx) {
        const_vec.push_back(param0);
        const_vec.push_back(param1);
    }
    CompoundOperator(const ulong idx,
        const std::shared_ptr<CompoundConstant> param0,
        const std::shared_ptr<CompoundConstant> param1,
        const std::shared_ptr<CompoundConstant> param2) : op_idx(idx) {
        const_vec.push_back(param0);
        const_vec.push_back(param1);
        const_vec.push_back(param2);
    }
    CompoundOperator(const ulong idx,
        const std::shared_ptr<CompoundConstant> param0,
        const std::shared_ptr<CompoundConstant> param1,
        const std::shared_ptr<CompoundConstant> param2,
        const std::shared_ptr<CompoundConstant> param3) : op_idx(idx) {
        const_vec.push_back(param0);
        const_vec.push_back(param1);
        const_vec.push_back(param2);
        const_vec.push_back(param3);
    }

    CompoundOperator(const std::string& s,
        const std::shared_ptr<CompoundConstant> param0) {
        op_idx = ket_map.get_idx(s);
        const_vec.push_back(param0);
    }
    CompoundOperator(const std::string& s,
        const std::shared_ptr<CompoundConstant> param0,
        const std::shared_ptr<CompoundConstant> param1) {
        op_idx = ket_map.get_idx(s);
        const_vec.push_back(param0);
        const_vec.push_back(param1);
    }
    CompoundOperator(const std::string& s,
        const std::shared_ptr<CompoundConstant> param0,
        const std::shared_ptr<CompoundConstant> param1,
        const std::shared_ptr<CompoundConstant> param2) {
        op_idx = ket_map.get_idx(s);
        const_vec.push_back(param0);
        const_vec.push_back(param1);
        const_vec.push_back(param2);
    }
    CompoundOperator(const std::string& s,
        const std::shared_ptr<CompoundConstant> param0,
        const std::shared_ptr<CompoundConstant> param1,
        const std::shared_ptr<CompoundConstant> param2,
        const std::shared_ptr<CompoundConstant> param3) {
        op_idx = ket_map.get_idx(s);
        const_vec.push_back(param0);
        const_vec.push_back(param1);
        const_vec.push_back(param2);
        const_vec.push_back(param3);
    }

    // void append(CompoundConstant* const_op);
    void append(std::shared_ptr<CompoundConstant> constant);
    const int type() const { return OPCOMPOUND; }
    const ulong get_head_op_idx() const { return 0; }
    const std::shared_ptr<BaseOperator> get_tail_op() const { return std::make_shared<NumericOperator>(1); }
    const std::string to_string() const;

    Sequence Compile(NewContext& context, const Sequence& seq) const;
    Sequence Compile(ContextList& context, const Sequence& seq) const;
    // Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx) const;
    // Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx, const ulong multi_label_idx) const;
    // Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx, const std::vector<Sequence>& args) const;

    Sequence Compile(ContextList& context, const Sequence& seq, const Ket& label_ket) const;
    Sequence Compile(ContextList& context, const Sequence& seq, const Ket& label_ket, const Ket& multi_label_ket) const;
    Sequence Compile(ContextList& context, const Sequence& seq, const Ket& label_ket, const std::vector<Sequence>& args) const;
};

