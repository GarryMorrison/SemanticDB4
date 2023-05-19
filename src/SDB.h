#pragma once
//
// Semantic DB 4
// Created 2021/12/5
// Updated 2023/5/20
// Author Garry Morrison
// License GPL v3
//

//============================================================================
// declarations
//============================================================================

#define APP_NAME "Semantic DB 4"
#define APP_DESCR "See http://semantic-db.org"

#define APP_MAINTAINER "Garry Morrison"
#define APP_VENDOR "SDB"
#define APP_COPYRIGHT "(C) 2021 Garry Morrison"
#define APP_LICENCE "GPL v3"

#define APP_BUILD_DATE "2023/5/20"
#define APP_VERSION "4.0.alpha4"
#define APP_USAGE_WEBSITE "http://semantic-db.org/docs/usage4/"
#define APP_WEBSITE "http://semantic-db.org"

#define DEFAULT_STATUS_BAR_TEXT "Welcome to the Semantic DB GUI"

#define AGENT_PROMPT "sa: "
#define KET_MAP_DISPLAY_MAX_ROWS 400  // Max number of rows to display in the ket map window.

#define EXAMPLE_STARTING_TEXT "|context> => |Fred Sam sample>\nage |Fred> => |37>\nfriends |Fred> => |Rob> + |Mary> + |Matt> + |Sam>\n\nage |Sam> => |41>\nfriends |Sam> => |Fred> + |Liz> + |Emma>\n\nspelling |*> #=> ssplit |_self>\nhow-many-friends |*> #=> how-many friends |_self>\ntable[name, age, friends, how-many-friends, spelling] rel-kets[friends]\n"
#define EXAMPLE_KET_KNOWLEDGE "age |Fred> => |37>\nfriends |Fred> => |Rob> + |Mary> + |Matt> + |Sam>\nspelling |Fred> => |F> . |r> . |e> . |d>"
#define EXAMPLE_OP_KNOWLEDGE "age |Fred> => |37>\nage |Sam> => |41>"
#define EDIT_STARTING_TEXT "|context> => |Hello world>\n\nprint |Hello world!>\n"

#define SW_EXPERIMENT_EXTENSION ".swe"

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/aboutdlg.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/versioninfo.h>
#include <wx/stc/stc.h>
#include <wx/aui/aui.h>
#include <wx/utils.h>
#include <wx/sizer.h>
#include <wx/listbox.h>
#include <wx/listctrl.h>
#include <wx/hyperlink.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/font.h>
#include <wx/scrolwin.h>
#include <wx/gdicmn.h>
#include <wx/grid.h>
#include <wx/spinctrl.h>
#include <wx/clipbrd.h>
#include <wx/url.h>
#include <wx/sstream.h>
#include <wx/filename.h>
#include <set>
#include <map>
#include <string>
#include <vector>

#include <iostream>
#include <streambuf>
#include <sstream>
#include <filesystem>

#include "Function/SplitJoin.h"
#include "KetMap/KetMap.h"
#include "FunctionOperatorMap/FunctionOperatorMap.h"
#include "OperatorUsageMap/OperatorUsageMap.h"
// #include "src/Function/CoutRedirect.h"
#include "Function/Timer.h"

#include "GUI/Interface/PrimaryFrame.h"
#include "GUI/Interface/AppAbout.h"
#include "GUI/Interface/UsageFrame.h"
#include "GUI/Interface/DumpFrame.h"
#include "GUI/Interface/LinkedTextCtrl.h"
#include "GUI/Interface/KetMapDialog.h"
#include "GUI/Interface/SortedListCtrl.h"
#include "GUI/Interface/SelectFromListDialog.h"
#include "GUI/Interface/ResultCanvas.h"
#include "GUI/Interface/CommandPanel.h"
#include "GUI/Interface/FilteredDumpFrame.h"
#include "GUI/Interface/GeneralOperatorsFrame.h"
#include "GUI/Interface/ResetContextDialog.h"
#include "GUI/Interface/SelectFromKetDialog.h"
#include "GUI/Interface/SelectFromLiteralOpDialog.h"
#include "GUI/Interface/EditPanel.h"
#include "GUI/Interface/OutputFrame.h"
#include "GUI/Interface/CreateNewFileDialog.h"
#include "GUI/OperatorLibrary/ActiveTableDialog.h"
#include "GUI/OperatorLibrary/TableDialog.h"
#include "GUI/OperatorLibrary/IfThenMachineDialog.h"
#include "GUI/OperatorLibrary/IfThenOperatorDialog.h"
#include "GUI/OperatorLibrary/SearchForOperatorDialog.h"
#include "GUI/OperatorLibrary/SearchResultsDialog.h"
#include "GUI/OperatorLibrary/GenerateDocsDialog.h"
#include "GUI/OperatorLibrary/GenerateDocs.h"
#include "GUI/OperatorLibrary/GenerateDocs2.h"


