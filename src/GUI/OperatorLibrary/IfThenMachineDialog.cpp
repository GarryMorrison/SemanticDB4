//
// Semantic DB 4
// Created 2022/1/22
// Updated 2022/1/22
// Author Garry Morrison
// License GPL v3
//


#include "IfThenMachineDialog.h"

IfThenMachineDialog::IfThenMachineDialog(wxWindow* parent)
	: wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	SetTitle("If-then machine");
	wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* header = new wxStaticText(this, wxID_ANY, "Create if-then machine");
	header->SetFont(wxFontInfo(14));

	wxStaticText* node_label_header = new wxStaticText(this, wxID_ANY, "Node label");
	node_label_header->SetFont(wxFontInfo(12));
	m_node_label_ctrl = new wxTextCtrl(this, wxID_ANY, "node", wxDefaultPosition, wxSize(200, -1));

	wxStaticText* pattern_operator_header = new wxStaticText(this, wxID_ANY, "Pattern operator");
	pattern_operator_header->SetFont(wxFontInfo(12));
	m_pattern_operator_ctrl = new wxTextCtrl(this, wxID_ANY, "pattern");

	wxStaticText* then_operator_header = new wxStaticText(this, wxID_ANY, "Then operator");
	then_operator_header->SetFont(wxFontInfo(12));
	m_then_operator_ctrl = new wxTextCtrl(this, wxID_ANY, "then");

	wxStaticText* node_starting_index_header = new wxStaticText(this, wxID_ANY, "Node starting index");
	node_starting_index_header->SetFont(wxFontInfo(12));
	m_starting_index_ctrl = new wxSpinCtrl(this, wxID_ANY, "1");

	wxStaticText* number_of_patterns_header = new wxStaticText(this, wxID_ANY, "Number of patterns");
	number_of_patterns_header->SetFont(wxFontInfo(12));
	m_pattern_count_ctrl = new wxSpinCtrl(this, wxID_ANY, "1");


	wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
	wxButton* insert_button = new wxButton(this, ID_If_Then_Insert, "Insert");
	wxButton* close_button = new wxButton(this, wxID_CANCEL, "Close");
	hbox1->Add(insert_button);
	hbox1->AddSpacer(10);
	hbox1->Add(close_button);

	topsizer->Add(header, wxSizerFlags(0).Center().Border(wxALL, 10));
	topsizer->Add(node_label_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_node_label_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);

	topsizer->Add(pattern_operator_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_pattern_operator_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);

	topsizer->Add(then_operator_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_then_operator_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);

	topsizer->Add(node_starting_index_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_starting_index_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);

	topsizer->Add(number_of_patterns_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_pattern_count_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);


	topsizer->Add(hbox1, wxSizerFlags(0).Left().Border(wxALL, 10));

	insert_button->Bind(wxEVT_BUTTON, &IfThenMachineDialog::OnInsertButton, this);


	SetSizerAndFit(topsizer);
	CenterOnScreen();
	Show();
}

void IfThenMachineDialog::OnInsertButton(wxCommandEvent& event)
{
	wxMessageBox("if-then insert pressed:\n" + GenerateMachine());
}

wxString IfThenMachineDialog::GenerateMachine()
{
	wxString node_label = m_node_label_ctrl->GetValue();
	wxString pattern_operator = m_pattern_operator_ctrl->GetValue();
	wxString then_operator = m_then_operator_ctrl->GetValue();
	int starting_idx = m_starting_index_ctrl->GetValue();
	int pattern_count = m_pattern_count_ctrl->GetValue();
	wxString machine_string = "\n\n";
	for (int i = 1; i <= pattern_count; i++)
	{
		machine_string += wxString::Format("%s |%s: %d: %d> => $%d\n", pattern_operator, node_label, starting_idx, i, i);
	}
	machine_string += wxString::Format("%s |%s: %d: *> => $%d\n\n", then_operator, node_label, starting_idx, pattern_count+1);
	return machine_string;
}

IfThenMachineDialog::~IfThenMachineDialog()
{}
