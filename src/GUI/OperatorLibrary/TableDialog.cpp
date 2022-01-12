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
	: wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
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
	wxGrid* grid_table = new wxGrid(this, wxID_ANY);
	grid_table->CreateGrid(input_sp.size(), operators.size());
	unsigned int list_idx = 0;
	for (const auto& op : operators)
	{
		grid_table->SetColLabelValue(list_idx, op);
		list_idx++;
	}
	list_idx = 0;
	for (const auto k : input_sp)
	{
		grid_table->SetCellValue(list_idx, 0, k.label());
		list_idx++;
	}
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
	topsizer->Add(grid_table, wxSizerFlags(1).Expand().Border(wxALL, 10));
	topsizer->AddSpacer(10);

	SetSizerAndFit(topsizer);
	CenterOnScreen();
	// ShowModal();
	Show();
}

TableDialog::~TableDialog()
{}