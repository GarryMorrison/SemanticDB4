//
// Semantic DB 4
// Created 2023/6/6
// Updated 2023/6/6
// Author Garry Morrison
// License GPL v3
//


#include "ImageFrame.h"

ImageFrame::ImageFrame(const wxString& title, const wxString& image_path) : wxFrame(NULL, wxID_ANY, title)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	// Load the png image:
	wxImage image(image_path);
	if (!image.IsOk())
	{
		wxMessageBox("Image could not be loaded: " + image_path);  // FIXME: For some reason, when this fails SDB.exe doesn't exit from task manager!
		return;
	}

	// Create a static bitmap:
	wxStaticBitmap* bitmap = new wxStaticBitmap(this, wxID_ANY, wxBitmap(image));

	// Add bitmap to the sizer:
	sizer->Add(bitmap, 0, wxALIGN_CENTER | wxALL, 10);
	SetSizer(sizer);
	sizer->Fit(this);
	Show();
}

ImageFrame::~ImageFrame()
{}
