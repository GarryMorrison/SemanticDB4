//
// Semantic DB 4
// Created 2021/12/28
// Updated 2021/12/28
// Author Garry Morrison
// License GPL v3
//

#pragma once

#include "../SDB_GUI.h"

class ResultCanvas;

class DumpFrame : public wxFrame
{
public:
    DumpFrame(wxWindow* parent, const wxString& title, const wxString& content, const wxPoint position_delta = wxPoint(0, 0), long style = 0);
    DumpFrame(wxWindow* parent, const wxString& title, const std::vector<std::string>& op_list, const std::vector<std::string>& ket_list, const wxPoint position_delta = wxPoint(0, 0), long style = 0);

    ~DumpFrame();
private:
    wxWindow* m_parent;
    ResultCanvas* m_result_canvas;
    wxPoint m_position_delta = wxPoint(0, 0);
};
