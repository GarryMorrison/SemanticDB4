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

    // Load Lexer styles:
    LoadLexerStyles();

    // Load our sets of operator names:
    LoadOperatorMaps();

    // If using highlighting, let's highlight the starting text:
    if (m_use_highlighting)
    {
        SyntaxHighlight(0, GetTextLength(), text.ToStdString());
    }

    // Bind to our Styling method:
    Bind(wxEVT_STC_STYLENEEDED, &LexerTextCtrl::OnStyleNeeded, this);
    Bind(wxEVT_LEFT_UP, &LexerTextCtrl::OnMouseClick, this);
}

void LexerTextCtrl::LoadLexerStyles()
{
    // Map LEX objects to colours:  // Choose better colours using wxColor() later!
    StyleSetForeground(static_cast<int>(LEX::LEX_NONE), *wxBLACK);
    StyleSetForeground(static_cast<int>(LEX::LEX_LITERAL), wxColor(144, 144, 144));
    StyleSetForeground(static_cast<int>(LEX::LEX_SIMPLE), wxColor(255, 0, 0));
    StyleSetForeground(static_cast<int>(LEX::LEX_COMPOUND), *wxRED);
    StyleSetForeground(static_cast<int>(LEX::LEX_FUNCTION), *wxRED);
    StyleSetForeground(static_cast<int>(LEX::LEX_KEYWORD), *wxBLUE);
    StyleSetForeground(static_cast<int>(LEX::LEX_KET), wxColor(0, 0, 0));
    StyleSetForeground(static_cast<int>(LEX::LEX_KET_SPECIAL), wxColor(0, 0, 0));
    StyleSetForeground(static_cast<int>(LEX::LEX_COMMENT), *wxBLACK);
    StyleSetForeground(static_cast<int>(LEX::LEX_STRING), *wxBLUE);
    StyleSetForeground(static_cast<int>(LEX::LEX_USER_FN), *wxBLUE);
    StyleSetForeground(static_cast<int>(LEX::LEX_ERROR), *wxWHITE);

    StyleSetBackground(static_cast<int>(LEX::LEX_NONE), *wxWHITE);
    StyleSetBackground(static_cast<int>(LEX::LEX_LITERAL), *wxWHITE);
    StyleSetBackground(static_cast<int>(LEX::LEX_SIMPLE), *wxWHITE);
    StyleSetBackground(static_cast<int>(LEX::LEX_COMPOUND), *wxWHITE);
    StyleSetBackground(static_cast<int>(LEX::LEX_FUNCTION), *wxWHITE);
    StyleSetBackground(static_cast<int>(LEX::LEX_KEYWORD), *wxWHITE);
    StyleSetBackground(static_cast<int>(LEX::LEX_KET), wxColor(244, 244, 255));
    StyleSetBackground(static_cast<int>(LEX::LEX_KET_SPECIAL), wxColor(194, 194, 255));
    StyleSetBackground(static_cast<int>(LEX::LEX_COMMENT), wxColor(236, 255, 236));
    StyleSetBackground(static_cast<int>(LEX::LEX_STRING), *wxWHITE);
    StyleSetBackground(static_cast<int>(LEX::LEX_USER_FN), *wxWHITE);
    StyleSetBackground(static_cast<int>(LEX::LEX_ERROR), wxColor(255, 64, 64));

    StyleSetUnderline(static_cast<int>(LEX::LEX_NONE), false);
    StyleSetUnderline(static_cast<int>(LEX::LEX_LITERAL), false);
    StyleSetUnderline(static_cast<int>(LEX::LEX_SIMPLE), false);
    StyleSetUnderline(static_cast<int>(LEX::LEX_COMPOUND), false);
    StyleSetUnderline(static_cast<int>(LEX::LEX_FUNCTION), false);
    StyleSetUnderline(static_cast<int>(LEX::LEX_KEYWORD), false);
    StyleSetUnderline(static_cast<int>(LEX::LEX_KET), false);
    StyleSetUnderline(static_cast<int>(LEX::LEX_KET_SPECIAL), false);
    StyleSetUnderline(static_cast<int>(LEX::LEX_COMMENT), false);
    StyleSetUnderline(static_cast<int>(LEX::LEX_STRING), false);
    StyleSetUnderline(static_cast<int>(LEX::LEX_USER_FN), false);
    StyleSetUnderline(static_cast<int>(LEX::LEX_ERROR), false);

    StyleSetItalic(static_cast<int>(LEX::LEX_NONE), false);
    StyleSetItalic(static_cast<int>(LEX::LEX_LITERAL), false);
    StyleSetItalic(static_cast<int>(LEX::LEX_SIMPLE), false);
    StyleSetItalic(static_cast<int>(LEX::LEX_COMPOUND), false);
    StyleSetItalic(static_cast<int>(LEX::LEX_FUNCTION), false);
    StyleSetItalic(static_cast<int>(LEX::LEX_KEYWORD), false);
    StyleSetItalic(static_cast<int>(LEX::LEX_KET), false);
    StyleSetItalic(static_cast<int>(LEX::LEX_KET_SPECIAL), false);
    StyleSetItalic(static_cast<int>(LEX::LEX_COMMENT), true);
    StyleSetItalic(static_cast<int>(LEX::LEX_STRING), false);
    StyleSetItalic(static_cast<int>(LEX::LEX_USER_FN), false);
    StyleSetItalic(static_cast<int>(LEX::LEX_ERROR), false);
}

