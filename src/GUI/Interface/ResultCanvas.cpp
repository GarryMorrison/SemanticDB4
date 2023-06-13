//
// Semantic DB 4
// Created 2021/12/28
// Updated 2022/1/18
// Author Garry Morrison
// License GPL v3
//

#include "ResultCanvas.h"


ResultCanvas::ResultCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxScrolledWindow(parent, id, pos, size, style | wxBORDER_THEME)
{
    SetScrollbars(20, 20, 50, 50);  // Finally solved my scrolling issue!
    m_mouse_pos = wxPoint(0, 0);

    // Set font types:
    wxClientDC local_dc(this);
    m_starting_font = local_dc.GetFont();
    m_mono_font = m_starting_font;
    m_mono_font.SetFamily(wxFONTFAMILY_TELETYPE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &ResultCanvas::OnPaint, this);
    Bind(wxEVT_MOTION, &ResultCanvas::OnMouseMove, this);
    Bind(wxEVT_LEFT_DOWN, &ResultCanvas::OnMouseLeftClick, this);
    Bind(wxEVT_KEY_DOWN, &ResultCanvas::OnKeyDown, this);
    Bind(wxEVT_KEY_UP, &ResultCanvas::OnKeyUp, this);
    // Bind(wxEVT_SCROLLWIN_BOTTOM, &ResultPanel::OnScroll, this);  // Scrolling is broken for now!
}

void ResultCanvas::OnPaint(wxPaintEvent& event)
{
    //wxPaintDC pdc(this);
    wxAutoBufferedPaintDC pdc(this);
    // DoPrepareDC(pdc);
    Draw(pdc);
    event.Skip(true);
}


void ResultCanvas::AppendText(const wxString& wxs, bool isactive, int object_type, bool ismonospace)
{
    wxClientDC local_dc(this);
    if (ismonospace) {
        local_dc.SetFont(m_mono_font);  // Set up a bool so we don't keep switching each time around?
    }
    else
    {
        local_dc.SetFont(m_starting_font);
    }
    int textWidth, textHeight;
    local_dc.GetTextExtent(wxs, &textWidth, &textHeight);
    m_canvas_objects.push_back(std::make_shared<ResultCanvasString>(this, wxs, isactive, object_type, ismonospace, wxRect(m_x, m_y, textWidth, textHeight)));
    m_x += textWidth;
    m_last_y = std::max(m_last_y, m_y + textHeight);
    m_max_x = std::max(m_max_x, m_x);
    Refresh();
}

void ResultCanvas::AppendMultiLineText(const wxString& wxs, bool isactive, int object_type, bool ismonospace)
{
    for (const auto& line : split(wxs.ToStdString(), "\n"))
    {
        AppendText(line, isactive, object_type, ismonospace);
        // AppendNewLine();
        m_canvas_objects.push_back(std::make_shared<ResultCanvasNewLine>());
        m_x = 10;
        m_y = m_last_y;
        m_last_y = m_y;
    }
    Refresh();
}

void ResultCanvas::AppendActiveText(const wxString& wxs, const wxString& prefix, const bool is_mono)  // Can we write a faster version!! Tidy it!!
{
    std::string text = wxs.ToStdString(); // Use standard string for now ...  // And split on new line chars.
    std::vector<std::string> split_text = split(text, "\n");
    if (split_text.size() == 2 && split_text.back().empty()) // If just a single line with a new line at the end, strip the final new line.
    {
        split_text.pop_back();
    }

    std::string token;

    if (!prefix.empty())
    {
        AppendText(prefix, false, RC_OBJECT_NONE, is_mono);
    }
    for (const auto line : split_text)
    {
        token.clear();
        bool inside_object = false;
        bool inside_ket = false;
        int the_object_type = RC_OBJECT_NONE;
        char last_char;
        for (char c : line)
        {
            if (!inside_ket && c == '|')
            {
                if (inside_object)
                {
                    AppendText(token, true, RC_OBJECT_SIMPLE_OP, is_mono);
                }
                else
                {
                    AppendText(token, false, RC_OBJECT_NONE, is_mono);
                }
                inside_object = false;
                inside_ket = true;
                token = c;
            }
            else if (inside_ket && c == '>')
            {
                inside_ket = false;
                AppendText(wxString(token + c), true, RC_OBJECT_KET, is_mono);
                token.clear();
            }
            else if (!inside_ket && !inside_object && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))  // Use c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' instead?
            {
                inside_object = true;
                AppendText(token, false, RC_OBJECT_NONE, is_mono);
                token = c;
            }
            else if (!inside_ket && inside_object && (c == ' ' || c == ',' || c == ']' || c == ')' || c == '[' || c == '(')) // [ -> compound op, ( -> function op, ] or ) -> simple op.
            {
                the_object_type = RC_OBJECT_NONE;
                if (c == ' ' || c == ',' || c == ']' || c == ')')
                {
                    the_object_type = RC_OBJECT_SIMPLE_OP;
                }
                else if (c == '[')
                {
                    the_object_type = RC_OBJECT_COMPOUND_OP;
                }
                else if (c == '(')
                {
                    the_object_type = RC_OBJECT_FUNCTION_OP;
                }
                inside_object = false;
                AppendText(token, true, the_object_type, is_mono);
                token = c;
            }
            else
            {
                token += c;
            }
            last_char = c;
        }
        if (inside_object && (last_char == ' ' || last_char == ',' || last_char == ']' || last_char == ')' || last_char == '[' || last_char == '('))  // Need to correctly handle end of line.
        {
            the_object_type = RC_OBJECT_NONE;
            if (last_char == ' ' || last_char == ',' || last_char == ']' || last_char == ')')
            {
                the_object_type = RC_OBJECT_SIMPLE_OP;
            }
            else if (last_char == '[')
            {
                the_object_type = RC_OBJECT_COMPOUND_OP;
            }
            else if (last_char == '(')
            {
                the_object_type = RC_OBJECT_FUNCTION_OP;
            }
            AppendText(token, true, the_object_type, is_mono);
        }
        else if (inside_object)
        {
            AppendText(token, true, RC_OBJECT_SIMPLE_OP, is_mono);  // I think this must be a simple operator?
        }
        else
        {
            AppendText(token, false, RC_OBJECT_NONE, is_mono);
        }
        AppendNewLine();
    }
}



