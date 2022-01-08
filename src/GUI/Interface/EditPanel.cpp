//
// Semantic DB 4
// Created 2022/1/8
// Updated 2022/1/8
// Author Garry Morrison
// License GPL v3
//

#include "EditPanel.h"

EditPanel::EditPanel(wxPanel* parent, wxWindowID id)
	: wxPanel(parent, id, wxDefaultPosition, wxSize(400, 300), 0)
{
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
	wxButton* run_button = new wxButton(this, ID_Edit_Run, "Run");
	vbox->AddSpacer(5);
	vbox->Add(run_button, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	vbox->AddSpacer(5);

	// unsigned int x = 0;
	// unsigned int y = 0;
	// parent->GetSize(&x, &y);
	// m_aui_notebook = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition, wxSize(x, y));
	m_aui_notebook = new wxAuiNotebook(this, wxID_ANY);
	// m_aui_notebook = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition, wxSize(400, 300));
	

	// Sample content:
	wxTextCtrl* textCtrl1 = new wxTextCtrl(m_aui_notebook, wxID_ANY, "Enter your code here ... \n");
	m_aui_notebook->AddPage(textCtrl1, "empty-file.sw4");
	// wxTextCtrl* textCtrl2 = new wxTextCtrl(m_aui_notebook, wxID_ANY, "Tab 2 Contents");
	// m_aui_notebook->AddPage(textCtrl2, "Tab 2");

	// wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
	// hbox->Add(m_aui_notebook, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	// vbox->Add(hbox, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));

	vbox->Add(m_aui_notebook, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);
	vbox->AddSpacer(10);
	SetSizerAndFit(vbox);
	// Layout();

	run_button->Bind(wxEVT_BUTTON, &EditPanel::OnRunButtonDown, this);
}

void EditPanel::OnRunButtonDown(wxCommandEvent& event)
{
	wxMessageBox("Run button clicked");
}

EditPanel::~EditPanel()
{}