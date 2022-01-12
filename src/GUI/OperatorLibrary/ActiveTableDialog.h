//
// Semantic DB 4
// Created 2022/1/11
// Updated 2022/1/11
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../../SDB.h"

class ActiveTableDialog : public wxDialog {

public:
    //! constructor
    ActiveTableDialog(wxWindow* parent, long style = 0);

    void OnUsageButton(wxCommandEvent& event);
    void OnGenerateButton(wxCommandEvent& event);
    void GenerateCommand();

    //! destructor
    ~ActiveTableDialog();

private:
    wxTextCtrl* m_input_superposition_ctrl;
    wxTextCtrl* m_input_label_ctrl;
    wxTextCtrl* m_lhs_ctrl;
    wxTextCtrl* m_rhs_ctrl;
    wxTextCtrl* m_sort_by_ctrl;
    wxCheckBox* m_sort_reverse_checkbox;
    wxTextCtrl* m_command_text_ctrl;

    std::vector<wxArrayString> m_our_arrays;
    std::vector<wxCheckListBox*> m_our_checkboxes;
};

