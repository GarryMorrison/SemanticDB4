//
// Semantic DB 4
// Created 2021/12/29
// Updated 2022/1/6
// Author Garry Morrison
// License GPL v3
//

#include "FilteredDumpFrame.h"

FilteredDumpFrame::FilteredDumpFrame(wxWindow* parent, const wxString& title, const std::vector<std::string>& op_list, const std::vector<std::string>& ket_list, const wxPoint position_delta, long style)
    : wxFrame(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(700, 800), style | wxDEFAULT_FRAME_STYLE | wxRESIZE_BORDER)
{
    m_parent = parent;
    m_position_delta = position_delta;
    wxString local_title = "Filtered knowledge for ";
    if (op_list.empty() || ket_list.empty())
    {
        local_title += join(op_list, ", ") + join(ket_list, ", ");
    }
    else
    {
        local_title += join(op_list, ", ") + ", " + join(ket_list, ", ");
    }

    /*
    for (const auto& op : op_list)  // Later put this section in UpdateKnowledge() method?
    {
        if (!m_knowledge.empty())
        {
            m_knowledge += "\n\n";
        }
        m_knowledge += EXAMPLE_OP_KNOWLEDGE;  // dump[op] rel-kets[op]
    }
    for (const auto& ket : ket_list)
    {
        if (!m_knowledge.empty())
        {
            m_knowledge += "\n\n";
        }
        m_knowledge += EXAMPLE_KET_KNOWLEDGE;  // dump[*] |ket>
    }
    */

    wxPanel* panel = new wxPanel(this, wxID_ANY);

    SetTitle(local_title);  // Ignore passed in title for now.
    wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);
 
    // Add context selector:
    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxArrayString context_list;  // Later wire in ContextList, for now just some dummy values.
    context_list.Add("global");
    context_list.Add("plurals");
    context_list.Add("numbers to words");
    context_list.Add("predicting integer sequences");
    wxChoice* context_selector = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, context_list);
    context_selector->SetSelection(0);
    hbox1->Add(new wxStaticText(panel, wxID_ANY, "Context", wxDefaultPosition, wxDefaultSize), wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
    hbox1->Add(context_selector, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
    wxCheckBox* use_active_text_checkbox = new wxCheckBox(panel, wxID_ANY, "Active text");
    use_active_text_checkbox->SetValue(m_use_active_text);
    hbox1->Add(use_active_text_checkbox, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
    wxCheckBox* op_ket_and_checkbox = new wxCheckBox(panel, wxID_ANY, "And operators and kets");
    op_ket_and_checkbox->SetValue(m_use_op_ket_and);
    hbox1->Add(op_ket_and_checkbox, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
    wxCheckBox* general_operators_checkbox = new wxCheckBox(panel, wxID_ANY, "General operators");
    general_operators_checkbox->SetValue(m_show_general_operators);
    hbox1->Add(general_operators_checkbox, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
    topsizer->AddSpacer(10);
    topsizer->Add(hbox1);

    // wxCheckListBox "header":
    wxBoxSizer* literal_op_sizer = new wxBoxSizer(wxVERTICAL);
    literal_op_sizer->Add(new wxStaticText(panel, wxID_ANY, "Literal operators", wxDefaultPosition, wxDefaultSize), wxSizerFlags(0).Left().Border(wxALL, 10));
    unsigned int list_idx = 0;
    for (const auto& op : op_list)
    {
        ulong op_idx = ket_map.get_idx(op);
        m_map_literal_ops[list_idx] = op_idx;
        m_set_active_literal_ops.insert(list_idx);
        list_idx++;
        m_literal_ops.Add(op);
    }  // Potentially sort m_literal_ops here.
    m_literal_op_list_box = new wxCheckListBox(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_literal_ops);
    for (unsigned int idx = 0; idx < m_literal_ops.size(); idx++)
    {
        m_literal_op_list_box->Check(idx, true);
    }
    literal_op_sizer->Add(m_literal_op_list_box, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));

    wxBoxSizer* ket_sizer = new wxBoxSizer(wxVERTICAL);
    ket_sizer->Add(new wxStaticText(panel, wxID_ANY, "Kets", wxDefaultPosition, wxDefaultSize), wxSizerFlags(0).Left().Border(wxALL, 10));
    list_idx = 0;
    for (const auto& k : ket_list)
    {
        m_set_active_kets.insert(list_idx);
        list_idx++;
        m_kets.Add(k);
    }  // Potentially sort m_kets here.
    m_ket_list_box = new wxCheckListBox(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_kets);
    for (unsigned int idx = 0; idx < m_kets.size(); idx++)
    {
        m_ket_list_box->Check(idx, true);
    }
    ket_sizer->Add(m_ket_list_box, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));

    // wxCheckBox* op_ket_and = new wxCheckBox(panel, wxID_ANY, "And operators and kets");
    // Maybe add an active-text checkbox here?

    wxBoxSizer* checklist_sizer = new wxBoxSizer(wxHORIZONTAL);
    checklist_sizer->Add(literal_op_sizer);
    checklist_sizer->Add(ket_sizer);
    // checklist_sizer->Add(op_ket_and, wxSizerFlags(0).Left().Border(wxTOP | wxBOTTOM, 10));
    topsizer->Add(checklist_sizer);
    topsizer->AddSpacer(10);


    m_result_canvas = new ResultCanvas(panel, wxID_ANY, wxDefaultPosition, wxSize(650, 600));
    m_result_canvas->AppendActiveText(m_knowledge);
    topsizer->Add(m_result_canvas, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));

    wxBoxSizer* button_sizer = new wxBoxSizer(wxHORIZONTAL);
    // wxButton* close_button = new wxButton(panel, wxID_CANCEL, "Close");
    wxButton* close_button = new wxButton(panel, wxID_OK, "OK");  // Use OK instead of Close for dump frames.
    // button_sizer->Add(close_button, wxSizerFlags(0).Center().Border(wxALL, 10));  // Center the button, or left?
    button_sizer->Add(close_button, wxSizerFlags(0).Left().Border(wxALL, 10));  // Center the button, or left?
    // topsizer->Add(button_sizer, wxSizerFlags(0).Center());
    topsizer->Add(button_sizer, wxSizerFlags(0).Left());

    wxArrayString grid_data;  // Later enter real data, ie: supported-ops |*>
    grid_data.Add("zero");
    grid_data.Add("one");
    grid_data.Add("two");
    grid_data.Add("three");
    grid_data.Add("four");
    grid_data.Add("five");
    grid_data.Add("six");
    grid_data.Add("seven");
    grid_data.Add("eight");
    grid_data.Add("nine");
    grid_data.Add("ten");

    m_general_operators_frame = new GeneralOperatorsFrame(this, "General operators", grid_data);  // Wire in supported-ops |*> later.
    m_general_operators_frame->Hide();

    close_button->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
        if (event.GetId() == wxID_OK)
        {
            Close();
        }
        });

    use_active_text_checkbox->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent& event) {
        m_use_active_text = use_active_text_checkbox->GetValue();
        UpdateKnowledge();
        });

    op_ket_and_checkbox->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent& event) {
        m_use_op_ket_and = op_ket_and_checkbox->GetValue();
        UpdateKnowledge();
        });

    general_operators_checkbox->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent& event) {
        m_show_general_operators = general_operators_checkbox->GetValue();
        if (m_show_general_operators)
        {
            m_general_operators_frame->Show();
        }
        else
        {
            m_general_operators_frame->Hide();
        }
        });

    m_literal_op_list_box->Bind(wxEVT_CHECKLISTBOX, &FilteredDumpFrame::CheckLiteralOpList, this);
    m_ket_list_box->Bind(wxEVT_CHECKLISTBOX, &FilteredDumpFrame::CheckKetList, this);

    UpdateKnowledge();
    panel->SetSizerAndFit(topsizer);
    CenterOnScreen();
    wxPoint dialog_position = GetScreenPosition();  // I think my position delta code is not working just yet ....
    dialog_position += m_position_delta;
    SetPosition(dialog_position);
    Show();
}

