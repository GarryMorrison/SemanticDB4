//
// Semantic DB 4
// Created 2022/1/6
// Updated 2022/1/6
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../../SDB.h"

class ResetContextDialog : public wxDialog {

public:
    //! constructor
    ResetContextDialog(wxWindow* parent, const wxString& title, const wxString& message, long style = 0);

    //! destructor
    ~ResetContextDialog();

private:
};

