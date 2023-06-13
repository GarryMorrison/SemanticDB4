//
// Semantic DB 4
// Created 2021/12/28
// Updated 2023/6/13
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../SDB_GUI.h"
#include <memory>


#define RC_STRING_CLASS 1
#define RC_NEW_LINE_CLASS 2
#define RC_LINE_CLASS 3
#define RC_COUT 4  // Implement later
#define RC_IMAGE 5 // Implement later

#define RC_OBJECT_NONE 0
#define RC_OBJECT_KET 1
#define RC_OBJECT_SIMPLE_OP 2
#define RC_OBJECT_COMPOUND_OP 3
#define RC_OBJECT_FUNCTION_OP 4

class ResultCanvas;

class ResultCanvasObject
{
public:
    virtual const int Type() const = 0;
    virtual const void Draw(wxAutoBufferedPaintDC& pdc) const = 0;
    virtual const void OnMouseLeftClick() const = 0;
    virtual const bool IsActivated() const = 0;
    virtual const wxString GetText() const = 0;
    virtual const int GetObjectType() const = 0;

private:
};

class ResultCanvasString : public ResultCanvasObject
{
public:
    ResultCanvasString(ResultCanvas* parent, const wxString& wxs, bool isactive, int object_type, bool ismonospace, const wxRect& rect);
    ~ResultCanvasString();
    const int Type() const { return RC_STRING_CLASS; }
    const void Draw(wxAutoBufferedPaintDC& pdc) const;
    const void OnMouseLeftClick() const;
    const bool IsActivated() const;
    const wxString GetText() const;
    const int GetObjectType() const;

private:
    ResultCanvas* m_parent;
    wxString m_text;
    bool m_isactive;
    bool m_ismonospace;
    int m_object_type;
    wxRect m_rect;
};

class ResultCanvasNewLine : public ResultCanvasObject
{
public:
    ResultCanvasNewLine();
    ~ResultCanvasNewLine();

    const int Type() const { return RC_NEW_LINE_CLASS; }
    const void Draw(wxAutoBufferedPaintDC& pdc) const { return; }
    const void OnMouseLeftClick() const { return; };
    const bool IsActivated() const { return false; }
    const wxString GetText() const { return "\n"; }
    const int GetObjectType() const { return RC_OBJECT_NONE; }

private:
};


class ResultCanvasLine : public ResultCanvasObject
{
public:
    ResultCanvasLine(ResultCanvas* parent, int line);
    ~ResultCanvasLine();

    const int Type() const { return RC_LINE_CLASS; }
    const void Draw(wxAutoBufferedPaintDC& pdc) const;
    const void OnMouseLeftClick() const { return; };
    const bool IsActivated() const { return false;  }
    const wxString GetText() const { return wxEmptyString; }  // Maybe it should be "\n" instead of wxEmptyString?
    const int GetObjectType() const { return RC_OBJECT_NONE; }
    
private:
    ResultCanvas* m_parent;
    int m_line;
};




class ResultCanvas : public wxScrolledWindow
{
public:
    ResultCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL);

    void OnPaint(wxPaintEvent& e);
    void OnEraseBg(wxEraseEvent& WXUNUSED(e)) {};
    void OnScroll(wxScrollWinEvent& scroll_event);
    void OnMouseWheel(wxMouseEvent& event);

    // void Draw(wxPaintDC& pdc);
    // void Draw(wxBufferedPaintDC& pdc);
    void Draw(wxAutoBufferedPaintDC& pdc);

    void ClearCanvas();

    void AppendText(const wxString& wxs, bool isactive = false, int object_type = RC_OBJECT_NONE, bool ismonospace = false);
    void AppendMultiLineText(const wxString& wxs, bool isactive = false, int object_type = RC_OBJECT_NONE, bool ismonospace = false);
    void AppendNewLine();
    void AppendLine();
    void AppendActiveText(const wxString& wxs, const wxString& prefix = wxEmptyString, const bool is_mono = false);

    const wxString GetText() const;

    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnMouseLeftClick(wxMouseEvent& event);
    void SetMousePosition(const wxPoint& pt);
    bool ShiftDown();

    wxFont GetMonoFont();
    wxFont GetStartingFont();
    wxPoint GetMousePos();
    std::vector<wxPoint> GetMousePositions();
    wxPoint GetPositionDelta();
    void SetPositionDelta(const wxPoint& pt);
    void IncreasePositionDelta(const wxPoint& pt);

    ~ResultCanvas();
private:
    // wxString m_some_text;
    int m_x = 10;
    int m_y = 10;
    int m_last_y = 10;
    int m_max_x = 10;

    std::vector<std::shared_ptr<ResultCanvasObject> > m_canvas_objects;

    wxPoint m_mouse_pos;
    int m_scroll_delta = 0;
    int m_scroll_scale_x = 20;
    int m_scroll_scale_y = 20;
    int m_mouse_scroll_total = 0;
    std::vector<wxPoint> m_mouse_positions;
    bool m_is_shift_down = false;

    wxFont m_starting_font;
    wxFont m_mono_font;

    wxPoint m_usage_frame_position_delta = wxPoint(0, 0); // Rename to just m_position_delta?
};



