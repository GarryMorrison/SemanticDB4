//
// Semantic DB 4
// Created 2023/4/9
// Updated 2023/4/14
// Author Garry Morrison
// License GPL v3
//

#include "GenerateDocsDialog.h"



GenerateDocsDialog::GenerateDocsDialog(wxWindow* parent, long style)
	: wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	SetTitle("Generate Docs");
	wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* header = new wxStaticText(this, wxID_ANY, "Generate Docs");
	header->SetFont(wxFontInfo(12));

	/*
	wxStaticText* docs_type = new wxStaticText(this, wxID_ANY, "Type");
	docs_type->SetFont(wxFontInfo(12));

	m_text_radio = new wxRadioButton(this, wxID_ANY, "text");
	m_html_radio = new wxRadioButton(this, wxID_ANY, "html");
	m_html_radio->SetValue(true);

	m_linkify_checkbox = new wxCheckBox(this, wxID_ANY, "linkify", wxDefaultPosition, wxDefaultSize, wxCHK_3STATE);
	// linkify_checkbox->Set3StateValue(wxCHK_UNDETERMINED);  // I don't think this is what we want.
	m_linkify_checkbox->Set3StateValue(wxCHK_CHECKED);

	wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
	hbox1->Add(m_html_radio, wxSizerFlags(0).Border(wxRIGHT, 5));
	hbox1->Add(m_linkify_checkbox, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 5));
	*/

	wxStaticText* docs_templates = new wxStaticText(this, wxID_ANY, "Templates");
	docs_templates->SetFont(wxFontInfo(12));
	m_template_dir_picker = new wxDirPickerCtrl(this, wxID_ANY, "", wxDirSelectorPromptStr, wxDefaultPosition, wxSize(350, -1));

	wxStaticText* docs_examples = new wxStaticText(this, wxID_ANY, "sw examples (empty for none)");
	docs_examples->SetFont(wxFontInfo(12));
	m_example_dir_picker = new wxDirPickerCtrl(this, wxID_ANY, "", wxDirSelectorPromptStr, wxDefaultPosition, wxSize(350, -1));

	wxStaticText* docs_destination = new wxStaticText(this, wxID_ANY, "Destination");
	docs_destination->SetFont(wxFontInfo(12));
	m_dir_picker = new wxDirPickerCtrl(this, wxID_ANY, "", wxDirSelectorPromptStr, wxDefaultPosition, wxSize(350, -1));

	wxStaticText* overwrite_files = new wxStaticText(this, wxID_ANY, "Overwrite files");
	overwrite_files->SetFont(wxFontInfo(12));

	m_yes_to_all_radio = new wxRadioButton(this, wxID_ANY, "yes to all", wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	m_warn_radio = new wxRadioButton(this, wxID_ANY, "warn");
	m_no_radio = new wxRadioButton(this, wxID_ANY, "no");
	m_warn_radio->SetValue(true);

	wxButton* generate_button = new wxButton(this, ID_Search_Operators_Button, "Generate");
	wxButton* cancel_button = new wxButton(this, wxID_CANCEL, "Cancel");

	wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
	hbox2->Add(generate_button, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 5));
	hbox2->Add(cancel_button, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 5));

	topsizer->Add(header, wxSizerFlags(0).Center().Border(wxALL, 10));
	/*
	topsizer->Add(docs_type, wxSizerFlags(0).Border(wxLEFT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_text_radio, wxSizerFlags(0).Border(wxLEFT, 20));
	topsizer->Add(hbox1, wxSizerFlags(0).Border(wxLEFT, 20));
	topsizer->AddSpacer(10);
	*/
	topsizer->Add(overwrite_files, wxSizerFlags(0).Border(wxLEFT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_yes_to_all_radio, wxSizerFlags(0).Border(wxLEFT, 20));
	topsizer->Add(m_warn_radio, wxSizerFlags(0).Border(wxLEFT, 20));
	topsizer->Add(m_no_radio, wxSizerFlags(0).Border(wxLEFT, 20));

	topsizer->AddSpacer(10);
	topsizer->Add(docs_templates, wxSizerFlags(0).Border(wxLEFT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_template_dir_picker, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 10));

	topsizer->AddSpacer(10);
	topsizer->Add(docs_examples, wxSizerFlags(0).Border(wxLEFT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_example_dir_picker, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 10));

	topsizer->AddSpacer(10);
	topsizer->Add(docs_destination, wxSizerFlags(0).Border(wxLEFT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_dir_picker, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 10));
	topsizer->Add(hbox2, wxSizerFlags(0).Center().Border(wxALL, 10));

	
	// m_text_radio->Bind(wxEVT_RADIOBUTTON, &GenerateDocsDialog::OnTextRadioButton, this);
	// m_html_radio->Bind(wxEVT_RADIOBUTTON, &GenerateDocsDialog::OnHtmlRadioButton, this);

	// run_button->Bind(wxEVT_BUTTON, &CommandPanel::OnRunButtonDown, this);
	generate_button->Bind(wxEVT_BUTTON, &GenerateDocsDialog::OnGenerateButtonDown, this);

	SetSizerAndFit(topsizer);
	CenterOnScreen();
	// ShowModal();
	Show();
}

