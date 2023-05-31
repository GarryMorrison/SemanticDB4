//
// Semantic DB 4
// Created 2022/1/22
// Updated 2022/1/22
// Author Garry Morrison
// License GPL v3
//


#include "IfThenMachineDialog.h"
wxDEFINE_EVENT(EVT_INSERT_IFTHEN_OPERATOR, wxCommandEvent);


IfThenOperatorDialog::IfThenOperatorDialog(wxWindow* parent)
	: wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	SetTitle("If-then operator");
	wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* header = new wxStaticText(this, wxID_ANY, "Create if-then operator");
	header->SetFont(wxFontInfo(14));

	wxStaticText* encoder_header = new wxStaticText(this, wxID_ANY, "Encoder");
	encoder_header->SetFont(wxFontInfo(12));
	m_encoder_ctrl = new wxTextCtrl(this, wxID_ANY, "ssplit[\" \"]", wxDefaultPosition, wxSize(200, -1));

	wxStaticText* pattern_operator_header = new wxStaticText(this, wxID_ANY, "Pattern operator (required)");
	pattern_operator_header->SetFont(wxFontInfo(12));
	m_pattern_operator_ctrl = new wxTextCtrl(this, wxID_ANY, "pattern");

	wxStaticText* drop_below_header = new wxStaticText(this, wxID_ANY, "Drop below threshold");
	drop_below_header->SetFont(wxFontInfo(12));
	m_drop_threshold_ctrl = new wxSpinCtrlDouble(this, wxID_ANY, "0.5");
	m_drop_threshold_ctrl->SetRange(0, 1);
	m_drop_threshold_ctrl->SetDigits(2);
	m_drop_threshold_ctrl->SetIncrement(0.05);
	m_drop_threshold_ctrl->SetValue(0.5);

	wxStaticText* then_operator_header = new wxStaticText(this, wxID_ANY, "Then operator");
	then_operator_header->SetFont(wxFontInfo(12));
	m_then_operator_ctrl = new wxTextCtrl(this, wxID_ANY, "then");

	wxStaticText* machine_name_header = new wxStaticText(this, wxID_ANY, "Operator name (required)");
	machine_name_header->SetFont(wxFontInfo(12));
	m_machine_operator_ctrl = new wxTextCtrl(this, wxID_ANY, "predict");

	wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
	wxButton* insert_button = new wxButton(this, ID_If_Then_Insert_Operator, "Insert");
	wxButton* close_button = new wxButton(this, wxID_CANCEL, "Close");
	hbox1->Add(insert_button);
	hbox1->AddSpacer(10);
	hbox1->Add(close_button);


	topsizer->Add(header, wxSizerFlags(0).Center().Border(wxALL, 10));
	topsizer->Add(encoder_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_encoder_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);

	topsizer->Add(pattern_operator_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_pattern_operator_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);

	topsizer->Add(drop_below_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_drop_threshold_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);

	topsizer->Add(then_operator_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_then_operator_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);

	topsizer->Add(machine_name_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_machine_operator_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);

	topsizer->Add(hbox1, wxSizerFlags(0).Left().Border(wxALL, 10));

	insert_button->Bind(wxEVT_BUTTON, &IfThenOperatorDialog::OnInsertButton, this);


	SetSizerAndFit(topsizer);
	CenterOnScreen();
	Show();
}

void IfThenOperatorDialog::OnInsertButton(wxCommandEvent& event)
{
	wxString operator_string = GenerateOperator();
	if (operator_string.IsEmpty())
	{
		return;
	}
	wxCommandEvent our_event(EVT_INSERT_IFTHEN_OPERATOR);
	our_event.SetString(operator_string);
	wxPostEvent(this, our_event);
}

wxString IfThenOperatorDialog::GenerateOperator()
{
	wxString operator_string;
	if (m_pattern_operator_ctrl->GetValue().IsEmpty())
	{
		wxMessageBox("Please provide a pattern operator.");
		return operator_string;
	}
	if (m_machine_operator_ctrl->GetValue().IsEmpty())
	{
		wxMessageBox("Please provide an if-then machine operator name.");
		return operator_string;
	}
	wxString then_operator;
	if (!m_then_operator_ctrl->GetValue().IsEmpty())
	{
		then_operator = m_then_operator_ctrl->GetValue() + " ";
	}
	wxString drop_below_operator;
	if (m_drop_threshold_ctrl->GetValue() > 0)
	{
		drop_below_operator = "drop-below[" + std::to_string(m_drop_threshold_ctrl->GetValue()) + "] ";
	}
	wxString similar_input_operator = "similar-input[" + m_pattern_operator_ctrl->GetValue() + "] ";
	wxString encoder_operator;
	if (!m_encoder_ctrl->GetValue().IsEmpty())
	{
		encoder_operator = m_encoder_ctrl->GetValue() + " ";
	}
	operator_string = m_machine_operator_ctrl->GetValue() + " |*> #=> " + then_operator + drop_below_operator + similar_input_operator + encoder_operator + "|_self>\n";
	return operator_string;
}


IfThenOperatorDialog::~IfThenOperatorDialog()
{}