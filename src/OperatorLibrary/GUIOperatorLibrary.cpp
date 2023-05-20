//
// Semantic DB 4
// Created 2023/5/20
// Updated 2023/5/20
// Author Garry Morrison
// License GPL v3
//

#define _CRT_SECURE_NO_WARNINGS  // We need this for the wxwidgets code to compile! Is there a security risk?
#include "GUIOperatorLibrary.h"
#include <wx/msgdlg.h>
#include "../GUI/Interface/DumpFrame.h"

Ket op_gmessage(const Ket& k)  // Our first, test, GUI operator!
{
	wxMessageBox(k.label());
	return k;
}

Ket op_gdump_fn1(ContextList& context, const Sequence& input_seq, const Sequence& one)
{
    Superposition input_sp = input_seq.to_sp().apply_sigmoid(&clean);  // Basically copy and pasted from FunctionOperatorLibrary.cpp version.
    Superposition operators_sp = one.to_sp();
    ulong star_idx = ket_map.get_idx("*");
    ulong ket_op_idx = ket_map.get_idx("op");
    ulong ket_ops_idx = ket_map.get_idx("ops");

	std::stringstream buffer;
	
    for (const Ket& object : input_sp)
    {
        bool found_rule = false;
        ulong object_idx = object.label_idx();
        for (const Ket& op : operators_sp)
        {
            if (op.label_idx() == star_idx)
            {
                std::vector<ulong> operators = context.supported_ops(object_idx);
                for (ulong op_idx : operators)
                {
                    found_rule = true;
                    int rule_type = context.recall_type(op_idx, object_idx);
                    std::shared_ptr<BaseSequence> rule_value = context.recall(op_idx, object_idx);
                    switch (rule_type)
                    {
                    case RULENORMAL: {
                        buffer << ket_map.get_str(op_idx) << " " << object.to_string() << " => " << rule_value->to_string() << "\n";
                        break;
                    }
                    case RULESTORED: {
                        buffer << ket_map.get_str(op_idx) << " " << object.to_string() << " #=> " << rule_value->to_string() << "\n";
                        break;
                    }
                    case RULEMEMOIZE: {
                        buffer << ket_map.get_str(op_idx) << " " << object.to_string() << " !=> " << rule_value->to_string() << "\n";
                        break;
                    }
                    default:
                        break;
                    }
                }
            }
            std::vector<ulong> op_vec = op.label_split_idx();
            if (op_vec.size() != 2)
            {
                continue;
            }
            if (op_vec[0] != ket_op_idx && op_vec[0] != ket_ops_idx)
            {
                continue;
            }
            if (op_vec[0] == ket_op_idx)
            {
                found_rule = true;
                int rule_type = context.recall_type(op_vec[1], object_idx);
                std::shared_ptr<BaseSequence> rule_value = context.recall(op_vec[1], object_idx);
                switch (rule_type)
                {
                case RULENORMAL: {
                    buffer << ket_map.get_str(op_vec[1]) << " " << object.to_string() << " => " << rule_value->to_string() << "\n";
                    break;
                }
                case RULESTORED: {
                    buffer << ket_map.get_str(op_vec[1]) << " " << object.to_string() << " #=> " << rule_value->to_string() << "\n";
                    break;
                }
                case RULEMEMOIZE: {
                    buffer << ket_map.get_str(op_vec[1]) << " " << object.to_string() << " !=> " << rule_value->to_string() << "\n";
                    break;
                }
                default:
                    found_rule = false;
                    break;
                }
            }
            if (op_vec[0] == ket_ops_idx)
            {
                std::vector<SimpleOperator> operators;
                auto string_ops = split(ket_map.get_str(op_vec[1]), " ");
                for (const auto& s : string_ops) {
                    SimpleOperator op(s);
                    operators.push_back(op);
                }
                Sequence seq = object.to_seq();
                for (auto it = operators.rbegin(); it != operators.rend(); ++it) {
                    seq = (*it).Compile(context, seq);
                }
                if (!seq.is_empty_ket())
                {
                    buffer << ket_map.get_str(op_vec[1]) << " " << object.to_string() << " => " << seq.to_string() << "\n";
                    found_rule = true;
                }
            }
        }
        if (found_rule)
        {
            buffer << " \n";  // Weird that we need the space here, but seems that we do!
            found_rule = false;
        }
    }

	std::string captured_text = buffer.str();

	DumpFrame* dump_frame = new DumpFrame(context.get_window_pointer(), "GUI dump operator output", captured_text);
	return Ket("gdump");
}