/*
void GenerateDocsDialog::OnTextRadioButton(wxCommandEvent& event)
{
	// wxMessageBox("Text radio button pressed");
	m_linkify_checkbox->SetValue(false);
}

void GenerateDocsDialog::OnHtmlRadioButton(wxCommandEvent& event)
{
	// wxMessageBox("Html radio button pressed");
	m_linkify_checkbox->SetValue(true);
}
*/

void GenerateDocsDialog::OnGenerateButtonDown(wxCommandEvent& event)
{
	wxString template_path = m_template_dir_picker->GetPath();
	wxString examples_path = m_example_dir_picker->GetPath();
	wxString new_docs_path = m_dir_picker->GetPath();
	if (template_path.IsEmpty() || new_docs_path.IsEmpty())
	{
		wxMessageBox("Please provide a template and destination path.");
	}
	else
	{
		/*
		wxString docs_type_option;
		if (m_text_radio->GetValue())
		{
			docs_type_option += "text";
		}
		else if (m_html_radio->GetValue())
		{
			docs_type_option += "html";
			if (m_linkify_checkbox->GetValue())
			{
				docs_type_option += ", linkify";
			}
		}
		*/
		wxString overwrite_files_style;
		if (m_yes_to_all_radio->GetValue())
		{
			overwrite_files_style = "yes to all";
		}
		else if (m_warn_radio->GetValue())
		{
			overwrite_files_style = "warn";
		}
		else if (m_no_radio->GetValue())
		{
			overwrite_files_style = "no";
		}
		/*
		wxMessageBox("Generate button pressed\nTemplate path: " + template_path + "\nExamples path: " + examples_path + "\nDocs path : " + new_docs_path + "\noption : " + docs_type_option + "\noverwrite files : " + overwrite_files_style);
		GenerateDocs docgen = GenerateDocs(m_text_radio->GetValue(), 
			m_html_radio->GetValue(), 
			m_linkify_checkbox->GetValue(), 
			m_yes_to_all_radio->GetValue(),
			m_warn_radio->GetValue(),
			m_no_radio->GetValue(),
			template_path, 
			examples_path, 
			new_docs_path);
		*/
		wxMessageBox("Generate button pressed\nTemplate path: " + template_path + "\nExamples path: " + examples_path + "\nDocs path : " + new_docs_path + "\noverwrite files : " + overwrite_files_style);
		GenerateDocs docgen = GenerateDocs(
			m_yes_to_all_radio->GetValue(),
			m_warn_radio->GetValue(),
			m_no_radio->GetValue(),
			template_path,
			examples_path,
			new_docs_path);
	}
}

GenerateDocsDialog::~GenerateDocsDialog()
{
}

