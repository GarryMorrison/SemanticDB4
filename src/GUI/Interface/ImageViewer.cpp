// Code from here:
// https://forums.wxwidgets.org/viewtopic.php?p=213598&sid=095afd46907454baec14abce0f8cd1b1#p213598
// Author: doublemax
// Added to SDB4: 2023/6/7

#include "ImageViewer.h"


cImageViewer::cImageViewer(wxWindow* parent, wxString title) : wxFrame(parent, wxID_ANY, title)
{
    m_scaleToFit = false;
    m_panInProgress = false;
    m_FirstPaint = true;

    // m_RawBitmap = wxBitmap("d:\\_big.jpg", wxBITMAP_TYPE_ANY);
    m_RawBitmap = wxBitmap("6000_4000.jpg", wxBITMAP_TYPE_ANY);

    Bind(wxEVT_PAINT, &cImageViewer::OnPaint, this);
    Bind(wxEVT_MOUSEWHEEL, &cImageViewer::OnMouseWheel, this);
    Bind(wxEVT_LEFT_DOWN, &cImageViewer::OnLeftDown, this);
    Bind(wxEVT_LEFT_DCLICK, &cImageViewer::OnLeftDClick, this);
    Bind(wxEVT_SIZE, &cImageViewer::OnSize, this);

    SetBackgroundStyle(wxBG_STYLE_PAINT);

    m_ZoomFactor = 1.0f;

    m_panVector = wxPoint2DDouble(0, 0);
    m_inProgressPanStartPoint = wxPoint(0, 0);
    m_inProgressPanVector = wxPoint2DDouble(0, 0);
    m_panInProgress = false;

    m_BitmapWidth = m_RawBitmap.GetWidth();
    m_BitmapHeight = m_RawBitmap.GetHeight();

    // Maximize();
    // m_scaleToFit = true;
    // ScaleToFit();
}

void cImageViewer::ScaleToFit()
{
    const wxSize& s = GetClientSize();

    const double win_aspect = (double)s.x / s.y;
    const double img_aspect = (double)m_BitmapWidth / m_BitmapHeight;

    // if the window is wider than the image, the height determines the scale factor
    if (win_aspect > img_aspect) {
        m_ZoomFactor = (double)s.y / m_BitmapHeight;
    }
    else {
        m_ZoomFactor = (double)s.x / m_BitmapWidth;
    }

    const double scaledImageWidth = (double)m_BitmapWidth * m_ZoomFactor;
    m_Start_X_Pos = ((s.x) - (scaledImageWidth)) / 2;
    m_Start_X_Pos /= m_ZoomFactor;

    const double scaledImageHeight = (double)m_BitmapHeight * m_ZoomFactor;
    m_Start_Y_Pos = ((s.y) - (scaledImageHeight)) / 2;
    m_Start_Y_Pos /= m_ZoomFactor;

    Refresh();
}

void cImageViewer::DoDrawCanvas(wxGraphicsContext* gc)
{
    gc->DrawBitmap(m_DrawBitmap, m_Start_X_Pos, m_Start_Y_Pos, m_BitmapWidth, m_BitmapHeight);

    SetTitle(wxString::Format("x: %.2f, y: %.2f", m_Start_X_Pos, m_Start_Y_Pos));
}


void cImageViewer::OnSize(wxSizeEvent& event)
{
    if (m_scaleToFit) ScaleToFit();

    event.Skip();
}

void cImageViewer::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    // direct2d renderer
    wxGraphicsRenderer* d2dr = wxGraphicsRenderer::GetDirect2DRenderer();
    wxGraphicsContext* gc = d2dr->CreateContext(dc);

    // wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        wxPoint2DDouble totalPan = m_panVector + m_inProgressPanVector;

        gc->Translate(-totalPan.m_x, -totalPan.m_y);
        gc->Scale(m_ZoomFactor, m_ZoomFactor);

        if (m_FirstPaint)
        {
            m_DrawBitmap = gc->CreateBitmap(m_RawBitmap);
            m_FirstPaint = false;
        }

        DoDrawCanvas(gc);
        delete gc;
    }
}

