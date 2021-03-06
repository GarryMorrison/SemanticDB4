#pragma once

//
// Created by Garry Morrison on 9/10/2020.
//


// #define LEARNRULE 11

#include "../KetMap/KetMap.h"
#include "../Context/Frame.h"
#include "../Operator/OperatorSequence.h"
#include "../Sequence/Sequence.h"
#include "../Context/ContextList.h"
#include "../Sequence/OperatorWithSequence.h"
#include "BaseSequence.h"
// #include "src/Sequence/MultiLearnRule.h"


class LearnRule : public BaseSequence {
private:
    bool _valid_learn_rule;
    ulong _first_op_idx;
    std::shared_ptr<BaseOperator> _ket_op;
    std::shared_ptr<BaseSequence> _ket_like_seq;
    unsigned int _rule_type;
    std::shared_ptr<BaseSequence> _RHS_seq;

public:
    LearnRule(class OperatorWithSequence& head, unsigned int rule_type, class OperatorWithSequence& tail);
    LearnRule(class OperatorWithSequence& head, unsigned int rule_type, class MultiLearnRule& tail);
    bool is_valid_learn_rule() { return _valid_learn_rule; }

    // void Compile(ContextList &context); We need it to return Sequence instead.

    // methods needed to support BaseSequence:
    const int type() const { return LEARNRULE; }
    const bool is_ket() const { return false; }
    const bool is_empty_ket() const { return false; }
    const size_t size() const { return 1; }
    const std::string to_string() const;
    const std::string to_string(const std::string& prefix) const;

    Ket to_ket() const { return Ket(); }  // Do something more interesting with these later!
    Superposition to_sp() const { return Superposition(); }
    Sequence to_seq() const { return Sequence(); }

    std::shared_ptr<BaseSequence> b_add(std::shared_ptr<BaseSequence> bSeq) { return bSeq; }  // Maybe change later!
    std::shared_ptr<BaseSequence> b_append(std::shared_ptr<BaseSequence> bSeq) { return bSeq; }

    Sequence Compile(ContextList& context) const;
    // Sequence Compile(ContextList& context, const ulong label_idx) const;  // needs filling out
    // Sequence Compile(ContextList& context, const ulong label_idx, const ulong multi_label_idx) const;
    // Sequence Compile(ContextList& context, const ulong label_idx, const std::vector<Sequence>& args) const;

    Sequence Compile(ContextList& context, const Ket& label_ket) const;
    Sequence Compile(ContextList& context, const Ket& label_ket, const Ket& multi_label_ket) const;
    Sequence Compile(ContextList& context, const Ket& label_ket, const std::vector<Sequence>& args) const;
};

