//
// Semantic DB 4
// Created 2022/1/11
// Updated 2022/1/12
// Author Garry Morrison
// License GPL v3
//

#include "ActiveTableDialog.h"
extern SDB::Driver driver;


ActiveTableDialog::ActiveTableDialog(wxWindow* parent, long style)
	: wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	SetTitle("Active Table");
	wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* header = new wxStaticText(this, wxID_ANY, "Active Table");
	header->SetFont(wxFontInfo(14));

	wxStaticText* input_superposition_header = new wxStaticText(this, wxID_ANY, "Input superposition");
	input_superposition_header->SetFont(wxFontInfo(12));
	m_input_superposition_ctrl = new wxTextCtrl(this, wxID_ANY, "rel-kets[*]", wxDefaultPosition, wxSize(400, -1));

	wxStaticText* input_label_header = new wxStaticText(this, wxID_ANY, "Input label");
	input_label_header->SetFont(wxFontInfo(12));
	m_input_label_ctrl = new wxTextCtrl(this, wxID_ANY, "ket");

	wxStaticText* such_that_header = new wxStaticText(this, wxID_ANY, "Such-that operator (empty for none)");
	such_that_header->SetFont(wxFontInfo(12));
	m_such_that_ctrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString);

	wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* filter_header = new wxStaticText(this, wxID_ANY, "Filter");
	filter_header->SetFont(wxFontInfo(12));
	wxButton* usage_button = new wxButton(this, ID_Table_Usage, "Usage");
	// wxCheckBox* usage_checkbox = new wxCheckBox(this, wxID_ANY, "Usage");
	hbox1->Add(filter_header);
	hbox1->AddSpacer(20);
	// hbox1->Add(usage_checkbox);
	hbox1->Add(usage_button);

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

	wxBoxSizer* hbox4 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* sort_by_header = new wxStaticText(this, wxID_ANY, "Sort-by operator (empty for none)");
	sort_by_header->SetFont(wxFontInfo(12));
	m_sort_reverse_checkbox = new wxCheckBox(this, wxID_ANY, "reverse");
	hbox4->Add(sort_by_header);
	hbox4->AddSpacer(20);
	hbox4->Add(m_sort_reverse_checkbox);
	m_sort_by_ctrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, -1));


	wxStaticText* known_operators_header = new wxStaticText(this, wxID_ANY, "Select from known operators");
	known_operators_header->SetFont(wxFontInfo(12));
	wxArrayString known_operators;
	std::set<std::string> set_of_operators;
	for (ulong idx : driver.context.relevant_kets("*"))
	{
		for (ulong op_idx : driver.context.supported_ops(idx))
		{
			std::string op_label = ket_map.get_str(op_idx);
			set_of_operators.insert(op_label);
		}
	}
	for (const auto& op_label : set_of_operators)
	{
		known_operators.Add(op_label);
	}
	unsigned int content_size = known_operators.size();
	unsigned int dim = (unsigned int)(std::ceil(sqrt(double(content_size))));  // Given a size, find the smallest square with dimensions dim * dim.
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

	wxBoxSizer* hbox5 = new wxBoxSizer(wxHORIZONTAL);
	for (const auto& col : m_our_checkboxes)
	{
		hbox5->AddSpacer(10);
		hbox5->Add(col, wxSizerFlags(0).Center().Border(wxTOP | wxBOTTOM, 10));
	}
	hbox5->AddSpacer(10);

	wxBoxSizer* hbox6 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* command_text_header = new wxStaticText(this, wxID_ANY, "Command");
	command_text_header->SetFont(wxFontInfo(12));
	m_command_text_ctrl = new wxTextCtrl(this, wxID_ANY, "table[ket] rel-kets[*]", wxDefaultPosition, wxSize(250, -1));
	wxButton* generate_button = new wxButton(this, ID_Table_Generate, "Generate");
	hbox6->Add(command_text_header);
	hbox6->AddSpacer(20);
	hbox6->Add(generate_button);

	wxButton* run_button = new wxButton(this, ID_Table_Run, "Run");

	topsizer->Add(header, wxSizerFlags(0).Center().Border(wxALL, 10));
	topsizer->Add(input_superposition_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_input_superposition_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);
	topsizer->Add(input_label_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_input_label_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);
	topsizer->Add(such_that_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_such_that_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);

	topsizer->Add(hbox1, wxSizerFlags(0).Expand().Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(hbox2, wxSizerFlags(0).Expand().Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(hbox3, wxSizerFlags(0).Expand().Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);
	// topsizer->Add(sort_by_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->Add(hbox4, wxSizerFlags(0).Expand().Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_sort_by_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);
	topsizer ->Add(known_operators_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	if (content_size == 0)
	{
		wxString message = "There are no known operators in this context.";
		wxStaticText* static_message = new wxStaticText(this, wxID_ANY, message);
		topsizer->Add(static_message, wxSizerFlags(0).Left().Border(wxALL, 10));
	}
	topsizer->Add(hbox5, wxSizerFlags(0).Expand().Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);
	// topsizer->Add(command_text_header, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->Add(hbox6, wxSizerFlags(0).Expand().Left().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(5);
	topsizer->Add(m_command_text_ctrl, wxSizerFlags(0).Left().Expand().Border(wxLEFT | wxRIGHT, 10));
	topsizer->AddSpacer(10);
	topsizer->Add(run_button, wxSizerFlags(0).Left().Border(wxALL, 10));

	usage_button->Bind(wxEVT_BUTTON, &ActiveTableDialog::OnUsageButton, this);
	generate_button->Bind(wxEVT_BUTTON, &ActiveTableDialog::OnGenerateButton, this);
	run_button->Bind(wxEVT_BUTTON, &ActiveTableDialog::OnRunButton, this);

	SetSizerAndFit(topsizer);
	CenterOnScreen();
	// ShowModal();
	Show();
}

void ActiveTableDialog::OnUsageButton(wxCommandEvent& event)
{
	UsageFrame* usage_frame = new UsageFrame(this, "filter");
}

void ActiveTableDialog::OnGenerateButton(wxCommandEvent& event)
{
	GenerateCommand();
}

void ActiveTableDialog::GenerateCommand()
{
	wxString such_that;
	if (!m_such_that_ctrl->IsEmpty())
	{
		such_that = "such-that[" + m_such_that_ctrl->GetValue() + "] ";
	}
	wxString filter_sp;
	if (!m_lhs_ctrl->IsEmpty() && !m_rhs_ctrl->IsEmpty())  // Use filter now.
	{
		filter_sp = "filter(" + m_lhs_ctrl->GetValue() + ", " + m_rhs_ctrl->GetValue() + ") ";
	}
	wxString sort_by;
	if (!(m_sort_by_ctrl->GetValue().IsEmpty()))
	{
		sort_by = "sort-by[" + m_sort_by_ctrl->GetValue() + "] ";
	}
	wxString reverse_sort;
	if (m_sort_reverse_checkbox->IsChecked())
	{
		reverse_sort = "reverse ";
	}
	wxArrayInt checked_items_idx;
	m_checked_items.clear();
	m_checked_items.push_back(m_input_label_ctrl->GetValue().ToStdString());
	unsigned int list_idx = 0;
	for (const auto& check_box : m_our_checkboxes)
	{
		check_box->GetCheckedItems(checked_items_idx);
		for (const auto idx : checked_items_idx)
		{
			m_checked_items.push_back(m_our_arrays[list_idx][idx].ToStdString());
		}
		list_idx++;
	}
	std::string operators = join(m_checked_items, ", ");
	m_input_sp_str = reverse_sort + sort_by + filter_sp + such_that + m_input_superposition_ctrl->GetValue();
	wxString s = "table[" + operators + "] " + m_input_sp_str;
	m_command_text_ctrl->SetValue(s);
}

void ActiveTableDialog::OnRunButton(wxCommandEvent& event)
{
	// wxMessageBox("Run button pressed.");
	TableDialog* table_dialog = new TableDialog(this, m_checked_items, m_input_sp_str);
}

ActiveTableDialog::~ActiveTableDialog()
{}