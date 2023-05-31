//
// Semantic DB 4
// Created 2022/1/22
// Updated 2022/1/22
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../../SDB.h"

class IfThenMachineDialog : public wxDialog {
public:
	IfThenMachineDialog(wxWindow* parent);

	void OnInsertButton(wxCommandEvent& event);
	wxString GenerateMachine();

	~IfThenMachineDialog();

private:
	wxTextCtrl* m_node_label_ctrl;
	wxTextCtrl* m_pattern_operator_ctrl;
	wxTextCtrl* m_then_operator_ctrl;

	wxSpinCtrl* m_starting_index_ctrl;
	wxSpinCtrl* m_pattern_count_ctrl;
};


