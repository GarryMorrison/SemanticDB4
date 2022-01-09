//
// Semantic DB 4
// Created 2022/1/6
// Updated 2022/1/8
// Author Garry Morrison
// License GPL v3
//

#pragma once

#include "../../SDB.h"


class GeneralOperatorsFrame : public wxFrame
{
public:
    GeneralOperatorsFrame(wxWindow* parent, const wxString& title, const wxArrayString& content, const wxPoint position_delta = wxPoint(0, 0), long style = 0);
    GeneralOperatorsFrame(wxWindow* parent, const wxPoint position_delta = wxPoint(0, 0));

    void OnCheckBoxClick(wxCommandEvent& event);
    bool IsChecked(unsigned int list_idx);
    void OnUpdateButton(wxCommandEvent& event);
    void OnContextSelect(wxCommandEvent& event);
    void UpdateFrame();

    ~GeneralOperatorsFrame();

private:
    wxWindow* m_parent;
    wxPanel* m_panel;
    wxBoxSizer* m_topsizer;
    wxArrayString m_general_ops;
    std::vector<wxArrayString> m_our_arrays;
    std::vector<wxCheckListBox*> m_our_checkboxes;
    wxButton* m_update_button;
    wxChoice* m_context_selector;
    unsigned int m_dim = 0;
};
