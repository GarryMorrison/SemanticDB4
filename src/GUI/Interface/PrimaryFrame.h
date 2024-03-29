//
// Semantic DB 4
// Created 2021/12/28
// Updated 2022/1/30
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../SDB_GUI.h"

class CommandPanel;
class EditPanel;
class LexerTextCtrl;

class PrimaryFrame : public wxFrame
{
    friend class AppAbout;
    friend class SelectFromListDialog;
    friend class KetMap;
    friend class KetMapDialog;
    friend class CommandPanel;
    friend class EditPanel;

public:
    PrimaryFrame();  // Do we need a destructor too?
    
    void InsertText(const wxString& wxs);
    void InsertStatement(const wxString& wxs);
    void InsertLearnRule(const wxString& wxs);
    void InsertInfixOperator(const wxString& wxs);
    void InsertSimpleOperator(const wxString& wxs);
    void InsertCompoundOperator(const wxString& wxs);
    void InsertFunctionOperator(const wxString& wxs);
    void InsertKet(const wxString& wxs);
    void InsertComment();

    ~PrimaryFrame();

private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void ShowSimpleAboutDialog(wxCommandEvent& event);
    void ShowPrettyAboutDialog(wxCommandEvent& event);
    void OnNew(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnStyleLoad(wxCommandEvent& event);
    void SelectKnownKet(wxCommandEvent& event);
    void OnSelectKetDialogItem(wxCommandEvent& event);
    void SelectKnownOperator(wxCommandEvent& event);
    void OnSelectLiteralOpDialogItem(wxCommandEvent& event);
    void SelectFromLearnRules(wxCommandEvent& event);
    void SelectFromInfix1(wxCommandEvent& event);
    void SelectFromInfix2(wxCommandEvent& event);
    void SelectFromSimple(wxCommandEvent& event);
    void SelectFromCompound(wxCommandEvent& event);
    void SelectFromFunction(wxCommandEvent& event);
    void InsertObject(wxCommandEvent& event);
    void UsageForOperator(wxCommandEvent& event);
    void ShowKetMap(wxCommandEvent& event);
    void SwitchWindow(wxCommandEvent& event);

    void InvokeActiveTable(wxCommandEvent& event);
    void OnIfThenInsert(wxCommandEvent& event);

    void SearchForOperator(wxCommandEvent& event);

    void GenerateDocs(wxCommandEvent& event);

    void OpenExampleWebpage(wxCommandEvent& event);

    void OpenWebsite(wxCommandEvent& event);
    void OpenWebUsage(wxCommandEvent& event);

    // set<ulong> version:
    int PopulateMenu(wxMenu* menu, int starting_id, std::set<ulong>& our_map, std::map<int, wxString>& menu_map, wxString status_text);
    int PopulateSubMenu(wxMenu* parent_menu, int starting_id, std::set<ulong>& our_map, std::map<int, wxString>& menu_map, std::map<wxString, wxMenu*>& label_menu_map, wxString menu_label, wxString sub_menu_label, wxString sub_sub_menu_status_text);

    // vector<string> version:
    int PopulateMenu(wxMenu* menu, int starting_id, std::vector<std::string>& our_list, std::map<int, wxString>& menu_map, wxString status_text);
    int PopulateSubMenu(wxMenu* parent_menu, int starting_id, std::vector<std::string>& our_list, std::map<int, wxString>& menu_map, std::map<wxString, wxMenu*>& label_menu_map, wxString menu_label, wxString sub_menu_label, wxString sub_sub_menu_status_text);


    wxBoxSizer* m_topSizer;
    wxBoxSizer* m_panelSizer;
    wxTextCtrl* m_textCtrl;
    wxAuiNotebook* m_auiNotebook;
    bool m_command_window_active = true;
    bool m_edit_window_active = false;
    // std::map<wxString, wxTextCtrl*> m_open_file_text_ctrl;
    std::map<wxString, LexerTextCtrl*> m_open_file_text_ctrl;
    wxMenu* m_menuWindow;

    CommandPanel* m_frame_commandPanel;
    EditPanel* m_frame_edit_panel;

    // int m_starting_highest_menu_id = ID_Help_Website + 1;
    // int m_current_highest_menu_id = m_starting_highest_menu_id;
    int m_starting_highest_insert_menu_id;
    int m_current_highest_insert_menu_id;
    std::map<int, wxString> m_insert_menu_map;
    std::map<wxString, wxMenu*> m_insert_label_menu_map;

    int m_starting_highest_usage_menu_id;
    int m_current_highest_usage_menu_id;
    std::map<int, wxString> m_usage_menu_map;
    std::map<wxString, wxMenu*> m_usage_label_menu_map;

    unsigned int m_insert_window_open_count = 0;

};


