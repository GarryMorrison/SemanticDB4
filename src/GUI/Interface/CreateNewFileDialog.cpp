//
// Semantic DB 4
// Created 2022/1/11
// Updated 2022/1/11
// Author Garry Morrison
// License GPL v3
//

#include "CreateNewFileDialog.h"

CreateNewFileDialog::CreateNewFileDialog(wxWindow* parent, long style)
	: wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	SetTitle("Create New File");
	wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* header = new wxStaticText(this, wxID_ANY, "Create New File");
	header->SetFont(wxFontInfo(12));
	wxStaticText* filename_header = new wxStaticText(this, wxID_ANY, "Filename");
	m_filename_ctrl = new wxTextCtrl(this, wxID_ANY, ".sw4", wxDefaultPosition, wxSize(250, -1));
	// m_filename_ctrl->SelectNone();  // These two don't seem to work ... 
	// m_filename_ctrl->SetInsertionPoint(0);
	wxStaticText* context_header = new wxStaticText(this, wxID_ANY, "Context (empty for none)");
	m_context_ctrl = new wxTextCtrl(this, wxID_ANY);
	topsizer->Add(header, wxSizerFlags(0).Center().Border(wxALL, 10));
	topsizer->Add(filename_header, wxSizerFlags(0).Left().Border(wxALL, 10));
	topsizer->Add(m_filename_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);
	topsizer->Add(context_header, wxSizerFlags(0).Left().Border(wxALL, 10));
	topsizer->Add(m_context_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);

	wxBoxSizer* button_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* create_button = new wxButton(this, ID_Create_File, "Create");
	wxButton* cancel_button = new wxButton(this, wxID_CANCEL, "Cancel");
	button_sizer->Add(create_button);
	button_sizer->AddSpacer(10);
	button_sizer->Add(cancel_button);
	topsizer->Add(button_sizer, wxSizerFlags(0).Center().Border(wxALL, 10));

	create_button->Bind(wxEVT_BUTTON, &CreateNewFileDialog::OnCreateButton, this);

	SetSizerAndFit(topsizer);
	CenterOnScreen();
	ShowModal();
}

void CreateNewFileDialog::OnCreateButton(wxCommandEvent& event)
{
	m_filename = m_filename_ctrl->GetLineText(0);
	m_context_name = m_context_ctrl->GetLineText(0);
	Close();
}

wxString CreateNewFileDialog::GetFilename()
{
	return m_filename;
}

wxString CreateNewFileDialog::GetContextname()
{
	return m_context_name;
}

CreateNewFileDialog::~CreateNewFileDialog()
{}