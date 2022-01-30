//
// Semantic DB 4
// Created 2021/12/28
// Updated 2021/12/28
// Author Garry Morrison
// License GPL v3
//

#include "UsageFrame.h"

// Improved UsageFrame:
UsageFrame::UsageFrame(wxWindow* parent, std::string op, wxPoint position_delta, long style)
    : wxFrame(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(700, 710), style | wxDEFAULT_FRAME_STYLE | wxRESIZE_BORDER)
{
    if (!operator_usage_map.usage_is_defined(op))
    {
        wxMessageBox("No usage info available for operator: " + op);
        return;
    }
    OpUsageInfo* usageInfo = operator_usage_map.get_usage_info(op);
    if (!usageInfo)
    {
        wxMessageBox("No usage info found.");
        return;
    }
    std::set<char> split_chars = { ' ', ',', '\n', '[', '(' };
    // std::set<std::string> clickable_words = fn_map.list_of_operator_names;  // What about adding fn_map.list_of_statements too?
    std::set<std::string> clickable_words = fn_map.list_of_operator_and_statement_names;


    wxPanel* panel = new wxPanel(this, wxID_ANY);

    SetTitle("Operator Usage Info");
    wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);
    // panel->SetSizer(topsizer);



    topsizer->Add(new wxStaticText(panel, wxID_ANY, "Name", wxDefaultPosition, wxDefaultSize), wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
    topsizer->Add(new wxTextCtrl(panel, wxID_ANY, usageInfo->Name, wxDefaultPosition, wxDefaultSize, wxTE_READONLY), wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));

    topsizer->AddSpacer(10);
    topsizer->Add(new wxStaticText(panel, wxID_ANY, "Description", wxDefaultPosition, wxDefaultSize), wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
    topsizer->Add(new wxTextCtrl(panel, wxID_ANY, usageInfo->Description, wxDefaultPosition, wxSize(600, -1), wxTE_READONLY | wxTE_MULTILINE), wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));


    topsizer->AddSpacer(10);
    topsizer->Add(new wxStaticText(panel, wxID_ANY, "Examples", wxDefaultPosition, wxDefaultSize), wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
    // topsizer->Add(new wxTextCtrl(this, wxID_ANY, *usageInfo->Examples, wxDefaultPosition, wxSize(600, -1), wxTE_READONLY | wxTE_MULTILINE), wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
    wxRichTextAttr defaultAttr = wxRichTextAttr();
    defaultAttr.SetFontFamily(wxFONTFAMILY_TELETYPE);
    // defaultAttr.SetFontStyle(wxFONTSTYLE_NORMAL);
    // defaultAttr.SetFontWeight(wxFONTWEIGHT_NORMAL);
    // defaultAttr.SetTextColour(*wxRED);
    defaultAttr.SetFont(defaultAttr.GetFont());
    LinkedTextCtrl* examplesCtrl = new LinkedTextCtrl(panel, wxID_ANY, clickable_words, split_chars, defaultAttr, usageInfo->Examples, wxDefaultPosition, wxSize(600, 300), wxTE_READONLY | wxTE_MULTILINE);
    topsizer->Add(examplesCtrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));

    LinkedTextCtrl* seeAlsoCtrl = new LinkedTextCtrl(panel, wxID_ANY, clickable_words, split_chars, defaultAttr, usageInfo->SeeAlso, wxDefaultPosition, wxSize(400, 50), wxTE_READONLY);

    topsizer->AddSpacer(10);
    topsizer->Add(new wxStaticText(panel, wxID_ANY, "See Also", wxDefaultPosition, wxDefaultSize), wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
    // topsizer->Add(new LinkedTextCtrl(this, wxID_ANY, clickable_words, split_chars, *usageInfo->SeeAlso, wxDefaultPosition, wxSize(400, 50), wxTE_READONLY), wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
    topsizer->Add(seeAlsoCtrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));

    examplesCtrl->Bind(wxEVT_TEXT_URL, [=](wxTextUrlEvent& event) {
        std::string the_operator = examplesCtrl->GetRange(event.GetURLStart(), event.GetURLEnd() + 1).ToStdString();  // Extract this to a function later?
        UsageFrame* dlg = new UsageFrame(this, the_operator, position_delta + wxPoint(40, 40));
        });

    examplesCtrl->Bind(wxEVT_MOTION, [=](wxMouseEvent& event) {
        examplesCtrl->SetFocus();
        examplesCtrl->GetCaret()->Hide();
        });

    seeAlsoCtrl->Bind(wxEVT_TEXT_URL, [=](wxTextUrlEvent& event) {
        wxString link = event.GetString();
        std::string the_operator = seeAlsoCtrl->GetRange(event.GetURLStart(), event.GetURLEnd() + 1).ToStdString();  // Extract this to a function later?
        UsageFrame* dlg = new UsageFrame(this, the_operator, position_delta + wxPoint(40, 40));
        });

    seeAlsoCtrl->Bind(wxEVT_MOTION, [=](wxMouseEvent& event) {
        seeAlsoCtrl->SetFocus();
        seeAlsoCtrl->GetCaret()->Hide();
        });

    wxButton* OK_Button = new wxButton(panel, wxID_OK, "OK");
    topsizer->Add(OK_Button, wxSizerFlags(0).Border(wxALL, 10));

    OK_Button->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
        if (event.GetId() == wxID_OK)
        {
            Close();
        }
        });

    panel->SetSizerAndFit(topsizer);
    CenterOnScreen();
    wxPoint dialog_position = GetScreenPosition();
    dialog_position += position_delta;
    SetPosition(dialog_position);
    Show();
}


UsageFrame::~UsageFrame()
{}