// Back end includes:
#include "KetMap/KetMap.h"
#include "Sequence/Ket.h"
#include "Sequence/Superposition.h"
#include "Sequence/Sequence.h"
#include "Context/Frame.h"
#include "Context/NewContext.h"
#include "Context/ContextList.h"
#include "Operator/SimpleOperator.h"
#include "Operator/NumericOperator.h"
#include "Operator/PoweredOperator.h"
#include "Operator/OperatorSequence.h"
#include "OperatorLibrary/SigmoidLibrary.h"
#include "FunctionOperatorMap/FunctionOperatorMap.h"
#include "Operator/BracketOperator.h"
#include "CompoundConstant/ConstantInteger.h"
#include "CompoundConstant/ConstantFloat.h"
#include "CompoundConstant/ConstantOperator.h"
#include "CompoundConstant/ConstantString.h"
#include "Operator/CompoundOperator.h"
#include "Sequence/OperatorWithSequence.h"
#include "Sequence/SelfKet.h"
#include "Operator/EmptyOperator.h"
#include "OperatorLibrary/OperatorLibrary.h"
#include "OperatorLibrary/FunctionOperatorLibrary.h"
#include "Function/misc.h"
#include "Function/Timer.h"
#include "Operator/FunctionOperator.h"
#include "Sequence/LearnRule.h"
#include "Sequence/MultiLearnRule.h"
#include "Sequence/MultiSelfKet.h"
#include "Parser/Driver.h"
#include "OperatorUsageMap/OperatorUsageMap.h"
// #include "DocsGenerator/DocsGenerator.h"
#include "Sequence/IfElseStatement.h"
#include "Sequence/ForStatement.h"
#include "Sequence/WhileStatement.h"
#include "OperatorLibrary/TMOperatorLibrary.h"
#include "OperatorLibrary/GUIOperatorLibrary.h"


extern ContextList context;
// extern SDB::Driver driver;

wxDECLARE_EVENT(EVT_GRID_CLICK, wxCommandEvent);
wxDECLARE_EVENT(EVT_KET_WINDOW_CLICK, wxCommandEvent);  // Put a space between Ket and Window?
wxDECLARE_EVENT(EVT_LITERALOP_WINDOW_CLICK, wxCommandEvent);
wxDECLARE_EVENT(EVT_INSERT_IFTHEN_MACHINE, wxCommandEvent);
wxDECLARE_EVENT(EVT_INSERT_IFTHEN_OPERATOR, wxCommandEvent);


class SDBApp : public wxApp
{
public:
    virtual bool OnInit();
};



enum
{
    ID_Hello = wxID_HIGHEST + 1,
    ID_New,
    ID_Open,
    ID_Save,
    ID_Insert,

    ID_YES,
    ID_NO,
    // ID_Insert_Known_Kets,
    // ID_Insert_Known_Literal_Operators,

    ID_Insert_Built_In,
    ID_Insert_Built_In_If,
    ID_Insert_Built_In_If_Else,
    ID_Insert_Built_In_For,
    ID_Insert_Built_In_Sfor,
    ID_Insert_Built_In_While,

    ID_Insert_Infix,

    ID_Insert_Infix_1,
    ID_Insert_Infix_1_Plus,
    ID_Insert_Infix_1_Minus,
    ID_Insert_Infix_1_Merge,
    ID_Insert_Infix_1_Smerge,
    ID_Insert_Infix_1_Cmerge,
    ID_Insert_Infix_1_Seq,

