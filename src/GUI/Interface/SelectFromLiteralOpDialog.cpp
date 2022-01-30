//
// Semantic DB 4
// Created 2022/1/7
// Updated 2022/1/7
// Author Garry Morrison
// License GPL v3
//

#include "SelectFromLiteralOpDialog.h"
extern SDB::Driver driver;

wxDEFINE_EVENT(EVT_LITERALOP_WINDOW_CLICK, wxCommandEvent);


SelectFromLiteralOpDialog::SelectFromLiteralOpDialog(wxWindow* parent, const wxPoint position_delta)
    : wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
    SetTitle("Select literal operator");
    wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);

    wxArrayString list_options;
    std::set<std::string> known_literal_operators;  // We need a set, so that we don't include duplicates!
    for (ulong ket_idx : context.relevant_kets("*"))
    {
        for (ulong op_idx : context.supported_ops(ket_idx))
        {
            std::string op_label = ket_map.get_str(op_idx);
            known_literal_operators.insert(op_label);
        }
    }
    for (const auto& op_label : known_literal_operators)
    {
        list_options.Add(op_label);
    }
    m_data_list = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(200, -1), list_options, wxLB_ALWAYS_SB);
    topsizer->Add(m_data_list, wxSizerFlags(1).Expand().Border(wxALL, 10));

    wxBoxSizer* button_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* update_button = new wxButton(this, ID_Update_Button, "Update");
    wxButton* close_button = new wxButton(this, wxID_CLOSE, "Close");
    button_sizer->Add(update_button, wxSizerFlags(0).Center().Border(wxLEFT | wxRIGHT, 10));
    button_sizer->Add(close_button, wxSizerFlags(0).Center().Border(wxLEFT | wxRIGHT, 10));

    update_button->Bind(wxEVT_BUTTON, &SelectFromLiteralOpDialog::OnUpdateButton, this);

    close_button->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
        Close();
        });

    m_data_list->Bind(wxEVT_LISTBOX, &SelectFromLiteralOpDialog::OnLiteralOpListClick, this);

    topsizer->Add(button_sizer, wxSizerFlags(0).Center());
    topsizer->AddSpacer(10);
    SetSizerAndFit(topsizer);
    CenterOnScreen();
    wxPoint dialog_position = GetScreenPosition();
    dialog_position += position_delta;
    SetPosition(dialog_position);
    Show();
}

void SelectFromLiteralOpDialog::OnLiteralOpListClick(wxCommandEvent& event)
{
    // wxMessageBox("Ket list clicked");

    unsigned int selected_idx = m_data_list->GetSelection();
    wxString selected_item = m_data_list->GetString(selected_idx);
    wxCommandEvent our_event(EVT_LITERALOP_WINDOW_CLICK);
    our_event.SetString(selected_item);
    wxPostEvent(this, our_event);
    m_data_list->DeselectAll();

}

void SelectFromLiteralOpDialog::OnUpdateButton(wxCommandEvent& event)
{
    m_data_list->Clear();
    std::set<std::string> known_literal_operators;  // We need a set, so that we don't include duplicates!
    for (ulong ket_idx : context.relevant_kets("*"))
    {
        for (ulong op_idx : context.supported_ops(ket_idx))
        {
            std::string op_label = ket_map.get_str(op_idx);
            known_literal_operators.insert(op_label);
        }
    }
    for (const auto& op_label : known_literal_operators)
    {
        m_data_list->Append(op_label);
    }
}

SelectFromLiteralOpDialog::~SelectFromLiteralOpDialog()
{}

