#pragma once

//
// Created by Garry Morrison on 16/09/2020.
//

// #define OPERATORWITHSEQUENCE 10

#define SPLUS 0
#define SMINUS 1
#define SSEQ 2
#define SMERGE 3
#define SMERGE2 4
#define SCOLONMERGE 5

#define OPEQUAL 100
#define OPNOTEQUAL 101
#define OPGREATEREQUAL 102
#define OPGREATER 103
#define OPLESSEQUAL 104
#define OPLESS 105
#define OPAND 106
#define OPOR 107
#define OPPLUS 108
#define OPMINUS 109
#define OPMULT 110
#define OPDIV 111
#define OPMOD 112
#define OPARITHPOWER 113
#define OPRANGE 114


#include <memory>
#include <string>
#include <vector>
#include "BaseSequence.h"
#include "../Operator/BaseOperator.h"
#include "LearnRule.h"

class OperatorWithSequence : public BaseSequence {
private:
    // unsigned int sign;
    // std::shared_ptr<BaseOperator> op;
    // std::shared_ptr<BaseSequence> seq;

    std::vector<unsigned int> sign_vec;
    std::vector<std::shared_ptr<BaseOperator> > op_vec;
    std::vector<std::shared_ptr<BaseSequence> > seq_vec;
    friend class LearnRule;

public:
    OperatorWithSequence() {}
    OperatorWithSequence(const std::shared_ptr<BaseOperator> the_op, const std::shared_ptr<BaseSequence> the_seq) {
        // op = the_op; seq = the_seq; sign = SPLUS;
        sign_vec.push_back(SPLUS);
        op_vec.push_back(the_op);
        seq_vec.push_back(the_seq);
    }

    OperatorWithSequence(const unsigned int the_sign, const std::shared_ptr<BaseOperator> the_op, const std::shared_ptr<BaseSequence> the_seq) {
        // op = the_op; seq = the_seq; sign = the_sign;
        sign_vec.push_back(the_sign);
        op_vec.push_back(the_op);
        seq_vec.push_back(the_seq);
    }

    void append(const std::shared_ptr<BaseOperator> the_op, const std::shared_ptr<BaseSequence> the_seq) {
        sign_vec.push_back(SPLUS);
        op_vec.push_back(the_op);
        seq_vec.push_back(the_seq);
    }

    void append(const unsigned int the_sign, const std::shared_ptr<BaseOperator> the_op, const std::shared_ptr<BaseSequence> the_seq) {
        sign_vec.push_back(the_sign);
        op_vec.push_back(the_op);
        seq_vec.push_back(the_seq);
    }

    void append(const unsigned int the_sign, const OperatorWithSequence& opWithSeq);

    const int type() const { return OPERATORWITHSEQUENCE; };
    const bool is_ket() const { return false; }
    // const ulong size() const { return sign_vec.size(); };
    // const size_t size() const { return sign_vec.size(); };  // Should this be in OperatorWithSequence.cpp?
    const size_t size() const;
    const bool is_empty_ket() const;
    const std::string to_string() const;
    const std::string to_string(const std::string& prefix) const;

    Ket to_ket() const;  // For now, these three just return empty Ket/Superposition/Sequence.
    Superposition to_sp() const;
    Sequence to_seq() const;

    std::shared_ptr<BaseSequence> b_add(std::shared_ptr<BaseSequence> bSeq) { return bSeq; }; // Implement something more interesting later!
    std::shared_ptr<BaseSequence> b_append(std::shared_ptr<BaseSequence> bSeq) { return bSeq; };

    Sequence Compile(ContextList& context) const;
    // Sequence Compile(ContextList& context, const ulong label_idx) const;
    // Sequence Compile(ContextList& context, const ulong label_idx, const ulong multi_label_idx) const;
    // Sequence Compile(ContextList& context, const ulong label_idx, const std::vector<Sequence>& args) const;

    Sequence Compile(ContextList& context, const Ket& label_ket) const;
    Sequence Compile(ContextList& context, const Ket& label_ket, const Ket& multi_label_ket) const;
    Sequence Compile(ContextList& context, const Ket& label_ket, const std::vector<Sequence>& args) const;
};
