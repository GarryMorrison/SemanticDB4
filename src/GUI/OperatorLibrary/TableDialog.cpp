//
// Semantic DB 4
// Created 2022/1/12
// Updated 2022/1/13
// Author Garry Morrison
// License GPL v3
//


#include "TableDialog.h"
extern SDB::Driver driver;

TableDialog::TableDialog(wxWindow* parent, std::vector<std::string>& operators, const std::string& input_sp_str, bool is_tidy, long style)
	: wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER), m_operators(operators)
{
	SetTitle("Table");
	wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* header = new wxStaticText(this, wxID_ANY, "Table");
	header->SetFont(wxFontInfo(14));
	topsizer->Add(header, wxSizerFlags(0).Center().Border(wxALL, 10));

	driver.result.clear();
	bool parse_success = driver.parse_string(input_sp_str + "\n");
	if (!parse_success)
	{
		wxMessageBox("Parse failed for: " + input_sp_str);
		return;
	}
	Superposition input_sp = driver.result.to_sp();

	m_grid_table = new wxGrid(this, wxID_ANY);
	m_grid_table->CreateGrid(input_sp.size(), operators.size());
	unsigned int list_idx = 0;
	for (const auto& op : operators)
	{
		m_grid_table->SetColLabelValue(list_idx, op);
		m_sort_ascending.push_back(-1);  // -1 for not sorted by this column. 0 for ascending, 1 for descending.
		list_idx++;
	}
	list_idx = 0;
	std::string k_label;
	for (const auto k : input_sp)  // Tidy this section!
	{
		if (!is_tidy)
		{
			k_label = k.label();
		}
		else
		{
			k_label = ket_map.get_str(ket_map.get_headless_idx(k.label_idx()));
		}
		m_grid_table->SetCellValue(list_idx, 0, k_label);
		list_idx++;
	}
	unsigned int column_idx = 1;
	unsigned int row_idx = 0;
	for (const auto k : input_sp)
	{
		std::vector<std::string> row_data;
		bool first_column = true;
		column_idx = 1;
		for (const auto& op : m_operators)
		{
			if (first_column)
			{
				first_column = false;
				if (!is_tidy)
				{
					row_data.push_back(k.label());
				}
				else
				{
					row_data.push_back(ket_map.get_str(ket_map.get_headless_idx(k.label_idx())));
				}
				continue;
			}
			ulong op_idx = ket_map.get_idx(op);
			std::string cell_value = driver.context.active_recall(op_idx, k.label_idx()).readable_display(is_tidy);
			m_grid_table->SetCellValue(row_idx, column_idx, cell_value);
			row_data.push_back(cell_value);
			column_idx++;
		}
		m_table_data.push_back(row_data);
		row_idx++;
	}
	m_grid_table->AutoSize();
	topsizer->Add(m_grid_table, wxSizerFlags(1).Expand().Border(wxALL, 10));
	topsizer->AddSpacer(10);

	m_grid_table->Bind(wxEVT_GRID_LABEL_LEFT_CLICK, &TableDialog::OnTableColumnClick, this);

	SetSizerAndFit(topsizer);
	CenterOnScreen();
	// ShowModal();
	Show();
}

void TableDialog::OnTableColumnClick(wxGridEvent& event)
{
	int column = event.GetCol();
	if (column < 0 || column >= m_operators.size()) { return; }
	int sorting_order = m_sort_ascending[column];
	bool sort_asc = true;
	switch (sorting_order) {
	case -1: {  // Currently not sorted by this column, so default to asc.
		sort_asc = true;
		break;
	}
	case 0: {  // Currently desc, so switch to asc.
		sort_asc = true;
		break;
	}
	case 1: {  // Currently asc, so switch to desc.
		sort_asc = false;
		break;
	}
	default: {  // Default is asc.
		sort_asc = true;
	}
	}
	m_sort_ascending[column] = sort_asc;

	// Sort the table:
	std::sort(m_table_data.begin(), m_table_data.end(), [column, sort_asc](std::vector<std::string>& row1, std::vector<std::string>& row2) {
		if (sort_asc)
		{
			return row1[column] < row2[column];
		}
		else
		{
			return row1[column] > row2[column];
		}
		});

	// Rebuild the table:
	unsigned int row_idx = 0;
	unsigned int column_idx = 0;
	for (const auto& row : m_table_data)
	{
		column_idx = 0;
		for (const auto& cell : row)
		{
			m_grid_table->SetCellValue(row_idx, column_idx, cell);
			column_idx++;
		}
		row_idx++;
	}
}

TableDialog::~TableDialog()
{}