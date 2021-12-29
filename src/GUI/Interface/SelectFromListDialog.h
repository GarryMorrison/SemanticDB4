//
// Semantic DB 4
// Created 2021/12/28
// Updated 2021/12/28
// Author Garry Morrison
// License GPL v3
//

#pragma once

#include "../../SDB.h"

class SelectFromListDialog : public wxDialog {

public:
    //! constructor
    SelectFromListDialog(wxWindow* parent, wxString dialog_title, wxArrayString list_options, const wxPoint position_delta = wxPoint(0, 0), bool sort_entries = false, long style = 0);

    bool IsOK();
    wxString GetResult();
    void DeselectAll();

    //! destructor
    ~SelectFromListDialog();


private:
    bool m_isOK;
    wxString m_result;
    wxListBox* m_result_list;

};

