//
// Semantic DB 4
// Created 2021/12/28
// Updated 2021/12/28
// Author Garry Morrison
// License GPL v3
//


// #include "../../SDB.h"  // We don't need this. Delete at some stage?
#include "DumpFrame.h"


DumpFrame::DumpFrame(wxWindow* parent, const wxString& title, const wxString& content, wxPoint position_delta, long style)
    : wxFrame(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(700, 680), style | wxDEFAULT_FRAME_STYLE | wxRESIZE_BORDER)
{
    m_parent = parent;
    m_position_delta = position_delta;
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    SetTitle(title);
    wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);
    m_result_canvas = new ResultCanvas(panel, wxID_ANY, wxDefaultPosition, wxSize(650, 600));
    m_result_canvas->AppendActiveText(content);
    topsizer->Add(m_result_canvas, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));

    wxBoxSizer* button_sizer = new wxBoxSizer(wxHORIZONTAL);
    // wxButton* close_button = new wxButton(panel, wxID_CANCEL, "Close");
    wxButton* close_button = new wxButton(panel, wxID_OK, "OK");  // Use OK instead of Close for dump frames.
    // button_sizer->Add(close_button, wxSizerFlags(0).Center().Border(wxALL, 10));  // Center the button, or left?
    button_sizer->Add(close_button, wxSizerFlags(0).Left().Border(wxALL, 10));  // Center the button, or left?
    // topsizer->Add(button_sizer, wxSizerFlags(0).Center());
    topsizer->Add(button_sizer, wxSizerFlags(0).Left());

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
    Show();
}

DumpFrame::DumpFrame(wxWindow* parent, const wxString& title, const std::vector<std::string>& op_list, const std::vector<std::string>& ket_list, const wxPoint position_delta, long style)
    : wxFrame(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(700, 680), style | wxDEFAULT_FRAME_STYLE | wxRESIZE_BORDER)
{
    m_parent = parent;
    m_position_delta = position_delta;
    wxString local_title = "Knowledge for ";
    if (op_list.empty() || ket_list.empty())
    {
        local_title += join(op_list, ", ") + join(ket_list, ", ");
    }
    else
    {
        local_title += join(op_list, ", ") + ", " + join(ket_list, ", ");
    }
    
    wxString knowledge;
    for (const auto& op : op_list) 
    {
        if (!knowledge.empty())
        {
            knowledge += "\n\n";
        }
        knowledge += EXAMPLE_OP_KNOWLEDGE;  // dump[op] rel-kets[op]
    }
    for (const auto& ket : ket_list)
    {
        if (!knowledge.empty())
        {
            knowledge += "\n\n";
        }
        knowledge += EXAMPLE_KET_KNOWLEDGE;  // dump[*] |ket>
    }

    wxPanel* panel = new wxPanel(this, wxID_ANY);

    SetTitle(local_title);  // Ignore passed in title for now.
    wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);
    m_result_canvas = new ResultCanvas(panel, wxID_ANY, wxDefaultPosition, wxSize(650, 600));
    m_result_canvas->AppendActiveText(knowledge);
    topsizer->Add(m_result_canvas, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));

    wxBoxSizer* button_sizer = new wxBoxSizer(wxHORIZONTAL);
    // wxButton* close_button = new wxButton(panel, wxID_CANCEL, "Close");
    wxButton* close_button = new wxButton(panel, wxID_OK, "OK");  // Use OK instead of Close for dump frames.
    // button_sizer->Add(close_button, wxSizerFlags(0).Center().Border(wxALL, 10));  // Center the button, or left?
    button_sizer->Add(close_button, wxSizerFlags(0).Left().Border(wxALL, 10));  // Center the button, or left?
    // topsizer->Add(button_sizer, wxSizerFlags(0).Center());
    topsizer->Add(button_sizer, wxSizerFlags(0).Left());

    close_button->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
        if (event.GetId() == wxID_OK)
        {
            Close();
        }
        });

    panel->SetSizerAndFit(topsizer);
    CenterOnScreen();
    wxPoint dialog_position = GetScreenPosition();  // I think my position delta code is not working just yet ....
    dialog_position += m_position_delta;
    SetPosition(dialog_position);
    Show();
}



DumpFrame::~DumpFrame()
{}
