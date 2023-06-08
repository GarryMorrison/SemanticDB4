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

    bool verbose_message_box = false;
    std::string dot_file = generate_dot_string(context, input_seq, one);
    if (dot_file.empty()) { return Ket(); }

    if (verbose_message_box)
    {
        std::cout << dot_file;  
    }

    // Now on to the GUI component of the ggraph operator:
    std::string random_string = generate_random_string(15);
    std::string filename_dot = random_string + ".dot";
    std::string filename_png = random_string + ".png";

    if (!std::filesystem::exists(filename_dot) && !std::filesystem::exists(filename_png))
    {
        if (verbose_message_box)
        {
            wxMessageBox("Graph is about to generate: " + filename_dot);
            wxMessageBox(dot_file);
        }

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
            if (verbose_message_box)
            {
                wxMessageBox("Graph about to invoke the dot command");
            }

            // Now check if dot is installed:
            int exit_code = std::system("dot --version");
            if (exit_code == 0)
            {
                if (verbose_message_box)
                {
                    wxMessageBox("Graphviz is installed");
                }
                
                // Now create the image:
                // dot -Tpng filename.dot -o outfile.png
                std::string dot_command = "dot -Tpng " + filename_dot + " -o " + filename_png;

                int dot_exit_code = std::system(dot_command.c_str());  // There is no user controllable input, so should be safe to run.
                if (dot_exit_code == 0)
                {
                    if (verbose_message_box)
                    {
                        wxMessageBox("Graphviz generated an image");
                    }
                    
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
                    if (true || verbose_message_box)  // For now, allow generation of this message.
                    {
                        wxMessageBox("Graphviz failed to generate an image");
                    }
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