//
// Semantic DB 4
// Created 2023/6/18
// Updated 2023/6/18
// Author Garry Morrison
// License GPL v3
//

#include "LexerColorMap.h"

LexerColorMap::LexerColorMap()
{
	m_ID_list.push_back(LEX::LEX_NONE);
	m_ID_list.push_back(LEX::LEX_LITERAL);
	m_ID_list.push_back(LEX::LEX_SIMPLE);
	m_ID_list.push_back(LEX::LEX_COMPOUND);
	m_ID_list.push_back(LEX::LEX_FUNCTION);
	m_ID_list.push_back(LEX::LEX_KEYWORD);
	m_ID_list.push_back(LEX::LEX_KET);
	m_ID_list.push_back(LEX::LEX_KET_SPECIAL);
	m_ID_list.push_back(LEX::LEX_COMMENT);
	m_ID_list.push_back(LEX::LEX_STRING);
	m_ID_list.push_back(LEX::LEX_USER_FN);
	m_ID_list.push_back(LEX::LEX_ERROR);

	m_string_map["LEX_NONE"] = LEX::LEX_NONE;
	m_string_map["LEX_LITERAL"] = LEX::LEX_LITERAL;
	m_string_map["LEX_SIMPLE"] = LEX::LEX_SIMPLE;
	m_string_map["LEX_COMPOUND"] = LEX::LEX_COMPOUND;
	m_string_map["LEX_FUNCTION"] = LEX::LEX_FUNCTION;
	m_string_map["LEX_KEYWORD"] = LEX::LEX_KEYWORD;
	m_string_map["LEX_KET"] = LEX::LEX_KET;
	m_string_map["LEX_KET_SPECIAL"] = LEX::LEX_KET_SPECIAL;
	m_string_map["LEX_COMMENT"] = LEX::LEX_COMMENT;
	m_string_map["LEX_STRING"] = LEX::LEX_STRING;
	m_string_map["LEX_USER_FN"] = LEX::LEX_USER_FN;
	m_string_map["LEX_ERROR"] = LEX::LEX_ERROR;
}

void LexerColorMap::EnableHighlights()
{
	m_use_highlights = true;  // Do more here later!
	LoadDefaults();
}

void LexerColorMap::DisableHighlights()
{
	m_use_highlights = false; // Do more here later!

	// Load the default background colours:
	for (const auto& id : m_ID_list)
	{
		m_background_colors[id] = *wxWHITE;
	}

	// Load the default foreground colours:
	for (const auto& id : m_ID_list)
	{
		m_foreground_colors[id] = *wxBLACK;
	}

	// Load the default underline state:
	for (const auto& id : m_ID_list)
	{
		m_underlines[id] = false;
	}

	// Load the default italic state:
	for (const auto& id : m_ID_list)
	{
		m_italics[id] = false;
	}

	// Load the default bold state:
	for (const auto& id : m_ID_list)
	{
		m_bold[id] = false;
	}
}

void LexerColorMap::LoadDefaults()
{
	// Load the default background colours:
	for (const auto& id : m_ID_list)
	{
		m_background_colors[id] = *wxWHITE;
	}

	// Load the default foreground colours:
	for (const auto& id : m_ID_list)
	{
		m_foreground_colors[id] = *wxBLACK;
	}

	// Load the default underline state:
	for (const auto& id : m_ID_list)
	{
		m_underlines[id] = false;
	}

	// Load the default italic state:
	for (const auto& id : m_ID_list)
	{
		m_italics[id] = false;
	}

	// Load the default bold state:
	for (const auto& id : m_ID_list)
	{
		m_bold[id] = false;
	}

	// Now my choices:
	m_foreground_colors[LEX::LEX_LITERAL] = wxColor(144, 144, 144);
	m_foreground_colors[LEX::LEX_SIMPLE] = *wxRED;
	m_foreground_colors[LEX::LEX_COMPOUND] = *wxRED;
	m_foreground_colors[LEX::LEX_FUNCTION] = *wxRED;
	m_foreground_colors[LEX::LEX_KEYWORD] = *wxBLUE;
	m_foreground_colors[LEX::LEX_STRING] = *wxBLUE;
	m_foreground_colors[LEX::LEX_USER_FN] = wxColor(144, 144, 144);
	m_foreground_colors[LEX::LEX_ERROR] = *wxWHITE;

	m_background_colors[LEX::LEX_KET] = wxColor(244, 244, 255);
	m_background_colors[LEX::LEX_ERROR] = wxColor(255, 64, 64);
	
	m_italics[LEX::LEX_COMMENT] = true;
	
	m_bold[LEX::LEX_KET_SPECIAL] = true;
}

bool LexerColorMap::LoadSettings(const wxString& filepath)
{
	// Load a local driver/context and load in the style sw file:

	ContextList local_context("load lexer colors");
	Sequence local_result;
	SDB::Driver local_driver(local_context, local_result);

	wxMessageBox("Lexer to load file: " + filepath);

	wxFileInputStream input_stream(filepath);
	if (!input_stream.IsOk())
	{
		wxLogError("Cannot open style file '%s'.", filepath);
		return false;
	}

	wxString lexer_content;
	wxTextInputStream text(input_stream, wxT("\x09"), wxConvUTF8);  // Check these settings are correct later.
	while (input_stream.IsOk() && !input_stream.Eof())
	{
		lexer_content.Append(text.ReadLine());
		lexer_content.Append("\n");  // There must be a better way to keep newlines in the text!
	}

	if (lexer_content.IsEmpty())  // If it is somehow empty, we can't do anything!
	{
		return false;
	}

	wxMessageBox("Lexer content:\n" + lexer_content);

	// Now parse it:
	local_driver.parse_string(lexer_content.ToStdString());

	std::string use_syntax_highlight = local_context.recall("use", "syntax highlight")->to_ket().label();
	if ( use_syntax_highlight == "false")
	{
		wxMessageBox("Don't use syntax highlighting");
		DisableHighlights();
		return false;
	}
	else if (use_syntax_highlight == "true")
	{
		wxMessageBox("Use syntax highlighting");
		EnableHighlights();  // Note this function loads in the default highlights.
	}
	else
	{
		return false;
	}

	return true;
}

std::vector<LEX> LexerColorMap::GetIDList()
{
	return m_ID_list;
}

LEX LexerColorMap::GetID(const std::string& s)
{
	if (m_string_map.find(s) == m_string_map.end())
	{
		return LEX::LEX_NONE;
	}
	return m_string_map[s];
}

wxColor LexerColorMap::GetBackgroundColor(LEX id)
{
	if (m_background_colors.find(id) == m_background_colors.end())
	{
		return *wxWHITE;
	}
	return m_background_colors[id];
}

wxColor LexerColorMap::GetForegroundColor(LEX id)
{
	if (m_foreground_colors.find(id) == m_foreground_colors.end())
	{
		return *wxBLACK;
	}
	return m_foreground_colors[id];
}

bool LexerColorMap::GetUnderline(LEX id)
{
	if (m_underlines.find(id) == m_underlines.end())
	{
		return false;
	}
	return m_underlines[id];
}

bool LexerColorMap::GetItalic(LEX id)
{
	if (m_italics.find(id) == m_italics.end())
	{
		return false;
	}
	return m_italics[id];
}

bool LexerColorMap::GetBold(LEX id)
{
	if (m_bold.find(id) == m_bold.end())
	{
		return false;
	}
	return m_bold[id];
}

LexerColorMap::~LexerColorMap()
{}
