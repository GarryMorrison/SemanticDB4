//
// Semantic DB 4
// Created 2022/1/7
// Updated 2022/1/7
// Author Garry Morrison
// License GPL v3
//

#pragma once

#include "../../SDB.h"


class SelectFromKetDialog : public wxDialog
{
public:
	SelectFromKetDialog(wxWindow* parent, const wxPoint position_delta = wxPoint(0, 0));

	void OnKetListClick(wxCommandEvent& event);
	void OnUpdateButton(wxCommandEvent& event);
	~SelectFromKetDialog();

private:
	wxListBox* m_data_list;
};