void ResultCanvas::AppendNewLine()
{
    m_x = 10;
    m_y = m_last_y + 5;  // Maybe something bigger than 5? 10?
    m_canvas_objects.push_back(std::make_shared<ResultCanvasNewLine>());  // Do we still need this here?
    m_last_y = m_y;
    SetVirtualSize(m_max_x, m_y);
    Refresh();
}


void ResultCanvas::AppendLine()
{
    m_x = 10;
    m_y = m_last_y + 5;
    m_last_y = m_y;
    m_canvas_objects.push_back(std::make_shared<ResultCanvasLine>(this, m_y));
    m_y += 5;
    SetVirtualSize(m_max_x, m_y);
    Refresh();
}

const wxString ResultCanvas::GetText() const
{
    wxString the_text;
    for (const auto& object : m_canvas_objects)
    {
        the_text += object->GetText();  // We may need to apply new-lines somehow ...
    }
    return the_text;
}

void ResultCanvas::OnKeyDown(wxKeyEvent& event)  // KeyDown and KeyUp don't seem to work .... Fix.
{
    m_is_shift_down = event.ShiftDown();
    event.Skip();
}


void ResultCanvas::OnKeyUp(wxKeyEvent& event)
{
    if (m_is_shift_down && !m_mouse_positions.empty())
    {
        std::vector<std::string> vect_of_literal_operators;
        std::vector<std::string> vect_of_kets;

        for (const auto& object : m_canvas_objects)
        {
            if (object->IsActivated()) 
            {
                std::string label = object->GetText().ToStdString();
                switch (object->GetObjectType())
                {
                case RC_OBJECT_KET: {  // We have a ket.
                    vect_of_kets.push_back(label);
                    break;
                }
                case RC_OBJECT_SIMPLE_OP: {
                    ulong idx = ket_map.get_idx(label);
                    if (fn_map.set_simple_operators.find(idx) != fn_map.set_simple_operators.end())  // We have a simple operator, not a literal operator.
                    {
                        m_usage_frame_position_delta += wxPoint(40, 40);
                        UsageFrame* usage_frame = new UsageFrame(this, label, m_usage_frame_position_delta);
                        // m_usage_frame_position_delta += wxPoint(40, 40);
                    }
                    else
                    {
                        vect_of_literal_operators.push_back(label);  // We have a literal operator.
                    }
                    break;
                }
                case RC_OBJECT_COMPOUND_OP:
                case RC_OBJECT_FUNCTION_OP: {
                    m_usage_frame_position_delta += wxPoint(40, 40);
                    UsageFrame* usage_frame = new UsageFrame(this, label, m_usage_frame_position_delta);
                    // m_usage_frame_position_delta += wxPoint(40, 40);
                    break;
                }
                default:
                    break;
                }
            }
        }
        if (!vect_of_kets.empty() || !vect_of_literal_operators.empty())
        {
            m_usage_frame_position_delta += wxPoint(40, 40);
            FilteredDumpFrame* dump_frame = new FilteredDumpFrame(this, "Knowledge for stuff ...", vect_of_literal_operators, vect_of_kets, m_usage_frame_position_delta);
            // m_usage_frame_position_delta += wxPoint(40, 40);
        }
    }
    m_is_shift_down = false;
    m_mouse_positions.clear();
    Refresh();
    event.Skip();
}


