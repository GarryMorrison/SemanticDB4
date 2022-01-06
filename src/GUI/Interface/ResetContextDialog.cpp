//
// Semantic DB 4
// Created 2022/1/6
// Updated 2022/1/6
// Author Garry Morrison
// License GPL v3
//

#include "ResetContextDialog.h"

ResetContextDialog::ResetContextDialog(wxWindow* parent, const wxString& title, const wxString& message, long style)
	: wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	SetTitle(title);
	wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* message_text = new wxStaticText(this, wxID_ANY, message);
	topsizer->Add(message_text, wxSizerFlags(0).Center().Border(wxALL, 20));

	wxBoxSizer* button_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* yes_button = new wxButton(this, wxID_OK, "Yes");
	wxButton* no_button = new wxButton(this, wxID_CANCEL, "No");
	button_sizer->Add(yes_button, wxSizerFlags(0).Center().Border(wxALL, 10));
	button_sizer->Add(no_button, wxSizerFlags(0).Center().Border(wxALL, 10));
	topsizer->Add(button_sizer, wxSizerFlags(0).Center().Border(wxALL, 10));

	SetSizerAndFit(topsizer);
	CenterOnScreen();
	// ShowModal();
}

ResetContextDialog::~ResetContextDialog()
{}