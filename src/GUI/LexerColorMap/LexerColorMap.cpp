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
}

void LexerColorMap::DisableHighlights()
{
	m_use_highlights = false; // Do more here later!
}

void LexerColorMap::LoadDefaults()
{
	// Load the default background colours:
	for (const auto& id : LEX_values)
	{
		m_background_colors[id] = *wxWHITE;
	}

	// Load the default foreground colours:
	for (const auto& id : LEX_values)
	{
		m_foreground_colors[id] = *wxBLACK;
	}

	// Load the default underline state:
	for (const auto& id : LEX_values)
	{
		m_underlines[id] = false;
	}

	// Load the default italic state:
	for (const auto& id : LEX_values)
	{
		m_italics[id] = false;
	}

	// Load the default bold state:
	for (const auto& id : LEX_values)
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

void LexerColorMap::LoadSettings(const wxString& filepath)
{
	// Load a local driver/context and load in the style sw file?
}

LexerColorMap::~LexerColorMap()
{}