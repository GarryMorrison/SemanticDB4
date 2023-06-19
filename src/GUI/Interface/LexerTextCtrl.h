//
// Semantic DB 4
// Created 2023/6/16
// Updated 2023/6/19
// Author Garry Morrison
// License GPL v3
//

// Written with the help of this page:
// https://wiki.wxwidgets.org/Adding_a_custom_lexer_with_syntax_highlighting_and_folding_to_a_WxStyledTextCtrl
// And ChatGPT


#pragma once

#include "../SDB_GUI.h"
#include "../LexerColorMap/LexerColorMap.h"

enum class LEX;
struct LEX_OBJECT;
class LexerColorMap;
extern LexerColorMap lexer_color_map;

/* // Moved to LexerColorMap:
struct LEX_OBJECT {
	LEX LEX_ID = LEX::LEX_NONE;
	size_t start = 0;
	size_t end = 0;
};
*/


class LexerTextCtrl : public wxStyledTextCtrl
{
public:
	LexerTextCtrl(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString &text = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0);
	void LoadLexerStyles();
	void LoadOperatorMaps();

	void SetUseHighlight(bool use_highlight) { m_use_highlighting = use_highlight; }  // Maybe something more here later.
	void SyntaxHighlight(size_t start, size_t end, const std::string& text);
	void RefreshSyntaxHighlight();
	void OnStyleNeeded(wxStyledTextEvent& event);
	void OnMouseClick(wxMouseEvent& event);

	~LexerTextCtrl();

private:
	bool m_use_highlighting = true;  // Apply highlighting by default, potentially add a checkbox to the EditFrame to enable/disable.

	std::set<std::string> m_ket_special;
	std::set<std::string> m_simple;
	std::set<std::string> m_compound;
	std::set<std::string> m_function;
	std::set<std::string> m_keyword;

};

