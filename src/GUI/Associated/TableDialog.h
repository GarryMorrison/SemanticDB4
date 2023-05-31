//
// Semantic DB 4
// Created 2022/1/12
// Updated 2022/1/13
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../SDB_GUI.h"

class TableDialog : public wxDialog {

public:
	TableDialog(wxWindow* parent, std::vector<std::string>& operators, const std::string& input_sp_str, bool is_tidy = false, long style = 0);
	TableDialog(wxWindow* parent, const std::vector<ulong>& operators, const Superposition& input_sp, bool is_tidy = false, long style = 0);

	void OnTableColumnClick(wxGridEvent& event);

	~TableDialog();
private:
	wxGrid* m_grid_table;
	// std::vector<std::string>& m_operators;
	std::vector<std::string> m_operators;
	std::vector<int> m_sort_ascending;
	std::vector<std::vector<std::string>> m_table_data;
};