void ResultCanvas::SetMousePosition(const wxPoint& pt)
{
    m_mouse_pos = pt;
}

void ResultCanvas::OnMouseMove(wxMouseEvent& event)
{
    long x = 0;
    long y = 0;
    event.GetPosition(&x, &y);
    m_mouse_pos = wxPoint(x, y);
    SetFocusIgnoringChildren();
    Refresh();
    event.Skip();
}


void ResultCanvas::OnMouseLeftClick(wxMouseEvent& event)
{
    long x = 0;
    long y = 0;
    event.GetPosition(&x, &y);
    m_mouse_pos = wxPoint(x, y);
    
    if (event.ShiftDown())
    {
        m_is_shift_down = true;
        m_mouse_positions.push_back(m_mouse_pos);
        // SetFocusIgnoringChildren();
    }
    else
    {
        for (const auto& object : m_canvas_objects)
        {
            object->OnMouseLeftClick();
        }
    }
    event.Skip();
}


void ResultCanvas::ClearCanvas()  // Tidy!
{
    m_x = 10;
    m_y = 10;
    m_last_y = 10;
    m_max_x = 10;
    m_mouse_pos = wxPoint(0, 0);
    m_mouse_positions.clear();

    m_canvas_objects.clear();
    ClearBackground();
}

void ResultCanvas::Draw(wxAutoBufferedPaintDC& pdc)
{
    pdc.Clear();
    // ClearBackground();
    DoPrepareDC(pdc);  // Nope. Scrolling doesn't seem to work yet ....
    // pdc.SetPen(*wxBLACK_PEN);
    pdc.SetPen(*wxBLUE_PEN);
    pdc.SetBrush(*wxTRANSPARENT_BRUSH);
    // pdc.SetBackgroundMode(wxTRANSPARENT);

    for (const auto& object : m_canvas_objects)
    {
        object->Draw(pdc);
    }
    // SetVirtualSize(m_x, m_y); // Not the best location for it.
}


void ResultCanvas::OnScroll(wxScrollWinEvent& scroll_event)
{
    wxScrolledWindow::HandleOnScroll(scroll_event);

    Refresh();
}

wxFont ResultCanvas::GetMonoFont()
{
    return m_mono_font;
}

wxFont ResultCanvas::GetStartingFont()
{
    return m_starting_font;
}

wxPoint ResultCanvas::GetMousePos()
{
    return m_mouse_pos;
}

std::vector<wxPoint> ResultCanvas::GetMousePositions()
{
    return m_mouse_positions;
}

wxPoint ResultCanvas::GetPositionDelta()
{
    return m_usage_frame_position_delta;
}

void ResultCanvas::SetPositionDelta(const wxPoint& pt)
{
    m_usage_frame_position_delta = pt;
}

void ResultCanvas::IncreasePositionDelta(const wxPoint& pt)
{
    m_usage_frame_position_delta += pt;
}

bool ResultCanvas::ShiftDown()
{
    return m_is_shift_down;
}

ResultCanvas::~ResultCanvas()
{}



// Start of ResultCanvasString code:
ResultCanvasString::ResultCanvasString(ResultCanvas* parent, const wxString& wxs, bool isactive, int object_type, bool ismonospace, const wxRect& rect)
    : m_parent(parent), m_text(wxs), m_isactive(isactive), m_object_type(object_type), m_ismonospace(ismonospace), m_rect(rect)
{}

