//
// Semantic DB 4
// Created 2021/12/28
// Updated 2021/12/28
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../../SDB.h"

class LinkedTextCtrl : public wxRichTextCtrl
{
public:
    LinkedTextCtrl(wxWindow* parent, wxWindowID id, std::set<std::string> clickable_words, std::set<char> split_chars, wxRichTextAttr defaultAttr, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxTextCtrlNameStr);
    // Maybe later a constructor which specifies the linked text wxRichTextAttr too?


    ~LinkedTextCtrl();
private:
    // wxRichTextCtrl* m_rtc;
    // wxRichTextAttr m_defaultAttr;
};


