#pragma once

//
// Created by Garry Morrison on 17/09/2020.
//

// #define SELFKET 3

#include "BaseSequence.h"
#include "Ket.h"
#include "Superposition.h"
#include "Sequence.h"
// #include "../Context/NewContext.h"


class SelfKet : public BaseSequence {
private:
    unsigned int idx;
    double value;

public:
    SelfKet() { idx = 1; value = 1; }
    SelfKet(const unsigned int idx2) { idx = idx2; value = 1; }
    SelfKet(const unsigned int idx2, const double d) { idx = idx2; value = d; }
    const int type() const { return SELFKET; }
    const bool is_ket() const { return true; }
    const bool is_empty_ket() const { return false; }
    const std::string to_string() const;
    const std::string to_string(const std::string& prefix) const;
    // const ulong size() const { return 1; }
    const size_t size() const { return 1; }
    void multiply(const double d) { value *= d; }
    Ket to_ket() const;
    Superposition to_sp() const;
    Sequence to_seq() const;
    std::shared_ptr<BaseSequence> b_add(std::shared_ptr<BaseSequence> bSeq);
    std::shared_ptr<BaseSequence> b_append(std::shared_ptr<BaseSequence> bSeq);

    Sequence Compile(ContextList& context) const;
    // Sequence Compile(ContextList& context, const ulong label_idx) const;
    // Sequence Compile(ContextList& context, const ulong label_idx, const ulong multi_label_idx) const;
    // Sequence Compile(ContextList& context, const ulong label_idx, const std::vector<Sequence>& args) const;

    Sequence Compile(ContextList& context, const Ket& label_ket) const;
    Sequence Compile(ContextList& context, const Ket& label_ket, const Ket& multi_label_ket) const;
    Sequence Compile(ContextList& context, const Ket& label_ket, const std::vector<Sequence>& args) const;
};