    ID_Insert_Infix_2,
    ID_Insert_Infix_2_Equal,
    ID_Insert_Infix_2_Not_Equal,
    ID_Insert_Infix_2_Greater_Equal,
    ID_Insert_Infix_2_Greater,
    ID_Insert_Infix_2_Less_Equal,
    ID_Insert_Infix_2_Less,
    ID_Insert_Infix_2_And,
    ID_Insert_Infix_2_Or,
    ID_Insert_Infix_2_Double_Plus,
    ID_Insert_Infix_2_Double_Minus,
    ID_Insert_Infix_2_Double_Mult,
    ID_Insert_Infix_2_Double_Div,
    ID_Insert_Infix_2_Double_Mod,
    ID_Insert_Infix_2_Double_Pow,
    ID_Insert_Infix_2_Range,

    ID_Insert_Learn_Rule,
    ID_Insert_Learn_Rule_Standard,
    ID_Insert_Learn_Rule_Add,
    ID_Insert_Learn_Rule_Seq,
    ID_Insert_Learn_Rule_Stored,
    ID_Insert_Learn_Rule_Memoize,

    ID_Insert_Misc,
    ID_Insert_Misc_Comment,
    ID_Insert_Misc_Context_Ket,
    ID_Insert_Misc_Context_Learn_Rule,
    ID_Insert_Misc_Empty_Ket,
    ID_Insert_Misc_Star_Ket,
    ID_Insert_Misc_Self_Ket,
    ID_Insert_Misc_Star_Params1,
    ID_Insert_Misc_Star_Params2,
    ID_Insert_Misc_Star_Params3,
    ID_Insert_Misc_Star_Params4,
    ID_Insert_Misc_Multi_Self_Ket,

    ID_Insert_Built_In_Op,
    ID_Insert_Sigmoid_Op,
    ID_Insert_Ket_Op,
    ID_Insert_Superposition_Op,
    ID_Insert_Sequence_Op,
    ID_Insert_Function_Op,
    ID_Usage,
    ID_Window,
    // ID_Window_Known_Kets,
    // ID_Window_Known_Literal_Operators,
    ID_Window_Command,
    ID_Window_Edit,
    ID_Visualize,

    ID_Insert_Window_Known_Kets,
    ID_Insert_Window_Known_Literal_Operators,
    ID_Insert_Window_Learn_Rules,
    ID_Insert_Window_Type1,
    ID_Insert_Window_Type2,
    ID_Insert_Window_Simple,
    ID_Insert_Window_Compound,
    ID_Insert_Window_Function,

    ID_Visualize_Active_Table,
    ID_Table_Usage,
    ID_Table_Generate,
    ID_Table_Run,
    ID_Active_Table_Usage_Suchthat,
    ID_Active_Table_Usage_Filter,
    ID_Active_Table_Usage_Sortby,

    ID_Example_Fibonacci,
    ID_Example_Temperature,
    ID_Example_Bottles,
    ID_Example_Plurals,
    ID_Example_Relations,
    ID_Example_Numbers,
    ID_Example_Monkey,
    ID_Example_Chemistry,
    ID_Example_Ant,
    ID_Example_Sequences,
    ID_Example_More,

    ID_Usage_Search_Operator,
    ID_Search_Operators_Button,
    ID_Launch_Usage_Button,
    ID_Usage_Generate_Docs,

    ID_Help_Ket_Map,
    ID_Help_Usage,
    ID_Help_Website,

    ID_Clear_Select_List,
    ID_Command_Run,
    ID_Command_Run_All,
    ID_Command_Clear,
    ID_Command_Dump,
    ID_Command_Save_As,
    ID_Command_Graph,
    ID_Command_Reset_Context,
    ID_Command_Reset_All,
    ID_Command_Clear_Results,
    ID_Command_Result_Insert_New_Line,
    ID_Command_Result_Insert_Line,
    ID_Command_Left_Click,
    ID_On_Paint,

    ID_Edit_Run,
    ID_Edit_Dump,
    ID_Edit_Reset,

    ID_Copy_All,

    ID_Update_Button,

    ID_Create_File,

    ID_If_Then_Insert,
    ID_If_Then_Insert_Operator,

    ID_Ket_Map_Display_Title_Click,
    ID_Command_Insert_Text
};














