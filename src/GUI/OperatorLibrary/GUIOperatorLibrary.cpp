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
#include "../Interface/DumpFrame.h"
#include "../Associated/TableDialog.h"


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

	DumpFrame* dump_frame = new DumpFrame(static_cast<wxWindow*>(context.get_window_pointer()), "GUI dump operator output", captured_text);
	return Ket("gdump");
}

Ket op_gtable(const Superposition& sp, ContextList& context, const std::vector<std::shared_ptr<CompoundConstant> >& parameters)
{
    if (sp.is_empty_ket() || parameters.empty()) { return Ket(); }

    // Walk the parameters list:
    std::vector<ulong> operators;
    for (const auto& p : parameters)
    {
        ulong idx = p->get_operator().get_idx();
        operators.push_back(idx);
    }

    // Now invoke it:
    TableDialog* table_frame = new TableDialog(static_cast<wxWindow*>(context.get_window_pointer()), operators, sp, false);
    return Ket("gtable");
}

Ket op_ggraph_fn1(ContextList& context, const Sequence& input_seq, const Sequence& one)
{
    if (input_seq.is_empty_ket() || one.is_empty_ket()) { return Ket(); }
    
    Superposition input_sp = input_seq.to_sp().apply_sigmoid(&clean);
    Superposition operators_sp = one.to_sp();

    ulong star_idx = ket_map.get_idx("*");
    ulong ket_op_idx = ket_map.get_idx("op");
    std::set<ulong> operators;

    std::string dot_file = "digraph G {\n";
    dot_file += "  labelloc=\"t\";\n";
    dot_file += "  label=<<font point-size=\"30\"><u>" + context.get_context_name() + "</u></font>>;\n";
    dot_file += "  node [ shape=Mrecord ]\n";
    unsigned int cluster_idx = 0;
    unsigned int node_idx = 0;
    std::map<std::string, unsigned int> node_label_idx_map;

    for (const Ket& object : input_sp)
    {
        std::string object_label = object.label();
        bool found_rule = false;
        ulong object_idx = object.label_idx();

        // Learn node index for our object:
        if (node_label_idx_map.find(object_label) == node_label_idx_map.end()) {
            node_idx++;
            node_label_idx_map[object_label] = node_idx;
            dot_file += "  " + std::to_string(node_idx) + " [ label=\"" + object_label + "\" ]\n";
        }

        for (const Ket& op : operators_sp)
        {
            std::string op_label = op.label();
            if (op.label_idx() == star_idx)
            {
                std::vector<ulong> supported_operators = context.supported_ops(object_idx);
                for (ulong supported_op_idx : supported_operators)
                {
                    std::string supported_op_label = ket_map.get_str(supported_op_idx);
                    found_rule = true;
                    unsigned int rule_type = context.recall_type(supported_op_idx, object_idx);
                    std::shared_ptr<BaseSequence> rule_value = context.recall(supported_op_idx, object_idx);
                    std::string box_shape;
                    std::string arrowhead_type;
                    std::string RHS_string;
                    Superposition rule_sp;
                    switch (rule_type)
                    {
                    case RULENORMAL: {
                        box_shape = "";
                        arrowhead_type = "";
                        rule_sp = rule_value->to_sp(); // FIXME: Handle sequences better later!
                        break;
                    }
                    case RULESTORED: {
                        box_shape = "shape=box ";
                        arrowhead_type = "arrowhead=box, ";
                        rule_sp = Superposition(rule_value->to_string());
                        break;
                    }
                    case RULEMEMOIZE: {
                        box_shape = "shape=box ";
                        arrowhead_type = "arrowhead=tee, ";
                        rule_sp = Superposition(rule_value->to_string());
                        break;
                    }
                    default:
                        break;
                    }
                    for (const Ket& rule_ket : rule_sp)
                    {
                        RHS_string = rule_ket.label();

                        // Escape chars for Graphviz/dot code:
                        string_replace_all(RHS_string, "|", "\\|");
                        string_replace_all(RHS_string, ">", "&gt;");
                        // string_replace_all(RHS_string, "\n", "\\n");
                        string_replace_all(RHS_string, "\n", "\\l");
                        string_replace_all(RHS_string, "\"", "\\\"");

                        // Now learn them:
                        if (node_label_idx_map.find(RHS_string) == node_label_idx_map.end())
                        {
                            node_idx++;
                            node_label_idx_map[RHS_string] = node_idx;
                            dot_file += "  " + std::to_string(node_idx) + " [ " + box_shape + "label=\"" + RHS_string + "\" ]\n";
                        }
                        dot_file += "  " + std::to_string(node_label_idx_map[object_label]) + " -> " + std::to_string(node_label_idx_map[RHS_string]) + " [ " + arrowhead_type + "label = \"" + supported_op_label + "\" ]\n";
                    }
                }
            }
        }
    }
    dot_file += "}\n";
    std::cout << dot_file;
    return Ket("ggraph");
}