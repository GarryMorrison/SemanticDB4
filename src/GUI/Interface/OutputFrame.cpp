//
// Semantic DB 4
// Created 2022/1/8
// Updated 2022/1/8
// Author Garry Morrison
// License GPL v3
//

#include "OutputFrame.h"

OutputFrame::OutputFrame(wxWindow* parent, const wxString& title, const wxString& content, const wxString& seq_result, const wxPoint position_delta, long style)
	: wxFrame(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(700, 680), style | wxDEFAULT_FRAME_STYLE | wxRESIZE_BORDER)
{
    m_parent = parent;
    m_position_delta = position_delta;
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    SetTitle(title);
    wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);
    // m_output_text = new wxRichTextCtrl(panel, wxID_ANY, content, wxDefaultPosition, wxSize(650, 600));  // Make read only?
    // topsizer->Add(m_output_text, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
    m_result_canvas = new ResultCanvas(panel, wxID_ANY, wxDefaultPosition, wxSize(600, 600));
    m_result_canvas->AppendMultiLineText(content, false, RC_OBJECT_NONE, true);
    if (!seq_result.empty())
    {
        m_result_canvas->AppendActiveText(seq_result);
    }
    topsizer->Add(m_result_canvas, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));

    wxButton* close_button = new wxButton(panel, wxID_OK, "OK");
    topsizer->Add(close_button, wxSizerFlags(0).Left().Border(wxALL, 10));

    close_button->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
        if (event.GetId() == wxID_OK)
        {
            Close();
        }
        });

    panel->SetSizerAndFit(topsizer);
    CenterOnScreen();
    wxPoint dialog_position = GetScreenPosition();
    dialog_position += m_position_delta;
    SetPosition(dialog_position);
    Fit();
    Show();
}

OutputFrame::~OutputFrame()
{}
