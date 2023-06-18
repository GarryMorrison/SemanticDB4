//
// Semantic DB 4
// Created 2023/6/18
// Updated 2023/6/18
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
	LEX_KET = 16,
	LEX_KET_SPECIAL = 17,
	LEX_COMMENT = 18,
	LEX_STRING = 19,
	LEX_USER_FN = 20,
	LEX_ERROR = 21
};

constexpr LEX LEX_values[] = {
	LEX::LEX_NONE,
	LEX::LEX_LITERAL,
	LEX::LEX_SIMPLE,
	LEX::LEX_COMPOUND,
	LEX::LEX_FUNCTION,
	LEX::LEX_KEYWORD,
	LEX::LEX_KET,
	LEX::LEX_KET_SPECIAL,
	LEX::LEX_COMMENT,
	LEX::LEX_STRING,
	LEX::LEX_USER_FN,
	LEX::LEX_ERROR
};

struct LEX_OBJECT {  // Seems we need it here, and not in LexerTextCtrl. Else LEX::LEX_NONE is not defined.
	LEX LEX_ID = LEX::LEX_NONE;
	size_t start = 0;
	size_t end = 0;
};

class LexerColorMap
{
public:
	LexerColorMap();
	
	bool GetHighlightStatus() { return m_use_highlights; }
	void EnableHighlights();
	void DisableHighlights();

	void LoadDefaults();
	void LoadSettings(const wxString& filepath);

	/*
	LEX GetID(const std::string& s) { return m_string_map.at(s); }  // Maybe use wrappers to return default values if s or id is not in the map
	wxColor GetBackgroundColor(LEX id) { return m_background_colors.at(id); }
	wxColor GetforegroundColor(LEX id) { return m_foreground_colors.at(id); }
	bool GetUnderline(LEX id) { return m_underlines.at(id); }
	bool GetItalic(LEX id) { return m_italics.at(id); }
	bool GetBold(LEX id) { return m_bold.at(id); }
	*/

	LEX GetID(const std::string& s);
	wxColor GetBackgroundColor(LEX id);
	wxColor GetforegroundColor(LEX id);
	bool GetUnderline(LEX id);
	bool GetItalic(LEX id);
	bool GetBold(LEX id);

	~LexerColorMap();

private:
	bool m_use_highlights = true;
	std::map<std::string, LEX> m_string_map;
	std::map<LEX, wxColor> m_background_colors;
	std::map<LEX, wxColor> m_foreground_colors;
	std::map<LEX, bool> m_underlines;
	std::map<LEX, bool> m_italics;
	std::map<LEX, bool> m_bold;
};
