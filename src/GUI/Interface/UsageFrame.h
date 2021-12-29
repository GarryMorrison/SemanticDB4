//
// Semantic DB 4
// Created 2021/12/28
// Updated 2021/12/28
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../../SDB.h"


class UsageFrame : public wxFrame {
public:
    UsageFrame(wxWindow* parent, std::string op, wxPoint position_delta = wxPoint(0, 0), long style = 0);
    ~UsageFrame();
private:

};
