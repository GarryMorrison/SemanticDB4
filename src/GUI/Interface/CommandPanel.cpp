//
// Semantic DB 4
// Created 2021/12/28
// Updated 2022/1/22
// Author Garry Morrison
// License GPL v3
//

#include "CommandPanel.h"
extern SDB::Driver driver;

CommandPanel::CommandPanel(wxPanel* parent, wxWindowID id)
    : wxPanel(parent, id, wxDefaultPosition, wxSize(400, 300), 0)
{
    // m_command_text = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(600, 200), wxTE_MULTILINE);
    // m_command_results = new wxRichTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(600, 400), wxTE_MULTILINE | wxTE_READONLY);
    m_command_text = new wxStyledTextCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(600, 200), wxTE_MULTILINE);
    m_command_text->SetCaretLineBackground(*wxLIGHT_GREY);
    // m_command_text->SetCaretLineBackground(wxColour(0,0,100));
    m_command_text->SetCaretLineVisible(true);
    // m_command_text->SetSelBackground(true, *wxBLUE);
    m_command_text->SetSelForeground(true, *wxBLUE);

    m_default_attr = new wxTextAttr();
    m_default_attr->SetFontFamily(wxFONTFAMILY_DEFAULT);  // Not sure what font family to set here.
    m_default_attr->SetFont(m_default_attr->GetFont());
    // m_command_text->StyleSetFont(0, m_default_attr->GetFont());  // At least be consistant with the same font after clicking and unclicking monospace font.

    m_mono_attr = new wxTextAttr();
    m_mono_attr->SetFontFamily(wxFONTFAMILY_TELETYPE);
    m_mono_attr->SetFont(m_mono_attr->GetFont());


    if (m_use_command_line_numbers)
    {
        m_command_text->SetMarginType(1, wxSTC_MARGIN_NUMBER); // Set margin to be numbers.
    }
    else
    {
        m_command_text->SetMarginType(1, wxSTC_MARGIN_SYMBOL); // Switch off numbers.
    }

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
    hbox1->Add(new wxStaticText(this, wxID_ANY, "Command", wxDefaultPosition, wxDefaultSize), wxSizerFlags(0).Left().Border(wxALL, 10));
    hbox1->AddSpacer(10);

    wxArrayString context_list;  // Later wire in ContextList, for now just some dummy values.
    for (const auto& name : driver.context.get_context_names())  // How dynamically update this when new context is generated by a run command??
    {
        context_list.Add(name);
    }
    m_context_selector = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, context_list);
    m_context_selector->SetSelection(0);
    hbox1->Add(new wxStaticText(this, wxID_ANY, "Context", wxDefaultPosition, wxDefaultSize), wxSizerFlags(0).Left().Border(wxALL, 10));
    hbox1->Add(m_context_selector, wxSizerFlags(0).Left().Border(wxALL, 10));
    hbox1->AddSpacer(10);

    m_command_monospace_checkbox = new wxCheckBox(this, wxID_ANY, "monospace");
    m_command_monospace_checkbox->SetValue(m_use_command_monospace);  // If the default value is true, we need to set the font to monospace on startup!
    if (m_use_command_monospace)
    {
        m_command_text->StyleSetFont(0, m_mono_attr->GetFont());  // Switch on monospace font.
    }
    hbox1->Add(m_command_monospace_checkbox, wxSizerFlags(0).Left().Border(wxTOP | wxBOTTOM, 10));
    hbox1->AddSpacer(10);

    m_command_line_numbers_checkbox = new wxCheckBox(this, wxID_ANY, "line numbers");
    m_command_line_numbers_checkbox->SetValue(m_use_command_line_numbers);
    hbox1->Add(m_command_line_numbers_checkbox, wxSizerFlags(0).Left().Border(wxTOP | wxBOTTOM, 10));
    vbox->Add(hbox1);

    wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxButton* run_button = new wxButton(this, ID_Command_Run, "Run");
    wxButton* run_all_button = new wxButton(this, ID_Command_Run_All, "Run All");
    wxButton* clear_button = new wxButton(this, ID_Command_Clear, "Clear");
    wxButton* dump_button = new wxButton(this, ID_Command_Dump, "Dump");
    wxButton* save_as_button = new wxButton(this, ID_Command_Save_As, "Save As");
    wxButton* graph_button = new wxButton(this, ID_Command_Graph, "Graph");
    wxButton* reset_context_button = new wxButton(this, ID_Command_Reset_Context, "Reset Context");
    wxButton* reset_all_button = new wxButton(this, ID_Command_Reset_All, "Reset All");
    hbox2->AddSpacer(10);
    hbox2->Add(run_button, wxSizerFlags(0).Left().Border(wxTOP | wxBOTTOM, 10));
    hbox2->Add(run_all_button, wxSizerFlags(0).Left().Border(wxTOP | wxBOTTOM, 10));
    hbox2->Add(clear_button, wxSizerFlags(0).Left().Border(wxTOP | wxBOTTOM, 10));
    hbox2->AddSpacer(10);
    hbox2->Add(dump_button, wxSizerFlags(0).Left().Border(wxTOP | wxBOTTOM, 10));
    hbox2->Add(save_as_button, wxSizerFlags(0).Left().Border(wxTOP | wxBOTTOM, 10));
    hbox2->Add(graph_button, wxSizerFlags(0).Left().Border(wxTOP | wxBOTTOM, 10));
    hbox2->Add(reset_context_button, wxSizerFlags(0).Left().Border(wxTOP | wxBOTTOM, 10));
    hbox2->Add(reset_all_button, wxSizerFlags(0).Left().Border(wxTOP | wxBOTTOM, 10));
    vbox->Add(hbox2);

    vbox->Add(m_command_text, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
    vbox->AddSpacer(10);

    wxBoxSizer* hbox3 = new wxBoxSizer(wxHORIZONTAL);
    hbox3->Add(new wxStaticText(this, wxID_ANY, "Result", wxDefaultPosition, wxDefaultSize), wxSizerFlags(0).Left().Border(wxALL, 10));
    wxCheckBox* active_results_checkbox = new wxCheckBox(this, wxID_ANY, "Active text");
    active_results_checkbox->SetValue(m_use_active_text);
    wxButton* insert_result_new_line_button = new wxButton(this, ID_Command_Result_Insert_New_Line, "Insert New Line");
    wxButton* insert_result_line_button = new wxButton(this, ID_Command_Result_Insert_Line, "Insert Line");
    wxButton* clear_results_button = new wxButton(this, ID_Command_Clear_Results, "Clear");
    wxCheckBox* insert_result_line_checkbox = new wxCheckBox(this, wxID_ANY, "Auto insert line");
    insert_result_line_checkbox->SetValue(m_auto_insert_new_line);
    hbox3->AddSpacer(10);
    hbox3->Add(active_results_checkbox, wxSizerFlags(0).Left().Border(wxTOP | wxBOTTOM, 10));
    hbox3->AddSpacer(10);
    hbox3->Add(insert_result_new_line_button, wxSizerFlags(0).Left().Border(wxTOP | wxBOTTOM, 10));
    hbox3->AddSpacer(10);
    hbox3->Add(insert_result_line_button, wxSizerFlags(0).Left().Border(wxTOP | wxBOTTOM, 10));
    hbox3->AddSpacer(10);
    hbox3->Add(insert_result_line_checkbox, wxSizerFlags(0).Left().Border(wxTOP | wxBOTTOM, 10));
    hbox3->AddSpacer(10);
    hbox3->Add(clear_results_button, wxSizerFlags(0).Left().Border(wxTOP | wxBOTTOM, 10));
    vbox->Add(hbox3);

    // vbox->Add(m_command_results, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
    m_command_result_canvas = new ResultCanvas(this, wxID_ANY, wxDefaultPosition, wxSize(600, 400));
    vbox->Add(m_command_result_canvas, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
    vbox->AddSpacer(10);

    m_timer_line = new wxStaticText(this, wxID_ANY, "Time taken: 0", wxDefaultPosition, wxDefaultSize);
    vbox->Add(m_timer_line, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT | wxBOTTOM, 10));


    SetSizerAndFit(vbox);

    m_parent = parent;

    // m_command_text->Bind(wxEVT_TEXT, &CommandPanel::OnInsertText, m_command_text, ID_Command_Insert_Text);
    // m_command_text->Bind(wxEVT_KEY_DOWN, &CommandPanel::OnInsertText, this, ID_Command_Insert_Text);
    if (!m_command_text)
    {
        wxMessageBox("panel m_command_text is null");
        return;
    }
    // m_command_text->Connect(wxEVT_KEY_UP, wxKeyEventHandler(CommandPanel::OnInsertText));
    // m_command_text->Connect(ID_Command_Insert_Text, wxEVT_KEY_UP, wxKeyEventHandler(CommandPanel::OnInsertText));
    // m_command_text->Bind(wxEVT_KEY_UP, wxKeyEventHandler(CommandPanel::OnInsertText), m_command_text->GetParent(), ID_Command_Insert_Text);
    m_command_text->Bind(wxEVT_KEY_DOWN, &CommandPanel::OnKeyDown, this);
    // m_command_result_canvas->Bind(wxEVT_RIGHT_DOWN, &CommandPanel::OnRightMouseDown, this);
    // m_command_result_canvas->Bind(wxEVT_MOTION, &CommandPanel::OnRightMouseDown, this);

    m_context_selector->Bind(wxEVT_CHOICE, &CommandPanel::OnContextSelect, this);

    run_button->Bind(wxEVT_BUTTON, &CommandPanel::OnRunButtonDown, this);
    run_all_button->Bind(wxEVT_BUTTON, &CommandPanel::OnRunAllButtonDown, this);
    clear_button->Bind(wxEVT_BUTTON, &CommandPanel::OnClearButtonDown, this);
    dump_button->Bind(wxEVT_BUTTON, &CommandPanel::OnDumpButtonDown, this);
    save_as_button->Bind(wxEVT_BUTTON, &CommandPanel::OnSaveAsButtonDown, this);
    graph_button->Bind(wxEVT_BUTTON, &CommandPanel::OnGraphButtonDown, this);
    reset_context_button->Bind(wxEVT_BUTTON, &CommandPanel::OnResetContextButtonDown, this);
    reset_all_button->Bind(wxEVT_BUTTON, &CommandPanel::OnResetAllButtonDown, this);

    m_command_monospace_checkbox->Bind(wxEVT_CHECKBOX, &CommandPanel::OnUseMonospaceCheckBox, this);
    m_command_line_numbers_checkbox->Bind(wxEVT_CHECKBOX, &CommandPanel::OnUseLineNumbersCheckBox, this);

    insert_result_new_line_button->Bind(wxEVT_BUTTON, &CommandPanel::OnInsertNewLineButtonDown, this);
    insert_result_line_button->Bind(wxEVT_BUTTON, &CommandPanel::OnInsertLineButtonDown, this);
    clear_results_button->Bind(wxEVT_BUTTON, &CommandPanel::OnClearResultsButtonDown, this);
    insert_result_line_checkbox->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent& event) {
        m_auto_insert_new_line = insert_result_line_checkbox->GetValue();
        });
    active_results_checkbox->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent& event) {
        m_use_active_text = active_results_checkbox->GetValue();
        });

}

