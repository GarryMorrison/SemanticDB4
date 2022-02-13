//
// Semantic DB 4
// Created 2022/1/8
// Updated 2022/2/11
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
	void OnPageChange(wxCommandEvent& event);
	void OnPageEdit(wxCommandEvent& event);
	void OnPageClose(wxCommandEvent& event);
	void AddPage(wxWindow* page, const wxString& caption, bool select = false);
	void ModifyPage(wxWindow* page, const wxString& caption, bool select = false);
	wxString GetTabLabel();
	bool TabLabelExists(const wxString& tab_label);
	void SaveFile(const wxString& filename);
	void DeleteAllPages();

	void WriteText(const wxString& text);

	void InsertText(const wxString& wxs);
	void InsertStatement(const wxString& wxs);
	void InsertLearnRule(const wxString& wxs);
	void InsertInfixOperator(const wxString& wxs);
	void InsertSimpleOperator(const wxString& wxs);
	void InsertCompoundOperator(const wxString& wxs);
	void InsertFunctionOperator(const wxString& wxs);
	void InsertKet(const wxString& wxs);
	void InsertComment();

	void ParseExperiment(const std::string& commands);

	~EditPanel();
private:
	wxAuiNotebook* m_aui_notebook;
	wxTextCtrl* m_text_ctrl;
	wxString m_current_tab;
	std::map<wxString, bool> m_unsaved_tabs;
};
