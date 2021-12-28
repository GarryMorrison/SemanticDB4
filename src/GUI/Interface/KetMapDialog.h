//
// Semantic DB 4
// Created 2021/12/28
// Updated 2021/12/28
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "SDB.h"

class KetMapDialog : public wxDialog {

public:
    //! constructor
    KetMapDialog(wxWindow* parent, long style = 0);

    // void OnColumnClick(wxListEvent& event);

    //! destructor
    ~KetMapDialog();

private:

    std::map<int, std::string> m_ket_map;
};


