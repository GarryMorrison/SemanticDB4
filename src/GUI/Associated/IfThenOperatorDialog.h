//
// Semantic DB 4
// Created 2022/1/23
// Updated 2022/1/23
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../../SDB.h"

class IfThenOperatorDialog : public wxDialog {
public:
	IfThenOperatorDialog(wxWindow* parent);

	void OnInsertButton(wxCommandEvent& event);
	wxString GenerateOperator();

	~IfThenOperatorDialog();

private:
	wxTextCtrl* m_encoder_ctrl;
	wxTextCtrl* m_pattern_operator_ctrl;
	wxTextCtrl* m_then_operator_ctrl;
	wxTextCtrl* m_machine_operator_ctrl;

	wxSpinCtrlDouble* m_drop_threshold_ctrl;
};

