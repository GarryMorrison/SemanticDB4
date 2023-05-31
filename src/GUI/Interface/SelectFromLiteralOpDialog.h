//
// Semantic DB 4
// Created 2022/1/7
// Updated 2022/1/7
// Author Garry Morrison
// License GPL v3
//

#pragma once

#include "../SDB_GUI.h"


class SelectFromLiteralOpDialog : public wxDialog
{
public:
	SelectFromLiteralOpDialog(wxWindow* parent, const wxPoint position_delta = wxPoint(0, 0));

	void OnLiteralOpListClick(wxCommandEvent& event);
	void OnUpdateButton(wxCommandEvent& event);
	~SelectFromLiteralOpDialog();

private:
	wxListBox* m_data_list;
};