void FilteredDumpFrame::CheckLiteralOpList(wxCommandEvent& event)
{
    unsigned int list_idx = event.GetInt();  // GetInt() is int not unsigned int ...
    ulong op_idx = m_map_literal_ops[list_idx];
    std::string op_name = ket_map.get_str(op_idx);  // Yeah, looks ugly for now, but will be cleaner later!
    if (m_literal_op_list_box->IsChecked(list_idx))
    {
        // wxMessageBox("Operator checked: " + op_name);
        m_set_active_literal_ops.insert(list_idx);
    }
    else
    {
        // wxMessageBox("Operator unchecked: " + op_name);
        m_set_active_literal_ops.erase(list_idx);
    }
    UpdateKnowledge();
}

void FilteredDumpFrame::CheckKetList(wxCommandEvent& event)
{
    unsigned int list_idx = event.GetInt();  // GetInt() is int not unsigned int ...
    // ulong ket_idx = m_map_kets[list_idx];  // Need to handle |Rob> vs Rob, when using ket_map.get_str().
    // std::string ket_name = ket_map.get_str(ket_idx);  // Yeah, looks ugly for now, but will be cleaner later!
    wxString ket_name = m_kets[list_idx];
    if (m_ket_list_box->IsChecked(list_idx))
    {
        // wxMessageBox("Ket checked: " + ket_name);
        m_set_active_kets.insert(list_idx);
    }
    else
    {
        // wxMessageBox("Ket unchecked: " + ket_name);
        m_set_active_kets.erase(list_idx);
    }
    UpdateKnowledge();
}