const void ResultCanvasString::Draw(wxAutoBufferedPaintDC& pdc) const
{
    bool is_selected_text = false;
    for (wxPoint mouse_pos : m_parent->GetMousePositions())
    {
        if (m_rect.Contains(mouse_pos))
        {
            is_selected_text = true;
            break;
        }
    }

    if (m_ismonospace) {
        pdc.SetFont(m_parent->GetMonoFont());
    }
    if (m_isactive && (m_rect.Contains(m_parent->GetMousePos()) || is_selected_text))
    {
        // pdc.SetTextForeground(*wxRED);
        pdc.SetTextForeground(*wxBLACK);
        pdc.SetTextBackground(*wxLIGHT_GREY);
        pdc.SetBackgroundMode(wxSOLID);
        pdc.DrawText(m_text, m_rect.x, m_rect.y);
        // pdc.DrawRectangle(the_text_struct.rect);
        // wxMessageBox(wxString::Format("Object type: %d", the_text_struct.object_type));
    }
    else if (m_isactive)
    {
        switch (m_object_type)
        {
        case RC_OBJECT_KET: {
            pdc.SetTextForeground(*wxBLUE);
            break;
        }
        case RC_OBJECT_SIMPLE_OP: {
            if (operator_usage_map.usage_is_defined(m_text.ToStdString()))
            {
                pdc.SetTextForeground(*wxRED);
            }
            else
            {
                pdc.SetTextForeground(*wxLIGHT_GREY);
            }
            break;
        }
        case RC_OBJECT_COMPOUND_OP: {
            pdc.SetTextForeground(*wxCYAN);
            break;
        }
        case RC_OBJECT_FUNCTION_OP: {
            pdc.SetTextForeground(*wxYELLOW);
            break;
        }
        default:
            pdc.SetTextForeground(*wxBLACK);
            break;
        }
        // pdc.SetTextForeground(*wxBLUE);
        pdc.SetBackgroundMode(wxTRANSPARENT);
        pdc.DrawText(m_text, m_rect.x, m_rect.y);
    }
    else
    {
        pdc.SetBackgroundMode(wxTRANSPARENT);
        pdc.SetTextForeground(*wxBLACK);
        pdc.DrawText(m_text, m_rect.x, m_rect.y);
    }
    if (m_ismonospace)
    {
        pdc.SetFont(m_parent->GetStartingFont());
    }
}

const void ResultCanvasString::OnMouseLeftClick() const
{
    if (m_isactive && m_rect.Contains(m_parent->GetMousePos()))
    {
        wxPoint position_delta = m_parent->GetPositionDelta();
        // wxMessageBox("Object clicked: " + the_text_struct.text);
        switch (m_object_type)
        {
        case RC_OBJECT_KET: {
            // wxMessageBox("Ket clicked: " + the_text_struct.text);
            std::string ket_label = strip_ket(m_text.ToStdString());  // wxString vs std::string again!
            Ket k(ket_label);
            std::vector<ulong> operators;
            operators.push_back(ket_map.get_idx("*"));
            std::vector<ulong> general_operators;
            std::string knowledge = dump(k, context, operators, general_operators);
            DumpFrame* dump_frame = new DumpFrame(m_parent, "Knowledge for " + m_text, knowledge, m_parent->GetPositionDelta());  // Change constructor later.
            m_parent->IncreasePositionDelta(wxPoint(40, 40));
            break;
        }
        case RC_OBJECT_SIMPLE_OP:
        case RC_OBJECT_COMPOUND_OP:
        case RC_OBJECT_FUNCTION_OP: {
            // wxMessageBox("Operator clicked: " + the_text_struct.text);
            std::string the_operator = m_text.ToStdString();
            if (!operator_usage_map.usage_is_defined(the_operator))
            {
                // wxMessageBox("No usage info available for operator: " + the_operator);
                Superposition ket_sp(context.relevant_kets(the_operator));
                std::vector<ulong> operators;
                operators.push_back(ket_map.get_idx(the_operator));
                std::vector<ulong> general_operators;
                std::string knowledge = dump(ket_sp, context, operators, general_operators);
                DumpFrame* dump_frame = new DumpFrame(m_parent, "Knowledge for " + m_text, knowledge, m_parent->GetPositionDelta());  // Change constructor later.
                m_parent->IncreasePositionDelta(wxPoint(40, 40));
                return;
            }
            UsageFrame* dlg = new UsageFrame(m_parent, the_operator, m_parent->GetPositionDelta());
            m_parent->IncreasePositionDelta(wxPoint(40, 40));
            break;
        }
        default: {
            wxMessageBox("Unknown object: " + m_text);
        }
        }
    }
}


const bool ResultCanvasString::IsActivated() const
{
    if (m_isactive)
    {
        for (wxPoint mouse_pos : m_parent->GetMousePositions())
        {
            if (m_rect.Contains(mouse_pos))
            {
                return true;
            }
        }
    }
    return false;
}

const wxString ResultCanvasString::GetText() const
{
    return m_text;
}

const int ResultCanvasString::GetObjectType() const
{
    return m_object_type;
}

ResultCanvasString::~ResultCanvasString()
{}


ResultCanvasNewLine::ResultCanvasNewLine()
{}

ResultCanvasNewLine::~ResultCanvasNewLine()
{}


// Start of ResultCanvasLine code:
ResultCanvasLine::ResultCanvasLine(ResultCanvas* parent, int line)
    : m_parent(parent), m_line(line)
{}

const void ResultCanvasLine::Draw(wxAutoBufferedPaintDC& pdc) const
{
    wxSize s = m_parent->GetClientSize();
    pdc.DrawLine(0, m_line, s.GetWidth(), m_line);
}


ResultCanvasLine::~ResultCanvasLine()
{}
