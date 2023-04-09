//
// Semantic DB 4
// Created 2023/4/9
// Updated 2023/4/9
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../../SDB.h"
#include <wx/radiobut.h>
#include <wx/filepicker.h>


class GenerateDocsDialog : public wxDialog
{
public:
    // Constructor:
    GenerateDocsDialog(wxWindow* parent, long style = 0);

    void OnTextRadioButton(wxCommandEvent& event);
    void OnHtmlRadioButton(wxCommandEvent& event);

    void OnGenerateButtonDown(wxCommandEvent& event);

    // Destructor:
    ~GenerateDocsDialog();
private:
    wxCheckBox* m_linkify_checkbox;
    wxRadioButton* m_text_radio;
    wxRadioButton* m_html_radio;
    wxDirPickerCtrl* m_dir_picker;
};


