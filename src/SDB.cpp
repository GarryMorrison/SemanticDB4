//
// Semantic DB 4
// Created 2021/12/5
// Updated 2021/12/28
// Author Garry Morrison
// License GPL v3
//

#include "SDB.h"

// Start up global ket_map:
KetMap ket_map;

// Start up global fn_map:
FunctionOperatorMap fn_map;

// Start up global usage_map:
OperatorUsageMap operator_usage_map;

// Set default decimal places:
unsigned int default_decimal_places = 5;

// Start up global context:
ContextList context("Global context");

// Start up global parser driver:
SDB::Driver driver(context);

wxIMPLEMENT_APP(SDBApp);
bool SDBApp::OnInit()
{                                           // Need a line to populate fn_map too, from maps to sets for operator names and types.
    fn_map.PopulateOperatorSets();
    operator_usage_map.PopulateUsageMap();  // Need to add a line to this constructor to enable images in wxAutoBufferedPaintDC.
    PrimaryFrame* frame = new PrimaryFrame();
    frame->Show(true);
    return true;
}








