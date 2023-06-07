//
// Semantic DB 4
// Created 2021/12/28
// Updated 2021/12/28
// Author Garry Morrison
// License GPL v3
//

#include "AppAbout.h"

AppAbout::AppAbout(wxWindow* parent, long style)
    : wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
    // sets the application title   // For now everything is hard coded in. Do we want to change that? Probably not at this point.
    SetTitle(_("About ..."));

    // about info
    wxGridSizer* aboutinfo = new wxGridSizer(2, 0, 2);
    aboutinfo->Add(new wxStaticText(this, wxID_ANY, _("Written by: ")),
        0, wxALIGN_LEFT);
    aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_MAINTAINER),
        1, wxEXPAND | wxALIGN_LEFT);

    aboutinfo->Add(new wxStaticText(this, wxID_ANY, _("Last updated: ")),
        0, wxALIGN_LEFT);
    aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_BUILD_DATE),
        1, wxEXPAND | wxALIGN_LEFT);

    aboutinfo->Add(new wxStaticText(this, wxID_ANY, _("Version: ")),
        0, wxALIGN_LEFT);
    aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_VERSION),
        1, wxEXPAND | wxALIGN_LEFT);
    aboutinfo->Add(new wxStaticText(this, wxID_ANY, _("Licence type: ")),
        0, wxALIGN_LEFT);
    aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_LICENCE),
        1, wxEXPAND | wxALIGN_LEFT);
    aboutinfo->Add(new wxStaticText(this, wxID_ANY, _("Copyright: ")),
        0, wxALIGN_LEFT);
    aboutinfo->Add(new wxStaticText(this, wxID_ANY, APP_COPYRIGHT),
        1, wxEXPAND | wxALIGN_LEFT);

    // about icontitle//info
    wxBoxSizer* aboutpane = new wxBoxSizer(wxHORIZONTAL);
    // wxBitmap bitmap = wxBitmap(wxICON(sample));  // Modify the Bitmap/Icon later.
    // aboutpane->Add(new wxStaticBitmap(this, wxID_ANY, bitmap),
    //     0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 20);
    aboutpane->Add(60, 0);
    aboutpane->Add(aboutinfo, 1, wxALIGN_CENTER);
    aboutpane->Add(60, 0);

    // about complete
    wxBoxSizer* totalpane = new wxBoxSizer(wxVERTICAL);
    totalpane->Add(0, 20);
    wxStaticText* appname = new wxStaticText(this, wxID_ANY, APP_NAME);
    appname->SetFont(wxFontInfo(24).Bold());
    totalpane->Add(appname, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 40);
    totalpane->Add(0, 10);
    totalpane->Add(aboutpane, 0, wxEXPAND | wxALL, 4);
    totalpane->Add(new wxStaticText(this, wxID_ANY, APP_DESCR),
        0, wxALIGN_CENTER | wxALL, 10);
    wxButton* okButton = new wxButton(this, wxID_OK, _("OK"));
    okButton->SetDefault();
    totalpane->Add(okButton, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    SetSizerAndFit(totalpane);

    CenterOnScreen();
    ShowModal();
}

AppAbout::~AppAbout()
{}
