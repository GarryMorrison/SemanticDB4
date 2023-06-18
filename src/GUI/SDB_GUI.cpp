//
// Semantic DB 4
// Created 2021/12/5
// Updated 2023/5/31
// Author Garry Morrison
// License GPL v3
//

#include "SDB_GUI.h"
#include "OperatorLibrary/PopulateGUIOperators.h"

// Start up global ket_map:
KetMap ket_map;

// Start up global fn_map:
FunctionOperatorMap fn_map;

// Start up global usage_map:
OperatorUsageMap operator_usage_map;

// Start up global colour map:
LexerColorMap lexer_color_map;

// Set default decimal places:
unsigned int default_decimal_places = 5;

// Start up global context:
ContextList context("Global context");

// Set up a location for parse results:
Sequence result;

// Start up global parser driver:
SDB::Driver driver(context, result);

wxIMPLEMENT_APP(SDBApp);
bool SDBApp::OnInit()
{  
    ::wxInitAllImageHandlers();  // This fixes the unknown image format bug in ImageFrame!

    PopulateGUIOperators(fn_map);           // Load GUI operators into our fn_map.
    fn_map.PopulateOperatorSets();          // Need a line to populate fn_map too, from maps to sets for operator names and types.
    operator_usage_map.PopulateUsageMap();  // Need to add a line to this constructor to enable images in wxAutoBufferedPaintDC.
    lexer_color_map.LoadDefaults();         // Load our default lexer object colours.
    PrimaryFrame* frame = new PrimaryFrame();
    frame->Show(true);
    return true;
}

int SDBApp::OnExit()
{
    return wxApp::OnExit();
}







