//
// Semantic DB 4
// Created 2022/1/11
// Updated 2022/1/11
// Author Garry Morrison
// License GPL v3
//

#include "ActiveTableDialog.h"

ActiveTableDialog::ActiveTableDialog(wxWindow* parent, long style)
	: wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	SetTitle("Active Table");
	wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* header = new wxStaticText(this, wxID_ANY, "Active Table");
	header->SetFont(wxFontInfo(14));

	wxStaticText* input_superposition_header = new wxStaticText(this, wxID_ANY, "Input Superposition");
	input_superposition_header->SetFont(wxFontInfo(12));
	m_input_superposition_ctrl = new wxTextCtrl(this, wxID_ANY, "rel-kets[*]", wxDefaultPosition, wxSize(400, -1));

	wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* filter_header = new wxStaticText(this, wxID_ANY, "Filter");
	filter_header->SetFont(wxFontInfo(12));
	wxCheckBox* usage_checkbox = new wxCheckBox(this, wxID_ANY, "Usage");
	// hbox1->Add(filter_header, wxSizerFlags(1).Left());
	// hbox1->Add(usage_checkbox, wxSizerFlags(1).Right());
	hbox1->Add(filter_header);
	hbox1->AddSpacer(20);
	hbox1->Add(usage_checkbox);

	wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* lhs = new wxStaticText(this, wxID_ANY, "LHS");
	m_lhs_ctrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
	hbox2->Add(lhs, wxSizerFlags(0).Left().Border(wxTOP | wxRIGHT, 5));
	hbox2->Add(m_lhs_ctrl, wxSizerFlags(1).Left().Expand().Border(wxLEFT | wxRIGHT, 0));

	wxBoxSizer* hbox3 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* rhs = new wxStaticText(this, wxID_ANY, "RHS");
	m_rhs_ctrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
	hbox3->Add(rhs, wxSizerFlags(0).Left().Border(wxTOP | wxRIGHT, 5));
	hbox3->Add(m_rhs_ctrl, wxSizerFlags(1).Left().Expand().Border(wxLEFT | wxRIGHT, 0));

	wxStaticText* sort_by_header = new wxStaticText(this, wxID_ANY, "Sort-by operator (empty for none)");
	sort_by_header->SetFont(wxFontInfo(12));
	m_sort_by_ctrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, -1));


	wxStaticText* known_operators_header = new wxStaticText(this, wxID_ANY, "Known operators");
	known_operators_header->SetFont(wxFontInfo(12));
	wxArrayString known_operators;
	known_operators.Add("age");
	known_operators.Add("friends");
	known_operators.Add("spelling");
	unsigned int content_size = known_operators.size();
	unsigned int dim = (unsigned int)(std::ceil(sqrt(double(content_size))));  // Given a size, find the smallest square with dimensions dim * dim.
	if (content_size == 0)  // Wire in later!
	{
		wxString message = "There are no known operators in this context.";
		wxStaticText* static_message = new wxStaticText(this, wxID_ANY, message);
		// topsizer->Add(static_message, wxSizerFlags(0).Center().Border(wxALL, 10));
	}
	wxArrayString grid_data;
	for (unsigned int i = 0; i < content_size; i++)
	{
		grid_data.Add(known_operators[i]);
		if (((i + 1) % dim) == 0)
		{
			m_our_arrays.push_back(grid_data);
			grid_data.Clear();
		}
	}
	if (grid_data.size() > 0)
	{
		m_our_arrays.push_back(grid_data);
	}

	wxCheckListBox* col;
	unsigned int idx = 0;
	for (const auto& wxas : m_our_arrays)
	{
		col = new wxCheckListBox(this, idx, wxDefaultPosition, wxDefaultSize, wxas);
		m_our_checkboxes.push_back(col);
		idx++;
	}

	wxBoxSizer* hbox4 = new wxBoxSizer(wxHORIZONTAL);
	for (const auto& col : m_our_checkboxes)
	{
		hbox4->AddSpacer(10);
		hbox4->Add(col, wxSizerFlags(0).Center().Border(wxTOP | wxBOTTOM, 10));
	}
	hbox4->AddSpacer(10);

	wxStaticText* command_text_header = new wxStaticText(this, wxID_ANY, "Command");
	command_text_header->SetFont(wxFontInfo(12));
	m_command_text_ctrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, -1));

	wxButton* run_button = new wxButton(this, ID_Table_Run, "Run");

	topsizer->Add(header, wxSizerFlags(0).Center().Border(wxALL, 10));
	topsizer->Add(input_superposition_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_input_superposition_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);
	topsizer->Add(hbox1, wxSizerFlags(0).Expand().Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(hbox2, wxSizerFlags(0).Expand().Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(hbox3, wxSizerFlags(0).Expand().Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);
	topsizer->Add(sort_by_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_sort_by_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);
	topsizer ->Add(known_operators_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->Add(hbox4, wxSizerFlags(0).Expand().Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);
	topsizer->Add(command_text_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_command_text_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);
	topsizer->Add(run_button, wxSizerFlags(0).Left().Border(wxALL, 10));

	SetSizerAndFit(topsizer);
	CenterOnScreen();
	ShowModal();
}

ActiveTableDialog::~ActiveTableDialog()
{}