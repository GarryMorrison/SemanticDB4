//
// Semantic DB 4
// Created 2022/1/6
// Updated 2022/1/6
// Author Garry Morrison
// License GPL v3
//

#include "GeneralOperatorsFrame.h"

GeneralOperatorsFrame::GeneralOperatorsFrame(wxWindow* parent, const wxString& title, const wxString& content, wxPoint position_delta, long style)
    : wxFrame(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style | wxDEFAULT_FRAME_STYLE | wxRESIZE_BORDER)
{
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    SetTitle(title);
    wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);
    
    wxArrayString grid_data;  // Later enter real data, ie: supported-ops |*>
    grid_data.Add("one");
    grid_data.Add("two");
    grid_data.Add("three");
    grid_data.Add("four");
    grid_data.Add("five");
    grid_data.Add("six");
    grid_data.Add("seven");
    grid_data.Add("eight");
    grid_data.Add("nine");
    grid_data.Add("ten");
    
    unsigned int grid_data_size = grid_data.size();
    unsigned int dim = (unsigned int)(std::ceil(sqrt(double(grid_data_size))));  // Given a size, find the smallest square with dimensions dim * dim.
    // wxMessageBox(wxString::Format("dim = %d", dim));

    wxArrayString tmp_grid_data;
    for (unsigned int i = 0; i < grid_data_size; i++)
    {
        tmp_grid_data.Add(grid_data[i]);
        if (i > 0 && ((i + 1) % dim) == 0)
        {
            m_our_arrays.push_back(tmp_grid_data);
            tmp_grid_data.Clear();
        }
    }
    if (tmp_grid_data.size() > 0)
    {
        m_our_arrays.push_back(tmp_grid_data);
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

