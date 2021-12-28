//
// Semantic DB 4
// Created 2021/12/28
// Updated 2021/12/28
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "SDB.h"

int wxCALLBACK SortedListCompareFunction(wxIntPtr, wxIntPtr, wxIntPtr);

class SortedListCtrl;

typedef struct
{
    SortedListCtrl* ListCtrl;
    int Column;
    bool SortAscending;
} SortInfoStruct;

class SortedListCtrl : public wxListCtrl {

public:
    SortedListCtrl(wxWindow* parent, long style = 0);

    // Code from here: https://forums.wxwidgets.org/viewtopic.php?t=2174
    wxString GetTextByColumn(long index, int column);
    SortInfoStruct SortInfo;

    ~SortedListCtrl();

private:
    void OnColumnClick(wxListEvent& event);

    bool m_clicked = false;
    bool m_sort_ascending = true;
    int m_sort_column = 0;
};

