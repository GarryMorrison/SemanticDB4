//
// Semantic DB 4
// Created 2023/5/20
// Updated 2023/5/20
// Author Garry Morrison
// License GPL v3
//

#define _CRT_SECURE_NO_WARNINGS  // We need this for the wxwidgets code to compile! Is there a security risk?
#include "GUIOperatorLibrary.h"
#include <wx/msgdlg.h>

Ket op_gmessage(const Ket& k)  // Our first, test, GUI operator!
{
	wxMessageBox(k.label());
	return k;
}

