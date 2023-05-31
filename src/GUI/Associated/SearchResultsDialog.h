//
// Semantic DB 4
// Created 2023/4/8
// Updated 2023/4/8
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../SDB_GUI.h"


class SearchResultsDialog : public wxDialog
{
public:
    // Constructor:
    SearchResultsDialog(wxWindow* parent, bool simple, bool compound, bool function, bool name, bool description, bool examples, bool seealso, wxString search_term, long style = 0);

    void OnLaunchUsageButton(wxCommandEvent& event);

    // Destructor:
    ~SearchResultsDialog();
private:
    // Are these still used?
    bool m_simple = true;
    bool m_compound = true;
    bool m_function = true;
    bool m_name = true;
    bool m_description = true;
    bool m_examples = true;
    wxString m_search_term;

    wxArrayString m_operator_list;
    wxCheckListBox* m_matching_operators;
};


