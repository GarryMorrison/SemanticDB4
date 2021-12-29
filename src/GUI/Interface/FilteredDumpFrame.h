//
// Semantic DB 4
// Created 2021/12/29
// Updated 2021/12/29
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "SDB.h"


class ResultCanvas;

class FilteredDumpFrame : public wxFrame
{
public:
    FilteredDumpFrame(wxWindow* parent, const wxString& title, const std::vector<std::string>& op_list, const std::vector<std::string>& ket_list, const wxPoint position_delta = wxPoint(0, 0), long style = 0);

    void CheckLiteralOpList(wxCommandEvent& event);
    void CheckKetList(wxCommandEvent& event);

    ~FilteredDumpFrame();

private:
    void UpdateKnowledge(); // make it public?

    wxWindow* m_parent;
    ResultCanvas* m_result_canvas;
    wxPoint m_position_delta = wxPoint(0, 0);

    wxString m_knowledge;
    bool m_use_active_text = true;

    wxArrayString m_literal_ops;
    wxArrayString m_active_literal_ops;
    std::map<unsigned int, ulong> m_map_literal_ops;  // Work out which of these we no longer need!
    std::map<unsigned int, ulong> m_map_active_literal_ops;
    std::set<unsigned int> m_set_active_literal_ops;
    wxArrayString m_kets;
    wxArrayString m_active_kets;
    std::map<unsigned int, ulong> m_map_active_kets;

    std::map<unsigned int, ulong> m_map_kets;
    std::set<unsigned int> m_set_active_kets;

    wxCheckListBox* m_literal_op_list_box;
    wxCheckListBox* m_ket_list_box;
};
