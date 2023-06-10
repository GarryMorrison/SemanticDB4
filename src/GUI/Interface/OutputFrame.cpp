//
// Semantic DB 4
// Created 2022/1/8
// Updated 2023/6/11
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

    // Add a close button:
    wxButton* close_button = new wxButton(panel, wxID_OK, "OK");

    // Add a copy-all button:
    wxButton* copy_all_button = new wxButton(panel, ID_Copy_All, "Copy All");
    wxButton* save_button = new wxButton(panel, ID_Save_Output, "Save");
    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

    hbox->Add(close_button, wxSizerFlags(0).Left().Border(wxALL, 10));
    hbox->Add(copy_all_button, wxSizerFlags(0).Left().Border(wxALL, 10));
    hbox->Add(save_button, wxSizerFlags(0).Left().Border(wxALL, 10));
    topsizer->Add(hbox);

    // Add a timer string:
    wxString timer_string = "Timer: " + display_time(m_run_time_ms);
    m_timer_line = new wxStaticText(panel, wxID_ANY, timer_string);
    topsizer->Add(m_timer_line, wxSizerFlags(0).Left().Border(wxALL, 10));

    close_button->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
        if (event.GetId() == wxID_OK)
        {
            Close();
        }
        });

    copy_all_button->Bind(wxEVT_BUTTON, &OutputFrame::OnCopyAll, this);
    save_button->Bind(wxEVT_BUTTON, &OutputFrame::OnSave, this);

    panel->SetSizerAndFit(topsizer);
    CenterOnScreen();
    wxPoint dialog_position = GetScreenPosition();
    dialog_position += m_position_delta;
    SetPosition(dialog_position);
    Fit();
    Show();
}

void OutputFrame::OnCopyAll(wxCommandEvent& event)
{
    wxString the_text = m_result_canvas->GetText();
    wxClipboardLocker clipLock;
    if (!clipLock)
    {
        return;  // Failed to lock clipboard.
    }
    if (!wxTheClipboard->AddData(new wxTextDataObject(the_text)))
    {
        return;  // Failed to put text on clipboard.
    }
    if (!wxTheClipboard->Flush())
    {
        return;  // Failed to flush clipboard.
    }
    wxMessageBox("Frame copied.");  // Do we need this?
}

void OutputFrame::OnSave(wxCommandEvent& event)
{
    // wxMessageBox("Output frame Save button pressed");
    wxFileDialog saveFileDialog(this, "Save output", "", "output.txt", "Text file (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }
    SaveFile(saveFileDialog.GetPath());
}

void OutputFrame::SaveFile(const wxString& filename)
{
    // wxMessageBox("OutputFrame SaveFile: " + filename);
    wxFileOutputStream output_stream(filename);
    if (!output_stream.IsOk())
    {
        wxLogError("Cannot save to file '%s'.", filename);
        return;
    }
    wxTextOutputStream text(output_stream);
    text.WriteString(m_result_canvas->GetText());
}

void OutputFrame::SetRunTime(long long time)
{
    m_run_time_ms = time;
    wxString timer_string = "Timer: " + display_time(m_run_time_ms);
    m_timer_line->SetLabel(timer_string);
}

OutputFrame::~OutputFrame()
{}
