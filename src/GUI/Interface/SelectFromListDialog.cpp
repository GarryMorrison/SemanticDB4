//
// Semantic DB 4
// Created 2021/12/28
// Updated 2021/12/28
// Author Garry Morrison
// License GPL v3
//

#include "SelectFromListDialog.h"

SelectFromListDialog::SelectFromListDialog(wxWindow* parent, wxString dialog_title, wxArrayString list_options, const wxPoint position_delta, bool sort_entries, long style)
    : wxDialog(parent, wxID_ANY, wxEmptyString,
        wxDefaultPosition, wxDefaultSize,
        style | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
    SetTitle(dialog_title);

    // wxListBox* result_list = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, items, wxLB_SINGLE | wxLB_ALWAYS_SB | wxLB_SORT);
    // wxListBox* result_list = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(200, -1), list_options, wxLB_SINGLE | wxLB_ALWAYS_SB);
    if (sort_entries)
    {
        m_result_list = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(200, -1), list_options, wxLB_ALWAYS_SB | wxLB_SORT);
    }
    else
    {
        m_result_list = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(200, -1), list_options, wxLB_ALWAYS_SB);
    }

    wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);
    // create text ctrl with minimal size 100x60 that is horizontally and
    // vertically stretchable with a border width of 10
    topsizer->Add(
        // new wxTextCtrl(this, -1, "My text.", wxDefaultPosition, wxSize(100, 60), wxTE_MULTILINE),
        // new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, items, wxLB_SINGLE | wxLB_ALWAYS_SB | wxLB_SORT),
        m_result_list,
        wxSizerFlags(1).Expand().Border(wxALL, 10));


    wxBoxSizer* button_sizer = new wxBoxSizer(wxHORIZONTAL);
    // wxButton* clear_button = new wxButton(this, ID_Clear_Select_List, "Clear");
    wxButton* close_button = new wxButton(this, wxID_CANCEL, "Close");
    // button_sizer->Add(clear_button, wxSizerFlags(0).Center().Border(wxALL, 10));
    button_sizer->Add(close_button, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));

    topsizer->Add(button_sizer, wxSizerFlags(0).Left());
    topsizer->AddSpacer(10);

    SetSizerAndFit(topsizer);
    CenterOnScreen();
    wxPoint dialog_position = GetScreenPosition();
    dialog_position += position_delta;
    SetPosition(dialog_position);
    // ShowModal();
    Show();

    /*
    clear_button->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
        if (event.GetId() == ID_Clear_Select_List) {
            m_result_list->DeselectAll();
        }
        });
    */

    return;

    m_result_list->Bind(wxEVT_LISTBOX_DCLICK, [=](wxCommandEvent& event) {  // Maybe shift this up further ...
        int the_selection = m_result_list->GetSelection();
        // wxMessageBox("The selection: " + std::to_string(the_selection));
        if (the_selection == wxNOT_FOUND)
        {
            m_isOK = false;
            return;
        }
        m_result = list_options[the_selection];  // Need to check bounds?
        m_isOK = true;
        wxMessageBox("The selection: " + m_result);
        });

    int the_selection = m_result_list->GetSelection();
    // wxMessageBox("The selection: " + std::to_string(the_selection));
    if (the_selection == wxNOT_FOUND)
    {
        m_isOK = false;
        return;
    }
    m_result = list_options[the_selection];  // Need to check bounds?
    m_isOK = true;
}


bool SelectFromListDialog::IsOK()
{
    return m_isOK;
}

wxString SelectFromListDialog::GetResult()
{
    return m_result;
}

void SelectFromListDialog::DeselectAll()
{
    m_result_list->DeselectAll();
}

SelectFromListDialog::~SelectFromListDialog()
{}
