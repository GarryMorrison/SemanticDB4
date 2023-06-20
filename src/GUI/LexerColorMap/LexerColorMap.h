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

/*  // Deprecated by GetIDList()
const LEX LEX_values[] = {
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
*/

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
	void LoadMyDefaults();
	bool LoadSettings(const wxString& filepath);

	std::vector<LEX> GetIDList();
	LEX GetID(const std::string& s);
	wxColor GetPanelBackgroundColor() { return m_panel_background_color; }
	wxColor GetPanelForegroundColor() { return m_panel_foreground_color; }
	wxColor GetBackgroundColor(LEX id);
	wxColor GetForegroundColor(LEX id);
	bool GetUnderline(LEX id);
	bool GetItalic(LEX id);
	bool GetBold(LEX id);

	~LexerColorMap();

private:
	bool IsValidColorString(const wxString& color_string);

	bool m_use_highlights = true;
	std::vector<LEX> m_ID_list;
	std::map<std::string, LEX> m_string_map;
	wxColor m_panel_background_color;
	wxColor m_panel_foreground_color;
	std::map<LEX, wxColor> m_background_colors;
	std::map<LEX, wxColor> m_foreground_colors;
	std::map<LEX, bool> m_underlines;
	std::map<LEX, bool> m_italics;
	std::map<LEX, bool> m_bold;
};

