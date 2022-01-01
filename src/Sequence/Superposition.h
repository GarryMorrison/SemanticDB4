#pragma once

//
// Created by Garry Morrison on 12/09/2020.
//


// #define SUPERPOSITION 1

#include <unordered_map>
#include <string>
#include <functional>
#include "../KetMap/KetMap.h"
#include "Ket.h"
#include "SuperpositionIter.h"
#include "BaseSequence.h"
#include "../CompoundConstant/CompoundConstant.h"

class Ket;
class SuperpositionIter;
class Sequence;
class ContextList;


class Superposition : public BaseSequence {
private:
    std::unordered_map<ulong, double> sp;
    std::vector<ulong> sort_order;
    ulong old_process_infix_compile(ulong idx1, unsigned int infix_type, ulong idx2) const;  // Deprecated. Remove later!
    ulong process_infix_compile(ulong idx1, unsigned int infix_type, ulong idx2) const;

public:
    Superposition() {};
    ~Superposition() {};
    Superposition(ulong idx);
    Superposition(const std::string& s);
    Superposition(const std::string& s, double v);
    Superposition(ulong idx, double v);
    Superposition(Ket k);
    Superposition(const Superposition& other_sp) : sp(other_sp.sp), sort_order(other_sp.sort_order) {};
    Superposition(const std::vector<ulong>& vec);

    bool operator==(const Superposition& other) const;

    const int type() const { return SUPERPOSITION; };
    const bool is_ket() const { if (sort_order.size() <= 1) { return true; } return false; }
    // const ulong size() const;
    const size_t size() const;
    const std::string to_string() const;
    const std::string to_string(const std::string& prefix) const;
    const std::string readable_display() const;

    Ket to_ket() const;
    Superposition to_sp() const;
    Sequence to_seq() const;

    // BaseSequence* b_add(BaseSequence* bSeq);
    // BaseSequence* b_append(BaseSequence* bSeq);
    std::shared_ptr<BaseSequence> b_add(std::shared_ptr<BaseSequence> bSeq);
    std::shared_ptr<BaseSequence> b_append(std::shared_ptr<BaseSequence> bSeq);

    void add(const ulong idx);
    void add(const ulong idx, const double v);
    void add(const std::string& s);
    void add(const std::string& s, const double v);
    void add(Ket& a);
    void add(const Superposition& a);
    void add(const std::vector<ulong>& vec);
    void multiply(const double d);
    void coeff_sort();
    void ket_sort();
    void natural_sort();
    void sort_by(ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters);
    // void select(const ulong start, const ulong stop);

    void merge(const Superposition& sp2, const std::string& s);
    void merge(const Superposition& sp2);

    void process_infix(unsigned int infix_type, const Superposition& sp2);  // Not sure this is the cleanest way to handle infix operators!
    void insert_range(const Superposition& sp2);

    Superposition operator+(Ket& b);
    Superposition operator+(Superposition& sp);

    // SuperpositionIter:
    Ket get(size_t pos) const;
    SuperpositionIter begin() const;
    SuperpositionIter end() const;

    /*  // Broken with "a non static member reference must be relative to a specific object" error.
    // New iterator, the last one was deprecated!
    struct Iterator  // See here: https://internalpointers.com/post/writing-custom-iterators-modern-cpp
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Ket;
        using pointer = size_t;
        using reference = Ket&;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { ulong ket_idx = sort_order[m_ptr]; double value = sp.at(ket_idx); return Ket(ket_idx, value); }
        // reference operator*() const;
        pointer operator->() { return m_ptr; }
        Iterator& operator++() { m_ptr++; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

    private:
        pointer m_ptr;
    };

    Iterator begin() { return Iterator(0); }
    Iterator end() { return Iterator(sort_order.size()); }
    */

    // A collection of built in operators:
    Superposition shuffle() const;
    double find_value(const Ket& k) const;
    Ket do_you_know() const;
    Ket how_many() const;
    Ket measure_currency() const;
    double find_min_coeff() const;
    double find_max_coeff() const;
    Superposition rescale(const double t) const;
    Superposition rescale() const;
    Superposition normalize(const double t) const;
    Superposition normalize() const;
    Superposition reverse() const;
    Superposition drop() const;
    Superposition drop_below(const double t) const;
    Superposition drop_above(const double t) const;
    Superposition pick(const ulong n) const;
    Ket pick_elt() const;
    Ket weighted_pick_elt() const;
    Superposition select(const int start, const int stop) const;
    Superposition rotate_left(const int n) const;
    Superposition rotate_right(const int n) const;

    Superposition apply_sigmoid(const std::function<double(double)>& sigmoid) const;
    Superposition apply_sigmoid(const std::function<double(double, double)>& sigmoid, const double t) const;
    Superposition apply_sigmoid(const std::function<double(double, double, double)>& sigmoid, const double t1, const double t2) const;
    Superposition apply_compound_sigmoid(const std::function<double(double, const std::vector<std::shared_ptr<CompoundConstant> >)>& fn, std::vector<std::shared_ptr<CompoundConstant> > parameters) const;

    // Nope! This produces "return type "class Sequence" is incomplete"
    // Sequence Compile(ContextList& context) const { return this->to_seq(); };
    // Sequence Compile(ContextList& context) const { Sequence tmp(*this); return tmp; };
    // Sequence Compile(ContextList& context, const ulong label_idx) const { return this->to_seq(); };
    // Sequence Compile(ContextList& context, const std::vector<Sequence>& args) const { return this->to_seq(); };

    Sequence Compile(ContextList& context) const;
    // Sequence Compile(ContextList& context, const ulong label_idx) const;
    // Sequence Compile(ContextList& context, const ulong label_idx, const ulong multi_label_idx) const;
    // Sequence Compile(ContextList& context, const ulong label_idx, const std::vector<Sequence>& args) const;

    Sequence Compile(ContextList& context, const Ket& label_ket) const;
    Sequence Compile(ContextList& context, const Ket& label_ket, const Ket& multi_label_ket) const;
    Sequence Compile(ContextList& context, const Ket& label_ket, const std::vector<Sequence>& args) const;
};

