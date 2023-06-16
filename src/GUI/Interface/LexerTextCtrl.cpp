//
// Semantic DB 4
// Created 2023/6/16
// Updated 2023/6/16
// Author Garry Morrison
// License GPL v3
//

#include "LexerTextCtrl.h"

LexerTextCtrl::LexerTextCtrl(wxWindow* parent, wxWindowID id, const wxString& text, const wxPoint& pos, const wxSize& size, long style)
	: wxStyledTextCtrl(parent, id, pos, size, style)
{
    // Set up some initial styles
    // StyleSetSpec(wxSTC_STYLE_DEFAULT, "face:Courier New,size:10");
    StyleClearAll();
    // SetLexer(wxSTC_LEX_PYTHON);

    // Load up some text:
    SetText(text);

    // Enable and configure line numbers:
    SetMarginType(1, wxSTC_MARGIN_NUMBER);
    SetMarginWidth(1, 30);
}

void LexerTextCtrl::LoadLexerStyles()
{
    m_style_map[LEX::LEX_NONE] = *wxBLACK;
    m_style_map[LEX::LEX_LITERAL] = *wxBLUE;
    m_style_map[LEX::LEX_SIMPLE] = *wxBLUE;
    m_style_map[LEX::LEX_COMPOUND] = *wxBLUE;
    m_style_map[LEX::LEX_FUNCTION] = *wxBLUE;
    m_style_map[LEX::LEX_KEYWORD] = *wxBLUE;
    m_style_map[LEX::LEX_KET] = *wxBLUE;
    m_style_map[LEX::LEX_COMMENT] = *wxBLUE;
    m_style_map[LEX::LEX_STRING] = *wxBLUE;

}

void LexerTextCtrl::LoadOperatorMaps()
{
    for (ulong idx : fn_map.set_simple_operators)
    {
        m_simple.insert(ket_map.get_str(idx));
    }
    for (ulong idx : fn_map.set_compound_operators)
    {
        m_compound.insert(ket_map.get_str(idx));
    }
    for (ulong idx : fn_map.set_function_operators)
    {
        m_function.insert(ket_map.get_str(idx));
    }
    for (const auto& s : fn_map.list_of_statements)
    {
        m_keyword.insert(s);
    }
}

void LexerTextCtrl::SyntaxHighlight(size_t start, size_t end, const wxString& text)
{

}

void LexerTextCtrl::OnStyleNeeded(wxStyledTextEvent& event)
{
    event.Skip();
}

LexerTextCtrl::~LexerTextCtrl()
{};

