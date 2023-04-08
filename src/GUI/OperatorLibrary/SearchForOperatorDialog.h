//
// Semantic DB 4
// Created 2023/4/8
// Updated 2023/4/8
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../../SDB.h"


class SearchForOperatorDialog : public wxDialog
{
public:
    // Constructor:
    SearchForOperatorDialog(wxWindow* parent, long style = 0);

    void OnSearchButton(wxCommandEvent& event);

    // Destructor:
    ~SearchForOperatorDialog();
private:

    wxCheckBox* m_simple_operator_checkbox;
    wxCheckBox* m_compound_operator_checkbox;
    wxCheckBox* m_function_operator_checkbox;

    wxCheckBox* m_name_checkbox;
    wxCheckBox* m_description_checkbox;
    wxCheckBox* m_examples_checkbox;

    wxTextCtrl* m_search_term_ctrl;
};

