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
}

void LexerTextCtrl::LoadLexerStyles()
{
    // Map LEX objects to foreground colours:  // Choose better colours using wxColor() later!
    StyleSetForeground(static_cast<int>(LEX::LEX_NONE), *wxBLACK);
    StyleSetForeground(static_cast<int>(LEX::LEX_LITERAL), wxColor(144, 144, 144));
    StyleSetForeground(static_cast<int>(LEX::LEX_SIMPLE), wxColor(255, 0, 0));
    StyleSetForeground(static_cast<int>(LEX::LEX_COMPOUND), *wxRED);
    StyleSetForeground(static_cast<int>(LEX::LEX_FUNCTION), *wxRED);
    StyleSetForeground(static_cast<int>(LEX::LEX_KEYWORD), *wxRED);
    StyleSetForeground(static_cast<int>(LEX::LEX_KET), wxColor(0, 0, 0));
    StyleSetForeground(static_cast<int>(LEX::LEX_COMMENT), *wxBLACK);
    StyleSetForeground(static_cast<int>(LEX::LEX_STRING), *wxBLUE);
    StyleSetForeground(static_cast<int>(LEX::LEX_USER_FN), *wxBLUE);
    StyleSetForeground(static_cast<int>(LEX::LEX_ERROR), *wxBLUE);

    StyleSetBackground(static_cast<int>(LEX::LEX_NONE), *wxWHITE);
    StyleSetBackground(static_cast<int>(LEX::LEX_LITERAL), *wxWHITE);
    StyleSetBackground(static_cast<int>(LEX::LEX_SIMPLE), *wxWHITE);
    StyleSetBackground(static_cast<int>(LEX::LEX_COMPOUND), *wxWHITE);
    StyleSetBackground(static_cast<int>(LEX::LEX_FUNCTION), *wxWHITE);
    StyleSetBackground(static_cast<int>(LEX::LEX_KEYWORD), *wxWHITE);
    StyleSetBackground(static_cast<int>(LEX::LEX_KET), wxColor(244, 244, 255));
    StyleSetBackground(static_cast<int>(LEX::LEX_COMMENT), wxColor(236, 255, 236));
    StyleSetBackground(static_cast<int>(LEX::LEX_STRING), *wxWHITE);
    StyleSetBackground(static_cast<int>(LEX::LEX_USER_FN), *wxWHITE);
    StyleSetBackground(static_cast<int>(LEX::LEX_ERROR), *wxRED);
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
    char c;
    std::string token;
    LEX_OBJECT object;
    while (text_pos < end_of_text)  // This approach vs using for (const char c: string) ?
    {
        c = text[text_pos];
        
        if (c == '-' && text_pos > 0 && text[text_pos - 1] == '-')
        {
            object.LEX_ID = LEX::LEX_COMMENT;
            object.start = text_pos - 1;
            inside_comment = true;
            text_pos++;
            continue;
        }
        if (inside_comment && c == '\n')
        {
            object.end = text_pos;
            lex_objects.push_back(object);
            inside_comment = false;
            text_pos++;
            continue;
        }
        if (inside_comment)
        {
            text_pos++;
            continue;
        }

        if (inside_object && c == '\n')
        {
            object.LEX_ID = LEX::LEX_LITERAL;
            object.end = text_pos;
            lex_objects.push_back(object);
            inside_object = false;
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
        else if (inside_ket && c == '>')
        {
            object.end = text_pos + 1;
            lex_objects.push_back(object);

            // Reset object:  // Do we even need this?
            // object.LEX_ID = LEX::LEX_NONE;
            // object.start = 0;
            // object.end = 0;

            // Switch off inside_ket:
            inside_ket = false;
            // token.Clear();  // Shouldn't be needed
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
                else
                {
                    object.LEX_ID = LEX::LEX_LITERAL;
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
            }
            lex_objects.push_back(object);

            // Do we need to clear object here? Possibly not, if we do it right.
            // object.LEX_ID = LEX::LEX_NONE;
            // object.start = 0;
            // object.end = 0;

            inside_object = false;
        }
        /*
        else if (!inside_ket)
        {
            

            token.Append(c);
        }
        */

        text_pos++;  // Move on to next char position
    }

    // Remove the old styling:  // This is buggy for now, so leave it out
    // StartStyling(start);
    // SetStyling(end - start, 0);

    // Style the lex objects:
    for (LEX_OBJECT object : lex_objects)
    {
        StartStyling(object.start);
        SetStyling(object.end - object.start, static_cast<int>(object.LEX_ID));
    }
}

void LexerTextCtrl::OnStyleNeeded(wxStyledTextEvent& event)  // Buggy on update, for some reason!
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
    this->SyntaxHighlight(start_pos, end_pos, local_text);

    // event.Skip();   // Is this needed?
}

LexerTextCtrl::~LexerTextCtrl()
{};