void FilteredDumpFrame::UpdateKnowledge()
{
    m_knowledge.Clear();
    if (!m_use_op_ket_and)
    {
        for (unsigned int op_idx : m_set_active_literal_ops)  // Later: dump[op] rel-kets[op]
        {
            // wxString op = m_literal_ops[op_idx];
            // m_knowledge += "knowledge for literal operator: " + op + "\n";  // Maybe sort the knowledge according to some criteria? For now, set sorts by list_idx. Which is good!
            std::string op = m_literal_ops[op_idx].ToStdString();
            Superposition ket_sp(context.relevant_kets(op));
            std::vector<ulong> operators;
            operators.push_back(ket_map.get_idx(op));
            m_knowledge += dump(ket_sp, context, operators);
        }
        if (!m_knowledge.empty())
        {
            m_knowledge += "\n";
        }
        for (unsigned int ket_idx : m_set_active_kets)  // Later: dump[*] |ket>
        {
            // wxString k = m_kets[ket_idx];
            // m_knowledge += "knowledge for ket: " + k + "\n";  // Maybe sort the knowledge according to some criteria?
            std::string ket_label = strip_ket(m_kets[ket_idx].ToStdString());  // wxString vs std::string again!
            Ket k(ket_label);
            std::vector<ulong> operators;
            operators.push_back(ket_map.get_idx("*"));
            m_knowledge += dump(k, context, operators);
        }
    }
    else
    {
        for (unsigned int op_idx : m_set_active_literal_ops)
        {
            // wxString op = m_literal_ops[op_idx];
            for (unsigned int ket_idx : m_set_active_kets)
            {
                // wxString k = m_kets[ket_idx];
                // m_knowledge += wxString::Format("knowledge for literal operator: %s and ket: %s\n", op, k);
                std::string ket_label = strip_ket(m_kets[ket_idx].ToStdString());  // wxString vs std::string again!
                Ket k(ket_label);
                std::string op = m_literal_ops[op_idx].ToStdString();
                std::vector<ulong> operators;
                operators.push_back(ket_map.get_idx(op));
                m_knowledge += dump(k, context, operators);
            }
        }
    }

    m_result_canvas->ClearCanvas();
    if (m_use_active_text)
    {
        m_result_canvas->AppendActiveText(m_knowledge);
    }
    else
    {
        m_result_canvas->AppendText(m_knowledge);
    }
}

FilteredDumpFrame::~FilteredDumpFrame()
{}