void CommandPanel::OnKeyDown(wxKeyEvent& event)
{
    if (!m_command_text)
    {
        wxMessageBox("insert text m_command_text is empty");

        return;
    }

    int key_code = event.GetKeyCode();
    switch (key_code) {
    case 13: {  // Handle enter, and shift enter:
        if (event.ShiftDown())
        {
            // wxMessageBox("Shift enter pressed ... ");
            // wxString the_command = m_command_text->GetLineText(m_current_line);  // Do something more interesting here later! Check for valid line too.
            wxString the_command = m_command_text->GetCurLine();
            // wxString the_command = m_command_text->GetLine(m_current_line - 1); // GotoLine seems to be 1 based, GetLine() 0 based ....
            Timer_ms the_timer;

            if (m_use_active_text)
            {
                m_command_result_canvas->AppendActiveText(the_command, AGENT_PROMPT, true);
                // std::vector<std::string> vect_str = split(the_command.ToStdString(), "=> ");  // Just a dummy until we wire in the backend code.
                // m_command_result_canvas->AppendActiveText(vect_str.back(), "", false);
                // bool parse_success = driver.parse_string(the_command.ToStdString() + "\n");  // wxString vs std::string again!!
                std::stringstream buffer;
                std::streambuf* old_buffer = std::cout.rdbuf(buffer.rdbuf());
                driver.result.clear();
                bool parse_success = driver.parse_string(the_command.ToStdString() + "\n");  // wxString vs std::string again!!
                std::string captured_text = buffer.str();
                std::cout.rdbuf(old_buffer);
                m_command_result_canvas->AppendMultiLineText(captured_text, false, RC_OBJECT_NONE, true);
                if (!driver.result.is_empty_ket())
                {
                    m_command_result_canvas->AppendActiveText(driver.result.to_string());
                }
                if (!parse_success)  // Should we shift this to up higher?
                {
                    wxMessageBox("Parse failed for command: " + the_command);
                }
                if (m_auto_insert_new_line)
                {
                    m_command_result_canvas->AppendLine();
                }
                // m_command_result_canvas->AppendNewLine();  // For now AppendActiveText inserts it's own new lines. Maybe change later.
            }
            else
            {
                m_command_result_canvas->AppendText(AGENT_PROMPT, false);
                m_command_result_canvas->AppendText(the_command, false);
                m_command_result_canvas->AppendNewLine();
                // std::vector<std::string> vect_str = split(the_command.ToStdString(), "=> ");  // Just a dummy until we wire in the backend code.
                // m_command_result_canvas->AppendNewLine();
                // m_command_result_canvas->AppendText(vect_str.back(), false);
                std::stringstream buffer;
                std::streambuf* old_buffer = std::cout.rdbuf(buffer.rdbuf());
                driver.result.clear();
                bool parse_success = driver.parse_string(the_command.ToStdString() + "\n");  // wxString vs std::string again!!
                std::string captured_text = buffer.str();
                std::cout.rdbuf(old_buffer);
                m_command_result_canvas->AppendMultiLineText(captured_text, false, RC_OBJECT_NONE, true);
                if (!driver.result.is_empty_ket())
                {
                    m_command_result_canvas->AppendText(driver.result.to_string());
                }
                if (m_auto_insert_new_line)
                {
                    m_command_result_canvas->AppendLine();
                }
            }

            the_timer.Stop();
            m_run_time = the_timer.GetTime();
            m_timer_line->SetLabel("Time taken: " + display_time(m_run_time));
        }
        /*
        else
        {

            // wxMessageBox("Enter key pressed ... ");
            m_command_text->WriteText("\n");
            m_current_line++;  // Handle cursor movements later too! And mouse movements!
            m_command_text->GotoLine(m_current_line);
        }
        */
        if (!event.ShiftDown())
        {
            event.Skip();
        }
        break;
    }
    case '\\': {
        if (event.ShiftDown())
        {
            if (m_command_text->GetCurrentPos() > 0)
            {
                char local_char1 = m_command_text->GetCharAt(m_command_text->GetCurrentPos() - 1);
                char local_char2 = m_command_text->GetCharAt(m_command_text->GetCurrentPos());
                if (m_inside_ket && local_char1 == '|' && local_char2 == '>')
                {
                    m_command_text->DeleteRange(m_command_text->GetCurrentPos(), 1);
                    m_command_text->WriteText("| ");
                }
                else if (local_char1 == '|')
                {
                    m_command_text->WriteText("| ");
                }
                else
                {
                    m_command_text->WriteText("|");
                }
            }
            else
            {
                m_command_text->WriteText("|> ");  // Need to check for || case though ... Check previous char was also '|', then clean up the '> ' text.
                int current_pos = m_command_text->GetCurrentPos();
                m_command_text->GotoPos(current_pos - 2);
                m_inside_ket = true;  // Need to change the value of this bool in a bunch of other places too! Eg, insert known ket menu ...
            }
        }
        else
        {
            m_command_text->WriteText("\\");
        }
        break;
    }
    case '[': {
        if (event.ShiftDown())
        {
            if (m_inside_ket)
            {
                m_command_text->WriteText("{");
            }
            else
            {
                m_command_text->WriteText("{} ");
                m_command_text->GotoPos(m_command_text->GetCurrentPos() - 2);
            }
        }
        else
        {
            if (m_inside_ket)
            {
                m_command_text->WriteText("[");
            }
            else
            {
                m_command_text->WriteText("[] ");
                m_command_text->GotoPos(m_command_text->GetCurrentPos() - 2);
            }
        }
        break;
    }
    case ']': {
        if (event.ShiftDown())
        {
            m_command_text->WriteText("}");
        }
        else
        {
            m_command_text->WriteText("]");
        }
        break;
    }
    case '9': {
        if (event.ShiftDown())
        {
            if (m_inside_ket)
            {
                m_command_text->WriteText("(");
            }
            else
            {
                m_command_text->WriteText("() ");
                m_command_text->GotoPos(m_command_text->GetCurrentPos() - 2);
            }
        }
        else
        {
            m_command_text->WriteText("9");
        }
        break;
    }
    case '0': {
        if (event.ShiftDown())
        {
            m_command_text->WriteText(")");
        }
        else
        {
            m_command_text->WriteText("0");
        }
        break;
    }
    case '\'': {
        if (event.ShiftDown())
        {
            if (m_inside_ket)
            {
                m_command_text->WriteText("\"");
            }
            else
            {
                m_command_text->WriteText("\"\"");
                m_command_text->GotoPos(m_command_text->GetCurrentPos() - 1);
            }
        }
        else
        {
            m_command_text->WriteText("\'");
        }
        break;
    }
    case ';': {
        if (event.ShiftDown())
        {
            m_command_text->WriteText(":");
        }
        else
        {
            m_command_text->WriteText(";");
        }
        break;
    }
    case '/': {
        if (event.ShiftDown())
        {
            m_command_text->WriteText("?");
        }
        else
        {
            m_command_text->WriteText("/");
        }
        break;
    }
    case 306: {  // Ignore shift key press.
        break;
    }
    case 32: {  // Handle space key press.
        m_command_text->WriteText(" ");
        break;
    }
    case 312: {  // Handle end key press:  // Currently jumps to first line ... Fix!
        /*
        m_command_text->GotoLine(m_current_line);  // Is this correct?
        wxString wxs = m_command_text->GetCurLine();
        int line_len = wxs.Length();
        m_command_text->GotoPos(line_len);
        m_command_text->GotoLine(m_current_line);
        */
        m_inside_ket = false;
        event.Skip();
        // wxMessageBox("End key pressed");
        // int end_pos = m_command_text->GetAnchor();
        // m_command_text->GotoPos(end_pos);
        break;
    }
    case 313: {  // Handle home key press:
        // m_command_text->Home();
        event.Skip();
        break;
    }
    case 314: {  // Handle left cursor press:
        // m_command_text->GotoPos(m_command_text->GetCurrentPos() - 1);
        int local_char = m_command_text->GetCharAt(m_command_text->GetCurrentPos() - 1);
        if (local_char == '|')
        {
            // wxMessageBox("local char is ket start");
            m_inside_ket = false;
        }
        if (local_char == '>')
        {
            int prev_char = m_command_text->GetCharAt(m_command_text->GetCurrentPos() - 2);
            if (prev_char == '=')
            {
                // wxMessageBox("local char is learn rule end");  // Probably need something a bit smarter! Eg, if have the ket |bah something => Is this even a valid ket?
            }
            else
            {
                // wxMessageBox("local char is ket end");
                m_inside_ket = true;
            }
        }
        event.Skip();
        break;
    }
    case 316: {  // Handle right cursor press:
        if (event.ShiftDown())
        {
            if (m_current_position == -1) {
                m_current_position = m_command_text->GetCurrentPos();  // We need to reset m_current_position to -1 later.
            }
            m_command_text->SetSelection(m_current_position, m_command_text->GetCurrentPos() + 1);
            // event.Skip(); // Do we need this here?
        }
        else
        {
            // m_command_text->GotoPos(m_command_text->GetCurrentPos() + 1);
            event.Skip();
        }
        int local_char = m_command_text->GetCharAt(m_command_text->GetCurrentPos());
        if (local_char == '|')  // Convert this to a switch statement.
        {
            // wxMessageBox("local char is ket start");
            m_inside_ket = true;
        }
        if (local_char == '>')
        {
            int prev_char = m_command_text->GetCharAt(m_command_text->GetCurrentPos() - 1);
            if (prev_char == '=')
            {
                // wxMessageBox("local char is learn rule end");  // Probably need something a bit smarter! Eg, if have the ket |bah something => Is this even a valid ket?
            }
            else
            {
                // wxMessageBox("local char is ket end");
                m_inside_ket = false;
            }
        }
        if (local_char == '=') {
            int next_char = m_command_text->GetCharAt(m_command_text->GetCurrentPos());
            if (next_char == '>') {
                // wxMessageBox("local char is learn rule start");
            }
        }
        break;
    }
    case 315: {  // Handle up cursor press:  // Handle multiple line selection?
        /*
        if (m_current_line > 0)
        {
            m_current_line--;
            m_command_text->GotoLine(m_current_line);
        }
        */
        event.Skip();
        break;
    }
    case 317: {  // Handle down cursor press:
        /*
        m_current_line++;  // Need a check that we aren't past the bottom of our text.
            m_command_text->GotoLine(m_current_line);
        */
        event.Skip();
        break;
    }
    case 8: {  // Handle backspace char press:
        m_command_text->DeleteBack();
        m_current_position = -1;
        break;
    }
    case 127: {  // Handle del char press:
        m_command_text->DeleteBack();
        m_current_position = -1;
        break;
    }
    case 61: {  // Handle = char press:
        if (event.ShiftDown())
        {
            if (!m_inside_ket && !m_line_has_learn_rule[m_current_line])
            {
                m_command_text->WriteText("+=> ");  // Need to handle == infix operator later. Also, need m_inside_ket bool.
                m_line_has_learn_rule[m_current_line] = true;
            }
            else
            {
                m_command_text->WriteText("+");
            }
        }
        else if (!m_inside_ket && !m_line_has_learn_rule[m_current_line])
        {
            m_command_text->WriteText("=> ");  // Need to handle == infix operator later. Also, need m_inside_ket bool.
            m_line_has_learn_rule[m_current_line] = true;
        }
        else
        {
            m_command_text->WriteText("=");
        }
        break;
    }
    case 45: {
        if (event.ShiftDown())
        {
            m_command_text->WriteText("_");
        }
        else
        {
            m_command_text->WriteText("-");
        }
        break;
    }
    case '1': {
        if (event.ShiftDown())
        {
            if (!m_inside_ket && !m_line_has_learn_rule[m_current_line])
            {
                m_command_text->WriteText("!=> ");
                m_line_has_learn_rule[m_current_line] = true;
            }
            else
            {
                m_command_text->WriteText("!");
            }
        }
        else
        {
            m_command_text->WriteText("1");
        }
        break;
    }
    case '3': {
        if (event.ShiftDown())
        {
            if (!m_inside_ket && !m_line_has_learn_rule[m_current_line])
            {
                m_command_text->WriteText("#=> ");
                m_line_has_learn_rule[m_current_line] = true;
            }
            else
            {
                m_command_text->WriteText("#");
            }
        }
        else
        {
            m_command_text->WriteText("3");
        }
        break;
    }
    case ',': {
        if (event.ShiftDown())
        {
            m_command_text->WriteText("<");
        }
        else
        {
            m_command_text->WriteText(",");  // Maybe if inside a compound operator, append ", "?
        }
        break;
    }
    case '.': {
        if (event.ShiftDown())
        {
            m_command_text->WriteText(">");
        }
        else
        {
            if (false && !m_inside_ket && !m_line_has_learn_rule[m_current_line])  // Disable for now, because of conflicts with .. and decimals 3.9
            {
                m_command_text->WriteText(".=> ");
                m_line_has_learn_rule[m_current_line] = true;
            }
            else
            {
                m_command_text->WriteText(".");
            }
        }
        break;
    }
    case '6': {
        if (event.ShiftDown())
        {
            m_command_text->WriteText("^");
        }
        else
        {
            m_command_text->WriteText("6");
        }
        break;
    }
    case '8': {
        if (event.ShiftDown())
        {
            m_command_text->WriteText("*");
        }
        else
        {
            m_command_text->WriteText("8");
        }
        break;
    }
    default: {
        if (key_code >= '0' && key_code <= '9')  // Handle number chars, if not already handled.
        {
            wxString c(static_cast<char>(key_code));
            m_command_text->WriteText(c);
            break;
        }
        else if (key_code >= 'A' && key_code <= 'Z') // Handle letter chars.
        {
            if (!event.ShiftDown())
            {
                wxString c(static_cast<char>(key_code));
                m_command_text->WriteText(c.Lower());
                break;
            }
            else if (event.ShiftDown())
            {
                // wxMessageBox("Upper char");
                //wxMessageBox(wxString::Format("Key ID: %d", event.GetKeyCode()));
                wxString c(static_cast<char>(key_code));
                m_command_text->WriteText(c);
                break;
            }
        }
        else
        {
            wxMessageBox(wxString::Format("Key ID: %d", event.GetKeyCode()));  // Show key code id of unknown keys.
            break;
        }
    }
    }
}

