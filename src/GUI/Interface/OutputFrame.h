//
// Semantic DB 4
// Created 2022/1/8
// Updated 2022/1/8
// Author Garry Morrison
// License GPL v3
//

#pragma once

#include "../../SDB.h"


class OutputFrame : public wxFrame
{
public:
    OutputFrame(wxWindow* parent, const wxString& title, const wxString& content, const wxPoint position_delta = wxPoint(0, 0), long style = 0);

    ~OutputFrame();

private:
    wxWindow* m_parent;
    wxRichTextCtrl* m_output_text;
    wxPoint m_position_delta = wxPoint(0, 0);
};

