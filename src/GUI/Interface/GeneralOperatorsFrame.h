//
// Semantic DB 4
// Created 2022/1/6
// Updated 2022/1/6
// Author Garry Morrison
// License GPL v3
//

#pragma once

#include "../../SDB.h"


class GeneralOperatorsFrame : public wxFrame
{
public:
    GeneralOperatorsFrame(wxWindow* parent, const wxString& title, const wxArrayString& content, const wxPoint position_delta = wxPoint(0, 0), long style = 0);

    void OnCheckBoxClick(wxCommandEvent& event);

    ~GeneralOperatorsFrame();

private:
    wxWindow* m_parent;
    std::vector<wxArrayString> m_our_arrays;
    std::vector<wxCheckListBox*> m_our_checkboxes;
    unsigned int m_dim = 0;
};