void CommandPanel::OnLeftMouseDown(wxStyledTextEvent& event)  // Nope. Is never invoked.
{
    event.Skip();
    if (true || event.GetId() == ID_Command_Left_Click)  // Nope. Is never invoked.
    {
        wxMessageBox("Left mouse click");
    }
    // event.Skip();
}

void CommandPanel::OnRightMouseDown(wxMouseEvent& event)  // Should this be in CommandPanel or ResultCanvas??
{
    long x = 0;
    long y = 0;
    event.GetPosition(&x, &y);
    // int pos = m_command_text->Pos
    // int pos = m_command_text->PositionFromPoint(wxPoint(x, y));
    // wxMessageBox(wxString::Format("Right mouse click, x = %d, y = %d", x, y));
    // wxMessageBox(wxString::Format("Right mouse click, pos = %s", pos));
    m_command_result_canvas->SetMousePosition(wxPoint(x, y));
    m_command_result_canvas->Refresh();
    event.Skip();
}


void CommandPanel::OnRunButtonDown(wxCommandEvent& event)
{
    wxString the_command = m_command_text->GetCurLine();
    Timer_ms the_timer;
    if (m_use_active_text)
    {
        m_command_result_canvas->AppendActiveText(the_command, AGENT_PROMPT, true);
        std::stringstream buffer;
        std::streambuf* old_buffer = std::cout.rdbuf(buffer.rdbuf());
        driver.result.clear();
        driver.context.set_window_pointer(this);
        bool parse_success = driver.parse_string(the_command.ToStdString() + "\n");  // wxString vs std::string again!!
        std::string captured_text = buffer.str();
        std::cout.rdbuf(old_buffer);
        m_command_result_canvas->AppendMultiLineText(captured_text, false, RC_OBJECT_NONE, true);
        if (!driver.result.is_empty_ket())
        {
            m_command_result_canvas->AppendActiveText(driver.result.to_string());
        }
        // m_command_result_canvas->AppendNewLine();
        // wxMessageBox("Captured text:\n" + captured_text);
        if (!parse_success)
        {
            wxMessageBox("Parse failed for command: " + the_command);
        }
        if (m_auto_insert_new_line)
        {
            m_command_result_canvas->AppendLine();
        }
        // m_command_result_canvas->AppendNewLine();  // For now AppendActiveText inserts it's own new lines. Maybe change later.
    }
    else
    {
        m_command_result_canvas->AppendText(AGENT_PROMPT, false);
        m_command_result_canvas->AppendText(the_command, false);
        std::stringstream buffer;
        std::streambuf* old_buffer = std::cout.rdbuf(buffer.rdbuf());
        driver.result.clear();
        driver.context.set_window_pointer(this);
        bool parse_success = driver.parse_string(the_command.ToStdString() + "\n");  // wxString vs std::string again!!
        std::string captured_text = buffer.str();
        std::cout.rdbuf(old_buffer);
        m_command_result_canvas->AppendNewLine();
        m_command_result_canvas->AppendMultiLineText(captured_text, false, RC_OBJECT_NONE, true);
        if (!driver.result.is_empty_ket())
        {
            m_command_result_canvas->AppendText(driver.result.to_string());
        }
        if (!parse_success)
        {
            wxMessageBox("Parse failed for command: " + the_command);
        }
        if (m_auto_insert_new_line)
        {
            m_command_result_canvas->AppendLine();
        }
    }
    the_timer.Stop();
    m_run_time = the_timer.GetTime();
    m_timer_line->SetLabel("Time taken: " + display_time(m_run_time));
    UpdateContextSelector();
}

