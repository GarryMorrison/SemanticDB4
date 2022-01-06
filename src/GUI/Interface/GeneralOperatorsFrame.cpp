//
// Semantic DB 4
// Created 2022/1/6
// Updated 2022/1/6
// Author Garry Morrison
// License GPL v3
//

#include "GeneralOperatorsFrame.h"

GeneralOperatorsFrame::GeneralOperatorsFrame(wxWindow* parent, const wxString& title, const wxArrayString& content, wxPoint position_delta, long style)
    : wxFrame(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style | wxDEFAULT_FRAME_STYLE | wxRESIZE_BORDER)
{
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    SetTitle(title);
    wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);
      
    unsigned int content_size = content.size();
    unsigned int dim = (unsigned int)(std::ceil(sqrt(double(content_size))));  // Given a size, find the smallest square with dimensions dim * dim.
    // wxMessageBox(wxString::Format("dim = %d", dim));

    wxArrayString grid_data;
    for (unsigned int i = 0; i < content_size; i++)
    {
        grid_data.Add(content[i]);
        if (((i + 1) % dim) == 0)
        {
            m_our_arrays.push_back(grid_data);
            grid_data.Clear();
        }
    }
    if (grid_data.size() > 0)
    {
        m_our_arrays.push_back(grid_data);
    }

    wxCheckListBox* col;
    unsigned int idx = 0;
    for (const auto& wxas : m_our_arrays)
    {
        col = new wxCheckListBox(panel, idx, wxDefaultPosition, wxDefaultSize, wxas);
        m_our_checkboxes.push_back(col);
        idx++;
    }

    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
    for (const auto& col : m_our_checkboxes)
    {
        hbox1->AddSpacer(10);
        hbox1->Add(col, wxSizerFlags(0).Left().Border(wxTOP | wxBOTTOM, 20));
    }

    topsizer->Add(hbox1);

    for (const auto& col : m_our_checkboxes)
    {
        col->Bind(wxEVT_CHECKLISTBOX, &GeneralOperatorsFrame::OnCheckBoxClick, this);
    }

    panel->SetSizerAndFit(topsizer);
    // CenterOnScreen();
    // wxPoint dialog_position = GetScreenPosition();
    // // dialog_position += m_position_delta;
    // dialog_position += position_delta;
    // SetPosition(dialog_position);
    SetPosition(wxPoint(100, 100));
    // Show();  // We want it hidden by default. Only show when FilteredDumpFrame wants it visible.
}

void GeneralOperatorsFrame::OnCheckBoxClick(wxCommandEvent& event)
{
    // wxMessageBox(wxString::Format("Check box clicked int: %d, id: %d", event.GetInt(), event.GetId()));
    wxString clicked_item = m_our_arrays[event.GetId()][event.GetInt()];
    bool item_is_checked = m_our_checkboxes[event.GetId()]->IsChecked(event.GetInt());
    if (item_is_checked)
    {
        wxMessageBox("Checked item: " + clicked_item);
    }
    else
    {
        wxMessageBox("Unchecked item: " + clicked_item);
    }
}

GeneralOperatorsFrame::~GeneralOperatorsFrame()
{}

