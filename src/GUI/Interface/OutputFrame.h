//
// Semantic DB 4
// Created 2022/1/8
// Updated 2022/1/8
// Author Garry Morrison
// License GPL v3
//

#pragma once

#include "../../SDB.h"
class ResultCanvas;

class OutputFrame : public wxFrame
{
public:
    OutputFrame(wxWindow* parent, const wxString& title, const wxString& content, const wxString& seq_result = wxEmptyString, const wxPoint position_delta = wxPoint(0, 0), long style = 0);

    void OnCopyAll(wxCommandEvent& event);
    void SetRunTime(long long time);
    ~OutputFrame();

private:
    wxWindow* m_parent;
    wxRichTextCtrl* m_output_text;
    ResultCanvas* m_result_canvas;
    long long m_run_time_ms = 0;
    wxStaticText* m_timer_line;
    wxPoint m_position_delta = wxPoint(0, 0);
};

