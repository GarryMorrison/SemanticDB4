#pragma once

//
// Created by Garry Morrison on 20/10/2020.
//


// #define MULTILEARNRULE 12

#include <vector>
#include "OperatorWithSequence.h"
#include "LearnRule.h"
#include "BaseSequence.h"
#include "IfElseStatement.h"
#include "ForStatement.h"
#include "WhileStatement.h"

class IfElseStatement;
class ForStatement;
class WhileStatement;


class MultiLearnRule : public BaseSequence {
private:
    std::vector<std::shared_ptr<BaseSequence> > vec_rules;

public:
    MultiLearnRule() {}
    MultiLearnRule(const LearnRule& learn_rule);
    MultiLearnRule(const OperatorWithSequence& operator_with_sequence);
    MultiLearnRule(const IfElseStatement& if_else_statement);
    MultiLearnRule(const ForStatement& for_statement);
    MultiLearnRule(const WhileStatement& while_statement);
    void append(const LearnRule& learn_rule);
    void append(const OperatorWithSequence& operator_with_sequence);
    void append(const IfElseStatement& if_else_statement);
    void append(const ForStatement& for_statement);
    void append(const WhileStatement& while_statement);

    // methods needed to support BaseSequence:
    const int type() const { return MULTILEARNRULE; }
    const bool is_ket() const { return false; }
    const bool is_empty_ket() const { return false; }
    const size_t size() const { return vec_rules.size(); }
    const std::string to_string() const;
    const std::string to_string(const std::string& prefix) const;

    Ket to_ket() const { return Ket(); }  // Do something more interesting with these later!
    Superposition to_sp() const { return Superposition(); }
    Sequence to_seq() const { return Sequence(); }

    std::shared_ptr<BaseSequence> b_add(std::shared_ptr<BaseSequence> bSeq) { return bSeq; }  // Maybe change later!
    std::shared_ptr<BaseSequence> b_append(std::shared_ptr<BaseSequence> bSeq) { return bSeq; }

    Sequence Compile(ContextList& context) const;  // needs filling out
    // Sequence Compile(ContextList& context, const ulong label_idx) const;  // needs filling out
    // Sequence Compile(ContextList& context, const ulong label_idx, const ulong multi_label_idx) const;  // needs filling out
    // Sequence Compile(ContextList& context, const ulong label_idx, const std::vector<Sequence>& args) const; // needs filling out

    Sequence Compile(ContextList& context, const Ket& label_ket) const;
    Sequence Compile(ContextList& context, const Ket& label_ket, const Ket& multi_label_ket) const;
    Sequence Compile(ContextList& context, const Ket& label_ket, const std::vector<Sequence>& args) const;
};
