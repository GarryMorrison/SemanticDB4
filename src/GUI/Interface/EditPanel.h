//
// Semantic DB 4
// Created 2022/1/8
// Updated 2022/1/19
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../../SDB.h"


// class ResultCanvas;

class EditPanel : public wxPanel
{
public:
	EditPanel(wxPanel* parent, wxWindowID id);
	void OnRunButtonDown(wxCommandEvent& event);
	void OnDumpButtonDown(wxCommandEvent& event);
	void OnResetButtonDown(wxCommandEvent& event);
	void AddPage(wxWindow* page, const wxString& caption, bool select = false);
	void SaveFile(const wxString& filename);

	~EditPanel();
private:
	wxAuiNotebook* m_aui_notebook;
	wxTextCtrl* m_text_ctrl;
};