void cImageViewer::OnMouseWheel(wxMouseEvent& event)
{
    if (m_panInProgress)
    {
        FinishPan(false);
    }

    int rot = event.GetWheelRotation();
    int delta = event.GetWheelDelta();

    double oldZoom = m_ZoomFactor;
    m_ZoomFactor += 0.1 * (rot / delta);

    if (m_ZoomFactor < 0.1)
    {
        m_ZoomFactor = 0.1;
    }

    if (m_ZoomFactor > 32.0)
    {
        m_ZoomFactor = 32;
    }

    double a = oldZoom;
    double b = m_ZoomFactor;

    // Set the panVector so that the point below the cursor in the new
    // scaled/panned cooresponds to the same point that is currently below it.
    wxPoint2DDouble uvPoint = event.GetPosition();
    wxPoint2DDouble stPoint = uvPoint + m_panVector;
    wxPoint2DDouble xypoint = stPoint / a;
    wxPoint2DDouble newSTPoint = b * xypoint;
    m_panVector = newSTPoint - uvPoint;

    Refresh();
}

void cImageViewer::ProcessPan(const wxPoint& pt, bool refresh)
{
    m_inProgressPanVector = m_inProgressPanStartPoint - pt;

    if (refresh)
    {
        Refresh();
    }
}

void cImageViewer::FinishPan(bool refresh)
{
    if (m_panInProgress)
    {
        SetCursor(wxNullCursor);

        if (HasCapture())
        {
            ReleaseMouse();
        }

        Unbind(wxEVT_LEFT_UP, &cImageViewer::OnLeftUp, this);
        Unbind(wxEVT_MOTION, &cImageViewer::OnMotion, this);
        Unbind(wxEVT_MOUSE_CAPTURE_LOST, &cImageViewer::OnCaptureLost, this);

        m_panVector += m_inProgressPanVector;
        m_inProgressPanVector = wxPoint2DDouble(0, 0);
        m_panInProgress = false;

        if (refresh)
        {
            Refresh();
        }
    }
}

wxRect2DDouble cImageViewer::GetUntransformedRect() const
{
    double a = m_ZoomFactor / 100.0;

    wxSize sz = GetSize();
    wxPoint2DDouble zero = m_panVector / a;

    return wxRect2DDouble(zero.m_x, zero.m_y, sz.GetWidth() / a, sz.GetHeight() / a);
}

void cImageViewer::OnLeftDClick(wxMouseEvent& event)
{
    m_scaleToFit = !m_scaleToFit;
    if (m_scaleToFit)
        ScaleToFit();
    // event.Skip();
}

void cImageViewer::OnLeftDown(wxMouseEvent& event)
{
    wxCursor cursor(wxCURSOR_HAND);
    SetCursor(cursor);

    m_inProgressPanStartPoint = event.GetPosition();
    m_inProgressPanVector = wxPoint2DDouble(0, 0);
    m_panInProgress = true;

    Bind(wxEVT_LEFT_UP, &cImageViewer::OnLeftUp, this);
    Bind(wxEVT_MOTION, &cImageViewer::OnMotion, this);
    Bind(wxEVT_MOUSE_CAPTURE_LOST, &cImageViewer::OnCaptureLost, this);

    CaptureMouse();
}

void cImageViewer::OnMotion(wxMouseEvent& event)
{
    ProcessPan(event.GetPosition(), true);
}

void cImageViewer::OnLeftUp(wxMouseEvent& event)
{
    ProcessPan(event.GetPosition(), false);
    FinishPan(true);
}

void cImageViewer::OnCaptureLost(wxMouseCaptureLostEvent&)
{
    FinishPan(true);
}

