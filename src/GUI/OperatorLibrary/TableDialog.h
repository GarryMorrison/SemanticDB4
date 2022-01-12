//
// Semantic DB 4
// Created 2022/1/12
// Updated 2022/1/12
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../../SDB.h"

class TableDialog : public wxDialog {

public:
	TableDialog(wxWindow* parent, std::vector<std::string>& operators, const std::string& input_sp_str, long style = 0);

	~TableDialog();
private:
};
