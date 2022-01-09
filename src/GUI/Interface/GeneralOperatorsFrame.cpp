//
// Semantic DB 4
// Created 2022/1/6
// Updated 2022/1/8
// Author Garry Morrison
// License GPL v3
//

#include "GeneralOperatorsFrame.h"
extern SDB::Driver driver;

wxDEFINE_EVENT(EVT_GRID_CLICK, wxCommandEvent);

GeneralOperatorsFrame::GeneralOperatorsFrame(wxWindow* parent, const wxString& title, const wxArrayString& content, wxPoint position_delta, long style)
    : wxFrame(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style | wxDEFAULT_FRAME_STYLE | wxRESIZE_BORDER)
{
    m_parent = parent;
    m_panel = new wxPanel(this, wxID_ANY);

    SetTitle(title);
    wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);
      
    unsigned int content_size = content.size();
    m_dim = (unsigned int)(std::ceil(sqrt(double(content_size))));  // Given a size, find the smallest square with dimensions dim * dim.
    // wxMessageBox(wxString::Format("dim = %d", m_dim));

    wxString message;
    if (content_size == 0)
    {
        message = wxString::Format("There are no general operators in the current context \"%s\".", driver.context.get_context_name());
    }
    else
    {
        message = wxString::Format("General operators in context \"%s\"", driver.context.get_context_name());
    }
    wxStaticText* static_message = new wxStaticText(m_panel, wxID_ANY, message);
    m_topsizer->Add(static_message, wxSizerFlags(0).Center().Border(wxALL, 10));

    wxArrayString grid_data;
    for (unsigned int i = 0; i < content_size; i++)
    {
        grid_data.Add(content[i]);
        if (((i + 1) % m_dim) == 0)
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
        col = new wxCheckListBox(m_panel, idx, wxDefaultPosition, wxDefaultSize, wxas);
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

    m_panel->SetSizerAndFit(topsizer);
    Fit();
    // CenterOnScreen();
    // wxPoint dialog_position = GetScreenPosition();
    // // dialog_position += m_position_delta;
    // dialog_position += position_delta;
    // SetPosition(dialog_position);
    SetPosition(wxPoint(100, 100));
    // Show();  // We want it hidden by default. Only show when FilteredDumpFrame wants it visible.
}

