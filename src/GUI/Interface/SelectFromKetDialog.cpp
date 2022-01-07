//
// Semantic DB 4
// Created 2022/1/7
// Updated 2022/1/7
// Author Garry Morrison
// License GPL v3
//

#include "SelectFromKetDialog.h"
extern SDB::Driver driver;

wxDEFINE_EVENT(EVT_KETWINDOW_CLICK, wxCommandEvent);


SelectFromKetDialog::SelectFromKetDialog(wxWindow* parent, const wxPoint position_delta)
	: wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	SetTitle("Select ket");
    wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);

    wxArrayString list_options;
    for (ulong ket_idx : driver.context.relevant_kets("*"))
    {
        list_options.Add('|' + ket_map.get_str(ket_idx) + '>');
    }
    m_data_list = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(200, -1), list_options, wxLB_ALWAYS_SB);
    topsizer->Add(m_data_list, wxSizerFlags(1).Expand().Border(wxALL, 10));

    wxBoxSizer* button_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* update_button = new wxButton(this, ID_Update_Button, "Update");
    wxButton* close_button = new wxButton(this, wxID_CLOSE, "Close");
    button_sizer->Add(update_button, wxSizerFlags(0).Center().Border(wxLEFT | wxRIGHT, 10));
    button_sizer->Add(close_button, wxSizerFlags(0).Center().Border(wxLEFT | wxRIGHT, 10));

    update_button->Bind(wxEVT_BUTTON, &SelectFromKetDialog::OnUpdateButton, this);

    close_button->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
        Close();
        });

    m_data_list->Bind(wxEVT_LISTBOX, &SelectFromKetDialog::OnKetListClick, this);

    topsizer->Add(button_sizer, wxSizerFlags(0).Center());
    topsizer->AddSpacer(10);
    SetSizerAndFit(topsizer);
    CenterOnScreen();
    wxPoint dialog_position = GetScreenPosition();
    dialog_position += position_delta;
    SetPosition(dialog_position);
    Show();
}

void SelectFromKetDialog::OnKetListClick(wxCommandEvent& event)
{
    // wxMessageBox("Ket list clicked");
    
    unsigned int selected_idx = m_data_list->GetSelection();
    wxString selected_item = m_data_list->GetString(selected_idx);
    wxCommandEvent our_event(EVT_KETWINDOW_CLICK);
    our_event.SetString(selected_item);
    wxPostEvent(this, our_event);
    m_data_list->DeselectAll();
    
}

void SelectFromKetDialog::OnUpdateButton(wxCommandEvent& event)
{
    m_data_list->Clear();
    for (ulong ket_idx : driver.context.relevant_kets("*"))
    {
        m_data_list->Append('|' + ket_map.get_str(ket_idx) + '>');
    }
}

SelectFromKetDialog::~SelectFromKetDialog()
{}