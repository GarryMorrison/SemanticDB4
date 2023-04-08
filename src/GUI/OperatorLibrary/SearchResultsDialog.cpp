//
// Semantic DB 4
// Created 2023/4/8
// Updated 2023/4/8
// Author Garry Morrison
// License GPL v3
//


#include "SearchResultsDialog.h"

SearchResultsDialog::SearchResultsDialog(wxWindow* parent, bool simple, bool compound, bool function, bool name, bool description, bool examples, bool seealso, wxString search_term, long style)
	: wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	SetTitle("Search Results");
	wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* header = new wxStaticText(this, wxID_ANY, "Search Results");
	header->SetFont(wxFontInfo(12));

	// wxStaticText* tmp_text = new wxStaticText(this, wxID_ANY, search_term);

	std::set<std::string> operator_search_results = operator_usage_map.search_usage_map(search_term.ToStdString(), name, description, examples, seealso);
	std::set<std::string> operator_search_results_filtered;
	for (const auto& s : operator_search_results)
	{
		ulong s_idx = ket_map.get_idx(s);
		if (simple && fn_map.set_simple_operators.find(s_idx) != fn_map.set_simple_operators.end())
		{
			operator_search_results_filtered.insert(s);
		}
		if (compound && fn_map.set_compound_operators.find(s_idx) != fn_map.set_compound_operators.end())
		{
			operator_search_results_filtered.insert(s);
		}
		if (function && fn_map.set_function_operators.find(s_idx) != fn_map.set_function_operators.end())
		{
			operator_search_results_filtered.insert(s);
		}
	}
	for (const auto& s : operator_search_results_filtered)
	{
		m_operator_list.Add(s);
	}

	m_matching_operators = new wxCheckListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_operator_list);

	wxButton* launch_usage_button = new wxButton(this, ID_Launch_Usage_Button, "Launch Usage");
	wxButton* cancel_button = new wxButton(this, wxID_CANCEL, "Cancel");

	wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
	hbox->Add(launch_usage_button, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 5));
	hbox->Add(cancel_button, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 5));

	topsizer->Add(header, wxSizerFlags(0).Center().Border(wxALL, 10));
	// topsizer->Add(tmp_text);
	topsizer->Add(m_matching_operators, wxSizerFlags(0).Center().Border(wxALL, 10));
	topsizer->Add(hbox, wxSizerFlags(0).Center().Border(wxALL, 10));

	launch_usage_button->Bind(wxEVT_BUTTON, &SearchResultsDialog::OnLaunchUsageButton, this);

	SetSizerAndFit(topsizer);
	CenterOnScreen();
	// ShowModal();
	Show();

}



void SearchResultsDialog::OnLaunchUsageButton(wxCommandEvent& event)
{
	size_t total_operator_count = m_operator_list.GetCount();
	wxString selected_operators;
	for (size_t i = 0; i < total_operator_count; i++)
	{
		if (m_matching_operators->IsChecked(i))
		{
			// selected_operators += m_operator_list.Item(i) + ", ";
			UsageFrame* dlg = new UsageFrame(this, m_operator_list.Item(i).ToStdString());
		}
	}
	// wxMessageBox("Launch usage button pressed for: " + selected_operators);
}

SearchResultsDialog::~SearchResultsDialog()
{}
