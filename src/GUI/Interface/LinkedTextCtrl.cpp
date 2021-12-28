//
// Semantic DB 4
// Created 2021/12/28
// Updated 2021/12/28
// Author Garry Morrison
// License GPL v3
//

#include "LinkedTextCtrl.h"

LinkedTextCtrl::LinkedTextCtrl(wxWindow* parent, wxWindowID id, std::set<std::string> clickable_words, std::set<char> split_chars, wxRichTextAttr defaultAttr, const wxString& value,
    const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name)
    : wxRichTextCtrl(parent, id, wxEmptyString, pos, size, style, validator, name)
{
    std::string text_to_process = value.ToStdString();

    /*
    wxRichTextAttr defaultAttr = wxRichTextAttr();
    // defaultAttr.SetFontFamily(wxFONTFAMILY_TELETYPE);
    // defaultAttr.SetFontStyle(wxFONTSTYLE_NORMAL);
    // defaultAttr.SetFontWeight(wxFONTWEIGHT_NORMAL);
    // defaultAttr.SetTextColour(*wxRED);
    defaultAttr.SetFont(defaultAttr.GetFont());
    SetDefaultStyle(defaultAttr);
    */
    // m_defaultAttr = wxRichTextAttr();
    SetDefaultStyle(defaultAttr);

    wxRichTextAttr urlAttr;
    urlAttr.SetURL("LINK-CLICKED");
    // urlAttr.SetFontWeight(wxFONTWEIGHT_BOLD);
    // urlAttr.SetFontUnderlined(true);
    urlAttr.SetTextColour(*wxBLUE);

    std::string token;
    for (const char c : text_to_process)
    {
        if (split_chars.find(c) != split_chars.end())
        {
            if (token.empty())
            {
                WriteText(c);
            }
            else if (clickable_words.find(token) != clickable_words.end()) {
                BeginStyle(urlAttr);
                WriteText(token);
                EndStyle();
                token.clear();
                WriteText(c);
            }
            else
            {
                WriteText(token);
                token.clear();
                WriteText(c);
            }
        }
        else
        {
            token += c;
        }
    }
    if (clickable_words.find(token) != clickable_words.end()) {
        BeginStyle(urlAttr);
        WriteText(token);
        EndStyle();
    }
    else
    {
        WriteText(token);
    }

}

LinkedTextCtrl::~LinkedTextCtrl()
{}


