//
// Semantic DB 4
// Created 2021/12/28
// Updated 2022/1/22
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../../SDB.h"


class ResultCanvas;  // Do we still need this?

class CommandPanel : public wxPanel
{
public:
    CommandPanel(wxPanel* parent, wxWindowID id);

    void InsertCommandText(const wxString& wxs);
    void InsertStatement(const wxString& wxs);
    void InsertLearnRule(const wxString& wxs);
    void InsertInfixOperator(const wxString& wxs);
    void InsertSimpleOperator(const wxString& wxs);
    void InsertCompoundOperator(const wxString& wxs);
    void InsertFunctionOperator(const wxString& wxs);
    void InsertKet(const wxString& wxs);
    void InsertComment();
    void MoveCaret(int steps);

    void OnKeyDown(wxKeyEvent& event);  // Rename to OnKeyDownPress?
    void OnRunButtonDown(wxCommandEvent& event);
    void OnRunAllButtonDown(wxCommandEvent& event);
    void OnClearButtonDown(wxCommandEvent& event);
    void OnDumpButtonDown(wxCommandEvent& event);
    void OnSaveAsButtonDown(wxCommandEvent& event);
    void OnGraphButtonDown(wxCommandEvent& event);
    void OnResetContextButtonDown(wxCommandEvent& event);
    void OnResetAllButtonDown(wxCommandEvent& event);
    void OnUseMonospaceCheckBox(wxCommandEvent& event);
    void OnUseLineNumbersCheckBox(wxCommandEvent& event);

    void OnInsertNewLineButtonDown(wxCommandEvent& event);
    void OnInsertLineButtonDown(wxCommandEvent& event);
    void OnClearResultsButtonDown(wxCommandEvent& event);
    void SetCurrentLine(int line);

    void OnLeftMouseDown(wxStyledTextEvent& event);
    void OnRightMouseDown(wxMouseEvent& event);

    void SetRunTime(long long time);

    void OnContextSelect(wxCommandEvent& event);
    void UpdateContextSelector();

    void SaveFile(const wxString& filename);

    ~CommandPanel();

private:
    wxPanel* m_parent; // Private or public?
    // wxTextCtrl* m_command_text;
    wxStyledTextCtrl* m_command_text;
    wxTextAttr* m_mono_attr;
    wxTextAttr* m_default_attr;
    wxRichTextCtrl* m_command_results;
    ResultCanvas* m_command_result_canvas;
    wxChoice* m_context_selector;
    wxCheckBox* m_command_monospace_checkbox;
    wxCheckBox* m_command_line_numbers_checkbox;
    int m_current_line = 1;  // Maybe it starts from 1??
    int m_current_position = -1;
    bool m_inside_ket = false;
    std::map<int, bool> m_line_has_learn_rule;
    long long m_run_time = 0;
    wxStaticText* m_timer_line;
    bool m_auto_insert_new_line = false;
    bool m_use_active_text = true;
    bool m_use_command_monospace = false;
    bool m_use_command_line_numbers = true;
};



