//
// Semantic DB 4
// Created 2023/5/16
// Updated 2023/5/16
// Author Garry Morrison
// License GPL v3
//

#pragma once

#include "../Sequence/Sequence.h"
#include "../Sequence/Ket.h"
#include "../Function/misc.h"
#include "../Context/ContextList.h"
#include "../Sequence/BaseSequence.h"
#include "../Operator/BaseOperator.h"
#include "../CompoundConstant/CompoundConstant.h"
#include "../Operator/SimpleOperator.h"
#include <algorithm>
#include <set>

struct TemplateMachine {
	bool has_daughters = false;
	ulong the_node_idx = 0;
	ulong compressed_text_idx = 0;
	size_t size = 0;
	std::vector<std::string> text_vec;
	std::vector<ulong> type_vec;
	std::vector<ulong> value_vec;
	std::string compressed_text;
	int structure_word_count = 0;
	std::set<int> range_stars;
	std::set<int> range_non_stars;
};

struct SentenceStruct {
	bool has_daughters = false;  // Probably don't need this variable
	ulong node_idx = 0;
	ulong raw_sentence_idx = 0;
	size_t size = 0;
	std::vector<std::string> text_vec;
	std::vector<ulong> type_vec;
	std::vector<ulong> value_vec;
};

std::size_t int_vector_to_hash(const std::vector<ulong>& vec);
Superposition op_TM_ngram_partition(const Sequence& input_seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters);

Ket op_TM_sequence_hash(const Sequence& input_seq);
Ket op_TM_ket_hash(const Ket& k);
Ket op_TM_compress_stars(const Ket& k);

Ket op_TM_extract_text(const Sequence& input_seq, const Sequence& one);

// Maybe change type to function, not compound operator?
Ket op_TM_learn_sentences(const Sequence& input_seq, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters);

// Superposition op_TM_generate(const Sequence& input_seq, ContextList& context);
Ket op_TM_generate(const Sequence& input_seq, ContextList& context);
void TM_seed(ContextList& context, const SentenceStruct& sentence, int& max_template_node, std::map<int, std::shared_ptr<TemplateMachine>>& TMs);
void TM_write_templates_to_context(ContextList& context, std::map<int, std::shared_ptr<TemplateMachine>>& TMs);
void TM_populate(ContextList& context, int& max_template_node, std::map<int, std::shared_ptr<TemplateMachine>>& TMs);