void CommandPanel::OnRunAllButtonDown(wxCommandEvent& event)
{
    wxString the_command;
    Timer_ms the_timer;
    if (m_use_active_text)
    {
        for (int idx = 0; idx < m_command_text->GetLineCount(); idx++)
        {
            the_command = m_command_text->GetLine(idx);
            m_command_result_canvas->AppendActiveText(the_command, AGENT_PROMPT, true);

            std::stringstream buffer;
            std::streambuf* old_buffer = std::cout.rdbuf(buffer.rdbuf());
            driver.result.clear();
            driver.context.set_window_pointer(this);
            bool parse_success = driver.parse_string(the_command.ToStdString() + "\n");  // wxString vs std::string again!!
            std::string captured_text = buffer.str();
            std::cout.rdbuf(old_buffer);
            m_command_result_canvas->AppendMultiLineText(captured_text, false, RC_OBJECT_NONE, true);
            if (!driver.result.is_empty_ket())
            {
                m_command_result_canvas->AppendActiveText(driver.result.to_string());
            }
            if (!parse_success)
            {
                wxMessageBox("Parse failed for command: " + the_command);
            }
            if (m_auto_insert_new_line)
            {
                m_command_result_canvas->AppendLine();
            }
            // m_command_result_canvas->AppendNewLine();  // For now AppendActiveText inserts it's own new lines. Maybe change later.
        }
    }
    else
    {
        for (int idx = 0; idx < m_command_text->GetLineCount(); idx++)
        {
            the_command = m_command_text->GetLine(idx);
            m_command_result_canvas->AppendText(AGENT_PROMPT, false);
            if (the_command != "\n")  // Do we really want this here? Ie, to just print a prompt if the command is empty?
            {
                m_command_result_canvas->AppendText(the_command, false);
                // m_command_result_canvas->AppendNewLine();
                // std::vector<std::string> vect_str = split(the_command.ToStdString(), "=> ");  // Just a dummy until we wire in the backend code.
                // m_command_result_canvas->AppendText(vect_str.back(), false);
                std::stringstream buffer;
                std::streambuf* old_buffer = std::cout.rdbuf(buffer.rdbuf());
                driver.result.clear();
                driver.context.set_window_pointer(static_cast<void *>(this));  // We cast to void* so that ContextList can be wxWidgets free.
                bool parse_success = driver.parse_string(the_command.ToStdString() + "\n");  // wxString vs std::string again!!
                std::string captured_text = buffer.str();
                std::cout.rdbuf(old_buffer);
                m_command_result_canvas->AppendNewLine();  // Do we need this here?
                m_command_result_canvas->AppendMultiLineText(captured_text, false, RC_OBJECT_NONE, true);
                if (!driver.result.is_empty_ket())
                {
                    m_command_result_canvas->AppendText(driver.result.to_string());
                }
                if (!parse_success)  // This should probably be before Appending captured_text!
                {
                    wxMessageBox("Parse failed for command: " + the_command);
                }

                if (m_auto_insert_new_line)
                {
                    m_command_result_canvas->AppendLine();
                }
                else
                {
                    m_command_result_canvas->AppendNewLine();  // Maybe two of these?
                }
            }
            else
            {
                m_command_result_canvas->AppendNewLine();
            }
        }
    }
    the_timer.Stop();
    m_timer_line->SetLabel("Time taken: " + display_time(the_timer.GetTime()));
    UpdateContextSelector();
}