void LexerTextCtrl::LoadOperatorMaps()
{
    m_ket_special.insert("|context>");
    m_ket_special.insert("|*>");
    m_ket_special.insert("|_self>");
    m_ket_special.insert("|__self>");
    m_ket_special.insert("|__self0>");
    m_ket_special.insert("|__self1>");
    m_ket_special.insert("|__self2>");
    m_ket_special.insert("|__self3>");
    m_ket_special.insert("|__self4>");

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
    m_keyword.insert("in");
    m_keyword.insert("else:");
    m_keyword.insert("end:");
}

// void LexerTextCtrl::SyntaxHighlight(size_t start, size_t end, const wxString& text)
void LexerTextCtrl::SyntaxHighlight(size_t start, size_t end, const std::string& text)
{
    std::vector<LEX_OBJECT> lex_objects;
    size_t text_pos = 0;
    size_t start_pos = 0;
    size_t end_of_text = text.size();
    size_t start_token = 0;
    bool inside_comment = false;
    bool inside_ket = false;
    bool inside_object = false;
    bool inside_compound_parameters = false;
    bool inside_compound_string = false;
    bool inside_brackets = false;
    bool inside_braces = false;
    bool is_fresh_line = true;
    size_t start_square_bracket = 0;
    size_t start_bracket = 0;
    size_t start_line = 0;
    char c;
    std::string token;
    LEX_OBJECT object;
    while (text_pos < end_of_text)
    {
        c = text[text_pos];
        
        
        if (c == '-' && end_of_text > 2 && text[text_pos + 1] == '-')
        {
            if (is_fresh_line)
            {
                object.LEX_ID = LEX::LEX_COMMENT;
                object.start = text_pos - 1;
                inside_comment = true;
            }
            is_fresh_line = false;
            text_pos++;
            continue;
        }

        if (!(c == '\n' || c == ' '))
        {
            if (is_fresh_line)
            {
                size_t space_delta = text_pos - start_line - 1;
                if (space_delta % 4 != 0)
                {
                    object.LEX_ID = LEX::LEX_ERROR;
                    object.start = start_line + 1;
                    object.end = text_pos;
                    lex_objects.push_back(object);
                }
            }
            is_fresh_line = false;
        }

        if (inside_comment && c == '\n')
        {
            object.end = text_pos;
            lex_objects.push_back(object);
            inside_comment = false;
            is_fresh_line = true;
            start_line = text_pos;
            text_pos++;
            continue;
        }
        if (inside_comment)
        {
            text_pos++;
            continue;
        }

        if (c == '\n' && inside_object)
        {
            std::string op = text.substr(object.start, text_pos - object.start);
            if (m_keyword.find(op) != m_keyword.end())
            {
                object.LEX_ID = LEX::LEX_KEYWORD;
            }
            else
            {
                object.LEX_ID = LEX::LEX_LITERAL;
            }
            object.end = text_pos;
            lex_objects.push_back(object);
            inside_object = false;
            is_fresh_line = true;
            start_line = text_pos;
            text_pos++;
            continue;
        }

        if (c == '\n')
        {
            if (is_fresh_line)
            {
                size_t space_delta = text_pos - start_line - 1;
                if (space_delta % 4 != 0)
                {
                    object.LEX_ID = LEX::LEX_ERROR;
                    object.start = start_line + 1;
                    object.end = text_pos;
                    lex_objects.push_back(object);
                }
            }
            if (inside_ket)
            {
                object.LEX_ID = LEX::LEX_ERROR;
                object.end = text_pos;
                lex_objects.push_back(object);
                inside_ket = false;
            }
            else if (inside_brackets)
            {
                object.LEX_ID = LEX::LEX_ERROR;
                object.start = start_bracket;
                object.end = object.start + 1;
                lex_objects.push_back(object);
                inside_brackets = false;
            }
            else if (inside_compound_parameters)
            {
                object.LEX_ID = LEX::LEX_ERROR;
                object.start = start_square_bracket;
                object.end = object.start + 1;
                lex_objects.push_back(object);
                inside_compound_parameters = false;
            }
            is_fresh_line = true;
            start_line = text_pos;
            text_pos++;
            continue;
        }

        

        if (c == '|')
        {
            if (inside_object)
            {
                object.LEX_ID = LEX::LEX_SIMPLE;
                object.end = text_pos - 1;
                lex_objects.push_back(object);
                inside_object = false;
            }
            object.LEX_ID = LEX::LEX_KET;
            object.start = text_pos;
            inside_ket = true;
        }
        else if (c == '>' && inside_ket)
        {
            std::string op = text.substr(object.start, text_pos - object.start + 1);
            if (m_ket_special.find(op) != m_ket_special.end())
            {
                object.LEX_ID = LEX::LEX_KET_SPECIAL;
            }
            object.end = text_pos + 1;
            lex_objects.push_back(object);
            inside_ket = false;
            
        }
        else if (!inside_ket && !inside_object && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
        {
            object.start = text_pos;
            inside_object = true;
        }
        else if (!inside_ket && inside_object && (c == ' ' || c == ',' || c == ']' || c == ')' || c == '[' || c == '('))
        {
            object.end = text_pos;
            if (c == ' ' || c == ',' || c == ']' || c == ')')
            {
                std::string op = text.substr(object.start, text_pos - object.start);
                if (m_simple.find(op) != m_simple.end())
                {
                    object.LEX_ID = LEX::LEX_SIMPLE;
                }
                else if (m_keyword.find(op) != m_keyword.end())
                {
                    object.LEX_ID = LEX::LEX_KEYWORD;
                }
                else
                {
                    object.LEX_ID = LEX::LEX_LITERAL;
                }
                if (c == ']')
                {
                    inside_compound_parameters = false;
                }
                else if (c == ')')
                {
                    inside_brackets = false;
                }
            }
            else if (c == '[')
            {
                std::string op = text.substr(object.start, text_pos - object.start);
                if (m_compound.find(op) != m_compound.end())
                {
                    object.LEX_ID = LEX::LEX_COMPOUND;
                }
                else
                {
                    object.LEX_ID = LEX::LEX_ERROR;
                }
                inside_compound_parameters = true;
                start_square_bracket = text_pos;
            }
            else if (c == '(')
            {
                std::string op = text.substr(object.start, text_pos - object.start);
                if (m_function.find(op) != m_function.end())
                {
                    object.LEX_ID = LEX::LEX_FUNCTION;
                }
                else
                {
                    object.LEX_ID = LEX::LEX_USER_FN;
                }
                inside_brackets = true;
                start_bracket = text_pos;
            }
            lex_objects.push_back(object);
            inside_object = false;
        }
        else if (!inside_ket)
        {
            if (c == '(')
            {
                inside_brackets = true;
                start_bracket = text_pos;
                text_pos++;
                continue;
            }
            if (c == ')')
            {
                inside_brackets = false;
                text_pos++;
                continue;
            }
            if (c == ']')
            {
                inside_compound_parameters = false;
                text_pos++;
                continue;
            }
        }
        text_pos++;  // Move on to next char position
    }

    // Remove the old styling:  // This is buggy for now, so leave it out
    StartStyling(start);
    SetStyling(end - start, static_cast<int>(LEX::LEX_NONE));

    // Style the lex objects:
    for (LEX_OBJECT object : lex_objects)
    {
        StartStyling(start + object.start);
        SetStyling(object.end - object.start, static_cast<int>(object.LEX_ID));
    }
}

void LexerTextCtrl::OnStyleNeeded(wxStyledTextEvent& event)
{
    size_t line_end = LineFromPosition(GetCurrentPos());
    size_t line_start = LineFromPosition(GetEndStyled());

    // if it is on one page, style the whole document:
    if (GetLineCount() == LinesOnScreen())
    {
        line_start = 0;
        line_end = GetLineCount() - 1;
    }

    if (line_end < line_start)
    {
        std::swap(line_start, line_end);
    }

    // Now find positions:
    size_t start_pos = PositionFromLine(line_start);
    size_t end_pos = GetLineEndPosition(line_end);
    std::string local_text = GetTextRange(start_pos, end_pos).ToStdString();

    // Now highlight it all:
    SyntaxHighlight(start_pos, end_pos, local_text);

    // event.Skip();   // Is this needed?
}

void LexerTextCtrl::OnMouseClick(wxMouseEvent& event)
{
    // wxMessageBox("Mouse click");
    size_t line_start = 0;
    size_t line_end = LinesOnScreen() - 1;

    // Now find positions:
    size_t start_pos = PositionFromLine(line_start);
    size_t end_pos = GetLineEndPosition(line_end);
    std::string local_text = GetTextRange(start_pos, end_pos).ToStdString();

    // Now highlight it all:
    SyntaxHighlight(start_pos, end_pos, local_text);

    event.Skip();
}


LexerTextCtrl::~LexerTextCtrl()
{};

