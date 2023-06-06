//
// Semantic DB 4
// Created 2023/6/6
// Updated 2023/6/6
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../SDB_GUI.h"

// wxImage::AddHandler(new wxPNGHandler);

class ImageFrame : public wxFrame
{
public:
	ImageFrame(const wxString& title, const wxString& image_path);

	~ImageFrame();
};

