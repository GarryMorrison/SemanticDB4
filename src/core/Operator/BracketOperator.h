#pragma once

//
// Created by Garry Morrison on 13/09/2020.
//


#include <string>
#include <memory>
#include "OperatorSequence.h"
#include "BaseOperator.h"
#include "NumericOperator.h"

class BracketOperator : public BaseOperator {
private:
    std::vector<unsigned int> sign_vec;
    std::vector<OperatorSequence> op_seq_vec;

public:
    BracketOperator(OperatorSequence& op_seq) { sign_vec.push_back(SPLUS); op_seq_vec.push_back(op_seq); }
    BracketOperator(unsigned int type, OperatorSequence& op_seq) { sign_vec.push_back(type); op_seq_vec.push_back(op_seq); }
    BracketOperator(BracketOperator& b_operator) : sign_vec(b_operator.sign_vec), op_seq_vec(b_operator.op_seq_vec) { }
    void append(OperatorSequence& op_seq) { sign_vec.push_back(SPLUS); op_seq_vec.push_back(op_seq); }
    void append(unsigned int type, OperatorSequence& op_seq) { sign_vec.push_back(type); op_seq_vec.push_back(op_seq); }

    Sequence Compile(NewContext& context, const Sequence& seq) const;
    Sequence Compile(ContextList& context, const Sequence& seq) const;
    // Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx) const;
    // Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx, const ulong multi_label_idx) const;
    // Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx, const std::vector<Sequence>& args) const;

    Sequence Compile(ContextList& context, const Sequence& seq, const Ket& label_ket) const;
    Sequence Compile(ContextList& context, const Sequence& seq, const Ket& label_ket, const Ket& multi_label_ket) const;
    Sequence Compile(ContextList& context, const Sequence& seq, const Ket& label_ket, const std::vector<Sequence>& args) const;

    const int type() const { return OPBRACKET; }
    const ulong get_head_op_idx() const { return 0; }
    const std::shared_ptr<BaseOperator> get_tail_op() const { return std::make_shared<NumericOperator>(1); }
    const std::string to_string() const;

};
