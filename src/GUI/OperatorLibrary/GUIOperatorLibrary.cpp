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
    
    // Learn requested operators:
    std::set<ulong> requested_operators;
    for (const Ket& op : operators_sp)
    {
        if (op.label_idx() == star_idx)
        {
            requested_operators.clear();
            for (const Ket& k : input_sp)
            {
                std::vector<ulong> supported_ops = context.supported_ops(k.label_idx());
                requested_operators.insert(std::begin(supported_ops), std::end(supported_ops));
            }
            break;
        }
        std::vector<ulong> op_idx_vec = op.label_split_idx();
        if (op_idx_vec.size() != 2)
        {
            continue;
        }
        if (op_idx_vec[0] != ket_op_idx)
        {
            continue;
        }
        requested_operators.insert(op_idx_vec[1]);
    }

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

        /* Shifted down lower, since if we put it here, we learn unwanted nodes when they don't have an operator defined for them.
        // Learn node index for our object:
        if (node_label_idx_map.find(object_label) == node_label_idx_map.end()) {
            node_idx++;
            node_label_idx_map[object_label] = node_idx;
            dot_file += "  " + std::to_string(node_idx) + " [ label=\"" + object_label + "\" ]\n";
        }
        */

        for (ulong requested_op : requested_operators)
        {
            std::string op_label = ket_map.get_str(requested_op);
            found_rule = true;
            unsigned int rule_type = context.recall_type(requested_op, object_idx);
            std::shared_ptr<BaseSequence> rule_value = context.recall(requested_op, object_idx);
            std::string box_shape;
            std::string arrowhead_type;
            std::string RHS_string;
            // Superposition rule_sp;
            Sequence rule_seq;
            switch (rule_type)
            {
            case RULENORMAL: {
                box_shape = "";
                arrowhead_type = "";
                // rule_sp = rule_value->to_sp(); // FIXME: Handle sequences better later!
                rule_seq = rule_value->to_seq();
                break;
            }
            case RULESTORED: {
                box_shape = "shape=box ";
                arrowhead_type = "arrowhead=box, ";
                // rule_sp = Superposition(rule_value->to_string() + "\n");
                rule_seq = Sequence(rule_value->to_string() + "\n");
                break;
            }
            case RULEMEMOIZE: {
                box_shape = "shape=box ";
                arrowhead_type = "arrowhead=tee, ";
                // rule_sp = Superposition(rule_value->to_string() + "\n");
                rule_seq = Sequence(rule_value->to_string() + "\n");
                break;
            }
            default:
                found_rule = false;
                break;
            }
            if (found_rule)
            {
                // Learn node index for our object if it has any valid rules:
                if (node_label_idx_map.find(object_label) == node_label_idx_map.end()) {
                    node_idx++;
                    node_label_idx_map[object_label] = node_idx;
                    dot_file += "  " + std::to_string(node_idx) + " [ label=\"" + object_label + "\" ]\n";
                }

                if (rule_seq.size() == 1)
                {
                    for (const Ket& rule_ket : rule_seq.to_sp())
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
                        dot_file += "  " + std::to_string(node_label_idx_map[object_label]) + " -> " + std::to_string(node_label_idx_map[RHS_string]) + " [ " + arrowhead_type + "label = \"" + op_label + "\" ]\n";
                    }
                }
                else
                {
                    dot_file += "\n  subgraph cluster_" + std::to_string(cluster_idx) + " {\n  label=\"\";\n  rank=max;\n  rankdir=\"LR\"\n  ranksep=\"0.05\"\n";
                    cluster_idx++;
                    std::string first_element;
                    unsigned int current_node_idx = node_idx;
                    for (const auto& sp2 : rule_seq) {
                        std::string current_element = sp2.readable_display();  // Do we need to escape this string for dot?
                        node_idx++;
                        dot_file += "  " + std::to_string(node_idx) + " [ label=\"" + current_element + "\" ]\n";
                    }
                    node_idx = current_node_idx;
                    unsigned int first_element_idx = current_node_idx;
                    bool first_pass = true;
                    for (const auto& sp2 : rule_seq) {
                        node_idx++;
                        if (first_pass) {
                            first_pass = false;
                            first_element_idx = node_idx;
                            dot_file += "  " + std::to_string(first_element_idx);
                        }
                        else {
                            dot_file += " -> " + std::to_string(node_idx);
                        }
                    }
                    dot_file += " [ arrowhead=dot ]\n  }\n  " + std::to_string(node_label_idx_map[object_label]) + " -> " + std::to_string(first_element_idx) +
                        "  [ label=\"" + op_label + "\" ] \n";
                }
            }
        }
    }
    dot_file += "}\n";
    std::cout << dot_file;  // Comment this out later, when we are finished with debugging.

    // Now on to the GUI component of the ggraph operator:
    std::string random_string = generate_random_string(15);
    std::string filename_dot = random_string + ".dot";
    std::string filename_png = random_string + ".png";

    if (!std::filesystem::exists(filename_dot) && !std::filesystem::exists(filename_png))
    {
        wxMessageBox("Graph is about to generate: " + filename_dot);
        wxMessageBox(dot_file);

        bool success = false;
        std::ofstream our_file(filename_dot);
        if (our_file.is_open())
        {
            our_file << dot_file << std::endl;
            our_file.close();
            success = true;
        }
        else
        {
            wxMessageBox("Graph failed to open: " + filename_dot);
        }

        bool image_success = false;
        if (success)  // Convert dot file to a png image:
        {
            wxMessageBox("Graph about to invoke the dot command");
            // Now check if dot is installed:
            int exit_code = std::system("dot --version");
            if (exit_code == 0)
            {
                wxMessageBox("Graphviz is installed");
                // Now create the image:
                // dot -Tpng filename.dot -o outfile.png
                std::string dot_command = "dot -Tpng " + filename_dot + " -o " + filename_png;

                int dot_exit_code = std::system(dot_command.c_str());  // There is no user controllable input, so should be safe to run.
                if (dot_exit_code == 0)
                {
                    wxMessageBox("Graphviz generated an image");
                    image_success = true;

                    // Now try to display it:
                    // ImageFrame* image_frame = new ImageFrame("Graph", filename_png);  // Doesn't work yet!

                    // Try with a full path:
                    std::filesystem::path current_path = std::filesystem::current_path();
                    std::filesystem::path full_filename_png = current_path / filename_png;
                    // ImageFrame* image_frame = new ImageFrame(driver.context.get_context_name(), full_filename_png.string());
                    cImageViewer* image_frame = new cImageViewer(static_cast<wxWindow*>(context.get_window_pointer()), context.get_context_name(), full_filename_png.string());
                }
                else
                {
                    wxMessageBox("Graphviz failed to generate an image");
                }
            }
            else
            {
                wxMessageBox("Graphviz not installed, or not in path");
            }
        }

        if (success)  // Tidy up:
        {
            try
            {
                std::filesystem::remove(filename_dot);
            }
            catch (const std::filesystem::filesystem_error& e)
            {
                (void)e; // To silence C4101 warning.
                wxMessageBox("Graph failed to delete temporary file: " + filename_dot);
            }
        }

        if (image_success)  // Delete the temporary image too:
        {
            try
            {
                std::filesystem::remove(filename_png);
            }
            catch (const std::filesystem::filesystem_error& e)
            {
                (void)e; // To silence C4101 warning.
                wxMessageBox("Graph failed to delete temporary file: " + filename_png);
            }
        }
    }

    return Ket("ggraph");
}