//
// Semantic DB 4
// Created 2023/4/8
// Updated 2023/4/8
// Author Garry Morrison
// License GPL v3
//

#include "SearchForOperatorDialog.h"

SearchForOperatorDialog::SearchForOperatorDialog(wxWindow* parent, long style)
	: wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	SetTitle("Search Operators");
	wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* header = new wxStaticText(this, wxID_ANY, "Search Operators");
	header->SetFont(wxFontInfo(12));

	wxStaticText* operator_type = new wxStaticText(this, wxID_ANY, "Operator type");
	operator_type->SetFont(wxFontInfo(12));

	m_simple_operator_checkbox = new wxCheckBox(this, wxID_ANY, "simple");
	m_compound_operator_checkbox = new wxCheckBox(this, wxID_ANY, "compound");
	m_function_operator_checkbox = new wxCheckBox(this, wxID_ANY, "function");

	m_simple_operator_checkbox->SetValue(true);
	m_compound_operator_checkbox->SetValue(true);
	m_function_operator_checkbox->SetValue(true);


	wxStaticText* usage_section = new wxStaticText(this, wxID_ANY, "Usage section");
	usage_section->SetFont(wxFontInfo(12));

	m_name_checkbox = new wxCheckBox(this, wxID_ANY, "name");
	m_description_checkbox = new wxCheckBox(this, wxID_ANY, "description");
	m_examples_checkbox = new wxCheckBox(this, wxID_ANY, "examples");
	
	m_name_checkbox->SetValue(true);
	m_description_checkbox->SetValue(true);
	m_examples_checkbox->SetValue(true);

	wxStaticText* search_header = new wxStaticText(this, wxID_ANY, "Search Term");
	search_header->SetFont(wxFontInfo(12));

	m_search_term_ctrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));

	wxButton* search_button = new wxButton(this, ID_Search_Operators_Button, "Search");
	wxButton* cancel_button = new wxButton(this, wxID_CANCEL, "Cancel");

	wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
	hbox->Add(search_button, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 5));
	hbox->Add(cancel_button, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 5));

	topsizer->Add(header, wxSizerFlags(0).Center().Border(wxALL, 10));
	topsizer->Add(operator_type, wxSizerFlags(0).Border(wxLEFT, 10));
	topsizer->Add(m_simple_operator_checkbox, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 20));
	topsizer->Add(m_compound_operator_checkbox, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 20));
	topsizer->Add(m_function_operator_checkbox, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 20));
	topsizer->AddSpacer(10);

	topsizer->Add(usage_section, wxSizerFlags(0).Border(wxLEFT, 10));
	topsizer->Add(m_name_checkbox, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 20));
	topsizer->Add(m_description_checkbox, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 20));
	topsizer->Add(m_examples_checkbox, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 20));
	topsizer->AddSpacer(10);

	topsizer->Add(search_header, wxSizerFlags(0).Border(wxLEFT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_search_term_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->Add(hbox, wxSizerFlags(0).Center().Border(wxALL, 10));
	
	search_button->Bind(wxEVT_BUTTON, &SearchForOperatorDialog::OnSearchButton, this);

	SetSizerAndFit(topsizer);
	CenterOnScreen();
	// ShowModal();
	Show();
}

void SearchForOperatorDialog::OnSearchButton(wxCommandEvent& event)
{
	wxString operator_types;
	if (m_simple_operator_checkbox->GetValue())
	{
		operator_types += "simple ";
	}
	if (m_compound_operator_checkbox->GetValue())
	{
		operator_types += "compound ";
	}
	if (m_function_operator_checkbox->GetValue())
	{
		operator_types += "function";
	}
	wxString usage_section;
	if (m_name_checkbox->GetValue())
	{
		usage_section += "name ";
	}
	if (m_description_checkbox->GetValue())
	{
		usage_section += "description ";
	}
	if (m_examples_checkbox->GetValue())
	{
		usage_section += "examples";
	}
	wxString search_term = m_search_term_ctrl->GetValue();
	wxMessageBox("Search button pressed\noperator types: " + operator_types + "\nusage section: " + usage_section + "\nsearch term: " + search_term);
}

SearchForOperatorDialog::~SearchForOperatorDialog()
{}