void CommandPanel::OnDumpButtonDown(wxCommandEvent& event)
{
    std::stringstream buffer;
    context.print_universe(true, buffer);
    std::string captured_text = buffer.str();
    wxString title = wxString::Format("Dump of the current context \"%s\"", driver.context.get_context_name());
    DumpFrame* dump_frame = new DumpFrame(this, title, captured_text);
}

void CommandPanel::OnSaveAsButtonDown(wxCommandEvent& event)
{
    // wxMessageBox("Save as the current command window to a .sw3 file");
    wxFileDialog saveFileDialog(this, "Save sw file", "", "", "sw file (*.sw;*.swc;*.sw3;*.sw4)|*.sw;*.swc;*.sw3;*.sw4|Text file (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }
    SaveFile(saveFileDialog.GetPath());
}

void CommandPanel::OnGraphButtonDown(wxCommandEvent& event)
{
    wxMessageBox("Graph button pressed.\nLater we will insert a graph!\nFor now see save-as-dot[].");
}

void CommandPanel::OnResetContextButtonDown(wxCommandEvent& event)
{
    wxString reset_context_text = wxString::Format("Are you really sure you want to erase the current context \"%s\"?\nAll knowledge in this context will be deleted!", driver.context.get_context_name());
    ResetContextDialog* dlg = new ResetContextDialog(this, "Reset context", reset_context_text);
    if (dlg->ShowModal() == wxID_OK)
    {
        driver.context.reset_current_context();
    }

}

void CommandPanel::OnResetAllButtonDown(wxCommandEvent& event)
{
    wxString reset_all_text = "Are you really sure you want to erase all knowledge?";
    ResetContextDialog* dlg = new ResetContextDialog(this, "Reset all", reset_all_text);
    if (dlg->ShowModal() == wxID_OK)
    {
        driver.context.reset();
    } 
    UpdateContextSelector();
}


void CommandPanel::OnUseMonospaceCheckBox(wxCommandEvent& event)
{
    m_use_command_monospace = m_command_monospace_checkbox->GetValue();
    if (m_use_command_monospace)
    {
        // switch on monospace font.
        // m_command_text->SetDefaultStyle(*m_mono_attr);  // Nope. Crashes! With assert failure. Fix later.
        m_command_text->StyleSetFont(0, m_mono_attr->GetFont());
    }
    else
    {
        // switch off monospace font.
        // m_command_text->SetDefaultStyle(*m_default_attr);
        m_command_text->StyleSetFont(0, m_default_attr->GetFont());
    }
}


void CommandPanel::OnUseLineNumbersCheckBox(wxCommandEvent& event)
{
    m_use_command_line_numbers = m_command_line_numbers_checkbox->GetValue();
    if (m_use_command_line_numbers)
    {
        m_command_text->SetMarginType(1, wxSTC_MARGIN_NUMBER); // Set margin to be numbers.
    }
    else
    {
        m_command_text->SetMarginType(1, wxSTC_MARGIN_SYMBOL); // Switch off numbers.
    }
}

void CommandPanel::OnClearButtonDown(wxCommandEvent& event)
{
    // m_command_result_canvas->ClearCanvas();
    // m_command_text->Clear();
    m_command_text->ClearAll();
    m_current_line = 1;
    m_current_position = -1;
    m_inside_ket = false;
    m_line_has_learn_rule.clear();
}

void CommandPanel::OnInsertNewLineButtonDown(wxCommandEvent& event)
{
    m_command_result_canvas->AppendNewLine();
    m_command_result_canvas->AppendNewLine();
}

void CommandPanel::OnInsertLineButtonDown(wxCommandEvent& event)
{
    m_command_result_canvas->AppendLine();
}

void CommandPanel::OnClearResultsButtonDown(wxCommandEvent& event)
{
    m_command_result_canvas->ClearCanvas();
}

void CommandPanel::InsertText(const wxString& wxs)
{
    m_command_text->WriteText(wxs);
}

void CommandPanel::InsertStatement(const wxString& wxs)
{
    std::string statement_name = wxs.ToStdString();  // Yeah, once again mapping from wxString to std::string!
    if (operator_usage_map.has_statement_prototype(statement_name))
    {
        m_command_text->WriteText(operator_usage_map.statement_prototypes[statement_name]);
    }
}

void CommandPanel::InsertLearnRule(const wxString& wxs)
{
    m_command_text->WriteText(wxs + " ");
    m_line_has_learn_rule[m_current_line] = true;
}

void CommandPanel::InsertInfixOperator(const wxString& wxs)
{
    m_command_text->WriteText(wxs + " ");
}

void CommandPanel::InsertSimpleOperator(const wxString& wxs)
{
    m_command_text->WriteText(wxs + " ");
}

void CommandPanel::InsertCompoundOperator(const wxString& wxs)
{
    m_command_text->WriteText(wxs + "[ ] ");
    m_command_text->GotoPos(m_command_text->GetCurrentPos() - 3);
}

void CommandPanel::InsertFunctionOperator(const wxString& wxs)
{
    m_command_text->WriteText(wxs + "( ) ");
    m_command_text->GotoPos(m_command_text->GetCurrentPos() - 3);
}

void CommandPanel::InsertKet(const wxString& wxs)
{
    m_command_text->WriteText(wxs + " ");
}

void CommandPanel::InsertComment()
{
    m_command_text->WriteText("\n-- ");
}

void CommandPanel::MoveCaret(int steps)  // Now we have InsertxxxOperator, maybe we don't need or want this?
{
    m_command_text->GotoPos(m_command_text->GetCurrentPos() + steps);
}

void CommandPanel::SetCurrentLine(int line)
{
    m_current_line = line;
}

void CommandPanel::SetRunTime(long long time)
{
    m_run_time = time;
}

void CommandPanel::OnContextSelect(wxCommandEvent& event)
{
    unsigned int new_selection = m_context_selector->GetSelection();
    driver.context.set(new_selection);
}

void CommandPanel::UpdateContextSelector()
{
    m_context_selector->Clear();
    for (const auto& name : driver.context.get_context_names())
    {
        m_context_selector->AppendString(name);
    }
    m_context_selector->SetSelection(driver.context.get_context_index());
}

void CommandPanel::SaveFile(const wxString& filename)
{
    // wxMessageBox("Command panel SaveFile: " + filename);
    wxFileOutputStream output_stream(filename);
    if (!output_stream.IsOk())
    {
        wxLogError("Cannot save to file '%s'.", filename);
        return;
    }
    wxTextOutputStream text(output_stream);
    text.WriteString(m_command_text->GetText());
}

CommandPanel::~CommandPanel()
{}

