//
// Semantic DB 4
// Created 2022/1/8
// Updated 2022/1/8
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
	void AddPage(wxWindow* page, const wxString& caption, bool select = false);
	~EditPanel();
private:
	wxAuiNotebook* m_aui_notebook;
};
