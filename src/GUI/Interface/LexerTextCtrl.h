//
// Semantic DB 4
// Created 2023/6/16
// Updated 2023/6/16
// Author Garry Morrison
// License GPL v3
//

#pragma once

#include "../SDB_GUI.h"

enum class LEX : int {
	LEX_NONE = 10,
	LEX_LITERAL = 11,
	LEX_SIMPLE = 12,
	LEX_COMPOUND = 13,
	LEX_FUNCTION = 14,
	LEX_KEYWORD = 15,
	LEX_KET = 16,     // I would prefer not to have the LEX_ prefix, but "KET" is already taken! It would take some work to fix that.
	LEX_COMMENT = 17,
	LEX_STRING = 18
};

struct LEX_OBJECT {
	int LEX_ID = 0;
	size_t start = 0;
	size_t end = 0;
};


class LexerTextCtrl : public wxStyledTextCtrl
{
public:
	LexerTextCtrl(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString &text = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0);
	void LoadLexerStyles();
	void LoadOperatorMaps();

	void SyntaxHighlight(size_t start, size_t end, const wxString& text);
	void OnStyleNeeded(wxStyledTextEvent& event);

	~LexerTextCtrl();

private:
	std::map<LEX, wxColor> m_style_map;
	std::set<std::string> m_simple;
	std::set<std::string> m_compound;
	std::set<std::string> m_function;
	std::set<std::string> m_keyword;

	int m_sytle_mask = 0; // For wxWidgets > 3.1.0 this needs to be 0.

};

