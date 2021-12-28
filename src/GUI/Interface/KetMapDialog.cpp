//
// Semantic DB 4
// Created 2021/12/28
// Updated 2021/12/28
// Author Garry Morrison
// License GPL v3
//

#include "KetMapDialog.h"

KetMapDialog::KetMapDialog(wxWindow* parent, long style)
    : wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
    SetTitle("Ket Map");

    wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);
    SortedListCtrl* ket_list_box = new SortedListCtrl(this, wxLC_HRULES);  // Rename MyListCtrl as SortedListCtrl?

    ket_list_box->InsertColumn(0, "Index", wxLIST_FORMAT_LEFT);  // Specify column widths too?
    ket_list_box->InsertColumn(1, "String", wxLIST_FORMAT_LEFT, 150);

    long index;
    long row_count = 0;
    for (auto str : ket_map.get_map())
    {
        index = ket_list_box->InsertItem(0, std::to_string(row_count));
        ket_list_box->SetItem(index, 1, str);
        ket_list_box->SetItemData(index, row_count);
        row_count++;

        if (row_count >= KET_MAP_DISPLAY_MAX_ROWS)  // Maybe do something more interesting here later. Like invoke a select range dialog.
        {
            break;
        }
    }

    // Sort ket_list_box:
    ket_list_box->SortInfo.SortAscending = true;
    ket_list_box->SortInfo.Column = 0;
    ket_list_box->SortInfo.ListCtrl = ket_list_box;
    ket_list_box->SortItems(SortedListCompareFunction, (wxIntPtr)&ket_list_box->SortInfo);


    topsizer->Add(
        ket_list_box,
        //     // wxSizerFlags(1).Expand().Border(wxALL, 10));
        wxSizerFlags(1).Expand().Border(wxALL, 10));

    if (row_count >= KET_MAP_DISPLAY_MAX_ROWS)
    {
        wxBoxSizer* text_sizer1 = new wxBoxSizer(wxHORIZONTAL);
        text_sizer1->Add(new wxStaticText(this, wxID_ANY, "Max row length exceeded"), wxSizerFlags(0));
        topsizer->Add(text_sizer1, wxSizerFlags(0).Center());

        wxBoxSizer* text_sizer2 = new wxBoxSizer(wxHORIZONTAL);
        text_sizer2->Add(new wxStaticText(this, wxID_ANY, "Total rows: " + std::to_string(row_count)), wxSizerFlags(0));
        topsizer->Add(text_sizer2, wxSizerFlags(0).Center());
    }

    wxBoxSizer* button_sizer = new wxBoxSizer(wxHORIZONTAL);
    //create two buttons that are horizontally unstretchable,
    // with an all-around border with a width of 10 and implicit top alignment
    button_sizer->Add(
        new wxButton(this, wxID_OK, "OK"),
        wxSizerFlags(0).Border(wxALL, 10));
    //create a sizer with no border and centered horizontally

    topsizer->Add(
        button_sizer,
        wxSizerFlags(0).Center());

    SetSizerAndFit(topsizer);
    CenterOnScreen();
    ShowModal();
}


KetMapDialog::~KetMapDialog()
{}
