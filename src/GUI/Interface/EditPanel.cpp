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

	m_aui_notebook = new wxAuiNotebook(this, wxID_ANY);
	
	// Sample content:
	wxTextCtrl* textCtrl1 = new wxTextCtrl(m_aui_notebook, wxID_ANY, "Enter your code here ... \n");
	m_aui_notebook->AddPage(textCtrl1, "empty-file.sw4", true);

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

void EditPanel::AddPage(wxWindow* page, const wxString& caption, bool select)
{
	m_aui_notebook->AddPage(page, caption, select);
}

EditPanel::~EditPanel()
{}