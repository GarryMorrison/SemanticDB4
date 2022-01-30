//
// Semantic DB 4
// Created 2022/1/11
// Updated 2022/1/11
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../../SDB.h"

class CreateNewFileDialog : public wxDialog {

public:
    //! constructor
    CreateNewFileDialog(wxWindow* parent, long style = 0);

    void OnCreateButton(wxCommandEvent& event);
    wxString GetFilename();
    wxString GetContextname();

    //! destructor
    ~CreateNewFileDialog();

private:
    wxTextCtrl* m_filename_ctrl;
    wxTextCtrl* m_context_ctrl;
    wxString m_filename;
    wxString m_context_name;
};

