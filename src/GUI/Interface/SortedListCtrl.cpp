//
// Semantic DB 4
// Created 2021/12/28
// Updated 2021/12/28
// Author Garry Morrison
// License GPL v3
//

#include "SortedListCtrl.h"


SortedListCtrl::SortedListCtrl(wxWindow* parent, long style) : wxListCtrl(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 400), style | wxLC_REPORT)
{
    Bind(wxEVT_LIST_COL_CLICK, &SortedListCtrl::OnColumnClick, this);
}

wxString SortedListCtrl::GetTextByColumn(long index, int column)
{
    wxListItem Item;
    Item.SetId(index);
    Item.SetColumn(column);
    Item.SetMask(wxLIST_MASK_TEXT);
    GetItem(Item);
    return Item.GetText();
}

void SortedListCtrl::OnColumnClick(wxListEvent& event)
{
    if (event.GetColumn() == SortInfo.Column)
    {
        SortInfo.SortAscending = SortInfo.SortAscending ? false : true;
    }
    else
    {
        SortInfo.SortAscending = true;
    }
    SortInfo.Column = event.GetColumn();
    SortInfo.ListCtrl = this;
    SortItems(SortedListCompareFunction, (wxIntPtr)&SortInfo);

}

SortedListCtrl::~SortedListCtrl()
{}

int wxCALLBACK SortedListCompareFunction(wxIntPtr item1, wxIntPtr item2, wxIntPtr sortinfo)
{
    SortInfoStruct* SortInfo = (SortInfoStruct*)sortinfo;
    int Column = SortInfo->Column;
    SortedListCtrl* ListCtrl = SortInfo->ListCtrl;
    bool SortAscending = SortInfo->SortAscending;
    long index1 = ListCtrl->FindItem(-1, item1);
    long index2 = ListCtrl->FindItem(-1, item2);
    wxString string1 = ListCtrl->GetTextByColumn(index1, Column);
    wxString string2 = ListCtrl->GetTextByColumn(index2, Column);
    if (Column == 0)   // Later, maybe make it an option which columns are integer sorted, and which are string sorted?
    {
        long val1 = std::stol(string1.ToStdString());
        long val2 = std::stol(string2.ToStdString());
        if (val1 < val2)
            return SortAscending ? -1 : 1;
        if (val1 > val2)
            return SortAscending ? 1 : -1;
        return 0;
    }

    if (string1.Cmp(string2) < 0)
    {
        return SortAscending ? -1 : 1;
    }
    else if (string1.Cmp(string2) > 0)
    {
        return SortAscending ? 1 : -1;
    }
    else
    {
        return 0;
    }
}
