//
// Semantic DB 4
// Created 2022/1/12
// Updated 2022/1/12
// Author Garry Morrison
// License GPL v3
//


#include "TableDialog.h"
extern SDB::Driver driver;

TableDialog::TableDialog(wxWindow* parent, std::vector<std::string>& operators, const std::string& input_sp_str, long style)
	: wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER), m_operators(operators)
{
	SetTitle("Active Table");
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

	// wxGridStringTable* grid_table = new wxGridStringTable(operators.size(), operators.size());  // Nope. Can't get it to work.
	m_grid_table = new wxGrid(this, wxID_ANY);
	m_grid_table->CreateGrid(input_sp.size(), operators.size());
	unsigned int list_idx = 0;
	for (const auto& op : operators)
	{
		m_grid_table->SetColLabelValue(list_idx, op);
		list_idx++;
	}
	list_idx = 0;
	for (const auto k : input_sp)
	{
		m_grid_table->SetCellValue(list_idx, 0, k.label());
		list_idx++;
	}
	/*
	bool first_column = true;
	unsigned int column_idx = 1;
	unsigned int row_idx = 0;
	for (const auto& op : operators)
	{
		ulong op_idx = ket_map.get_idx(op);
		if (first_column)
		{
			first_column = false;
			continue;
		}
		row_idx = 0;
		for (const auto k : input_sp)
		{
			// std::string cell_value = driver.context.active_recall(op_idx, k.label_idx()).to_string();
			std::string cell_value = driver.context.active_recall(op_idx, k.label_idx()).readable_display();
			grid_table->SetCellValue(row_idx, column_idx, cell_value);
			row_idx++;
		}
		column_idx++;
	}
	*/
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
				row_data.push_back(k.label());
				continue;
			}
			ulong op_idx = ket_map.get_idx(op);
			std::string cell_value = driver.context.active_recall(op_idx, k.label_idx()).readable_display();
			m_grid_table->SetCellValue(row_idx, column_idx, cell_value);
			row_data.push_back(cell_value);
			column_idx++;
		}
		m_table_data.push_back(row_data);
		m_sort_ascending.push_back(-1);  // -1 for not sorted by this column. 0 for ascending, 1 for descending.
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
	// wxMessageBox("Table column: " + m_operators[column]);

	// Sort the table:
	std::sort(m_table_data.begin(), m_table_data.end(), [&column](std::vector<std::string>& row1, std::vector<std::string>& row2) {
		return row1[column] < row2[column];
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