GeneralOperatorsFrame::GeneralOperatorsFrame(wxWindow* parent, const wxPoint position_delta)
    : wxFrame(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE | wxRESIZE_BORDER)
{
    m_parent = parent;
    m_panel = new wxPanel(this, wxID_ANY);

    SetTitle("General Operators");
    m_topsizer = new wxBoxSizer(wxVERTICAL);

    // Add context selector:
    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxArrayString context_list;
    for (const auto& name : driver.context.get_context_names())
    {
        context_list.Add(name);
    }
    m_context_selector = new wxChoice(m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, context_list);
    m_context_selector->SetSelection(driver.context.get_context_index());
    hbox1->Add(new wxStaticText(m_panel, wxID_ANY, "Context", wxDefaultPosition, wxDefaultSize), wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
    hbox1->Add(m_context_selector, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
    m_topsizer->AddSpacer(10);
    m_topsizer->Add(hbox1);

    ulong star_idx = ket_map.get_idx("*");  
    for (ulong op_idx : driver.context.supported_ops(star_idx))
    {
        m_general_ops.Add(ket_map.get_str(op_idx));
    }
    unsigned int content_size = m_general_ops.size();
    m_dim = (unsigned int)(std::ceil(sqrt(double(content_size))));  // Given a size, find the smallest square with dimensions dim * dim.
    // wxMessageBox(wxString::Format("dim = %d", m_dim));

    /*/
    wxString message;
    if (content_size == 0)
    {
        message = wxString::Format("There are no general operators in the current context \"%s\".", driver.context.get_context_name());
    }
    else
    {
        message = wxString::Format("General operators in context \"%s\"", driver.context.get_context_name());
    }
    wxStaticText* static_message = new wxStaticText(m_panel, wxID_ANY, message);
    m_topsizer->Add(static_message, wxSizerFlags(0).Center().Border(wxALL, 10));
    */

    if (content_size == 0)
    {
        wxString message = "There are no general operators in this context.";
        wxStaticText* static_message = new wxStaticText(m_panel, wxID_ANY, message);
        m_topsizer->Add(static_message, wxSizerFlags(0).Center().Border(wxALL, 10));
    }

    wxArrayString grid_data;
    for (unsigned int i = 0; i < content_size; i++)
    {
        grid_data.Add(m_general_ops[i]);
        if (((i + 1) % m_dim) == 0)
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
        col = new wxCheckListBox(m_panel, idx, wxDefaultPosition, wxDefaultSize, wxas);
        m_our_checkboxes.push_back(col);
        idx++;
    }

    wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
    for (const auto& col : m_our_checkboxes)
    {
        hbox2->AddSpacer(10);
        hbox2->Add(col, wxSizerFlags(0).Center().Border(wxTOP | wxBOTTOM, 10));
    }
    hbox2->AddSpacer(10);
    m_topsizer->Add(hbox2, wxSizerFlags(0).Center().Border(wxTOP | wxBOTTOM, 0));

    /*
    m_update_button = new wxButton(m_panel, wxID_ANY, "Update");
    m_topsizer->Add(m_update_button, wxSizerFlags(0).Center().Border(wxALL, 10));
    m_update_button->Bind(wxEVT_BUTTON, &GeneralOperatorsFrame::OnUpdateButton, this);
    */

    m_context_selector->Bind(wxEVT_CHOICE, &GeneralOperatorsFrame::OnContextSelect, this);
    for (const auto& col : m_our_checkboxes)
    {
        col->Bind(wxEVT_CHECKLISTBOX, &GeneralOperatorsFrame::OnCheckBoxClick, this);
    }

    m_panel->SetSizerAndFit(m_topsizer);
    Fit();
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
    unsigned int idx = event.GetId() * m_dim + event.GetInt();
    wxCommandEvent our_event(EVT_GRID_CLICK);
    our_event.SetString(clicked_item);  // Send through the label with SetString().
    our_event.SetInt(idx);              // Send through the list idx with SetInt().
    wxPostEvent(this, our_event);
}

bool GeneralOperatorsFrame::IsChecked(unsigned int list_idx)
{
    unsigned int column = list_idx / m_dim;
    unsigned int row = list_idx % m_dim;
    return m_our_checkboxes[column]->IsChecked(row);
}

void GeneralOperatorsFrame::OnUpdateButton(wxCommandEvent& event)
{
    // wxMessageBox("Update button pressed");
    // Reset everything:
    for (const auto& col : m_our_checkboxes)
    {
        col->Unbind(wxEVT_CHECKLISTBOX, &GeneralOperatorsFrame::OnCheckBoxClick, this);
    }
    m_update_button->Unbind(wxEVT_BUTTON, &GeneralOperatorsFrame::OnUpdateButton, this);  // Needs a wrapper to check m_update_button is not null.
    m_topsizer->Clear(true);
    m_general_ops.Clear();
    m_our_arrays.clear();
    m_our_checkboxes.clear();
    

    // Rebuild the panel:
    ulong star_idx = ket_map.get_idx("*");   
    for (ulong op_idx : driver.context.supported_ops(star_idx))
    {
        m_general_ops.Add(ket_map.get_str(op_idx));
    }
    unsigned int content_size = m_general_ops.size();
    m_dim = (unsigned int)(std::ceil(sqrt(double(content_size))));  // Given a size, find the smallest square with dimensions dim * dim.

    wxString message;
    if (content_size == 0)
    {
        message = wxString::Format("There are no general operators in the current context \"%s\".", driver.context.get_context_name());
    }
    else
    {
        message = wxString::Format("General operators in context \"%s\"", driver.context.get_context_name());
    }
    wxStaticText* static_message = new wxStaticText(m_panel, wxID_ANY, message);
    m_topsizer->Add(static_message, wxSizerFlags(0).Center().Border(wxALL, 10));

    wxArrayString grid_data;
    for (unsigned int i = 0; i < content_size; i++)
    {
        grid_data.Add(m_general_ops[i]);
        if (((i + 1) % m_dim) == 0)
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
        col = new wxCheckListBox(m_panel, idx, wxDefaultPosition, wxDefaultSize, wxas);
        m_our_checkboxes.push_back(col);
        idx++;
    }
    
    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
    for (const auto& col : m_our_checkboxes)
    {
        hbox1->AddSpacer(10);
        hbox1->Add(col, wxSizerFlags(0).Center().Border(wxTOP | wxBOTTOM, 10));
    }
    hbox1->AddSpacer(10);
    m_topsizer->Add(hbox1, wxSizerFlags(0).Center().Border(wxTOP | wxBOTTOM, 0));
    
    m_update_button = new wxButton(m_panel, wxID_ANY, "Update");
    m_topsizer->Add(m_update_button, wxSizerFlags(0).Center().Border(wxALL, 10));

    m_update_button->Bind(wxEVT_BUTTON, &GeneralOperatorsFrame::OnUpdateButton, this);
    for (const auto& col : m_our_checkboxes)
    {
        col->Bind(wxEVT_CHECKLISTBOX, &GeneralOperatorsFrame::OnCheckBoxClick, this);
    }

    m_panel->SetSizerAndFit(m_topsizer);
    Fit();
}

void GeneralOperatorsFrame::OnContextSelect(wxCommandEvent& event)
{
    // wxMessageBox("context changed");
    unsigned int new_selection = m_context_selector->GetSelection();
    driver.context.set(new_selection);
    UpdateFrame();
}

void GeneralOperatorsFrame::UpdateFrame()
{
    // Reset everything:
    for (const auto& col : m_our_checkboxes)
    {
        col->Unbind(wxEVT_CHECKLISTBOX, &GeneralOperatorsFrame::OnCheckBoxClick, this);
    }
    // m_update_button->Unbind(wxEVT_BUTTON, &GeneralOperatorsFrame::OnUpdateButton, this);
    m_topsizer->Clear(true);
    m_general_ops.Clear();
    m_our_arrays.clear();
    m_our_checkboxes.clear();

    // Rebuild our frame:
    // Add context selector:
    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxArrayString context_list;
    for (const auto& name : driver.context.get_context_names())
    {
        context_list.Add(name);
    }
    m_context_selector = new wxChoice(m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, context_list);
    m_context_selector->SetSelection(driver.context.get_context_index());
    hbox1->Add(new wxStaticText(m_panel, wxID_ANY, "Context", wxDefaultPosition, wxDefaultSize), wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
    hbox1->Add(m_context_selector, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
    m_topsizer->AddSpacer(10);
    m_topsizer->Add(hbox1);

    ulong star_idx = ket_map.get_idx("*");
    for (ulong op_idx : driver.context.supported_ops(star_idx))
    {
        m_general_ops.Add(ket_map.get_str(op_idx));
    }
    unsigned int content_size = m_general_ops.size();
    m_dim = (unsigned int)(std::ceil(sqrt(double(content_size))));  // Given a size, find the smallest square with dimensions dim * dim.
    // wxMessageBox(wxString::Format("dim = %d", m_dim));

    if (content_size == 0)
    {
        wxString message = "There are no general operators in this context.";
        wxStaticText* static_message = new wxStaticText(m_panel, wxID_ANY, message);
        m_topsizer->Add(static_message, wxSizerFlags(0).Center().Border(wxALL, 10));
    }

    wxArrayString grid_data;
    for (unsigned int i = 0; i < content_size; i++)
    {
        grid_data.Add(m_general_ops[i]);
        if (((i + 1) % m_dim) == 0)
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
        col = new wxCheckListBox(m_panel, idx, wxDefaultPosition, wxDefaultSize, wxas);
        m_our_checkboxes.push_back(col);
        idx++;
    }

    wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
    for (const auto& col : m_our_checkboxes)
    {
        hbox2->AddSpacer(10);
        hbox2->Add(col, wxSizerFlags(0).Center().Border(wxTOP | wxBOTTOM, 10));
    }
    hbox2->AddSpacer(10);
    m_topsizer->Add(hbox2, wxSizerFlags(0).Center().Border(wxTOP | wxBOTTOM, 0));

    m_context_selector->Bind(wxEVT_CHOICE, &GeneralOperatorsFrame::OnContextSelect, this);
    for (const auto& col : m_our_checkboxes)
    {
        col->Bind(wxEVT_CHECKLISTBOX, &GeneralOperatorsFrame::OnCheckBoxClick, this);
    }

    m_panel->SetSizerAndFit(m_topsizer);
    Fit();
}

GeneralOperatorsFrame::~GeneralOperatorsFrame()
{}
