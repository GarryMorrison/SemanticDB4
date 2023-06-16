//
// Semantic DB 4
// Created 2021/12/28
// Updated 2022/1/30
// Author Garry Morrison
// License GPL v3
//

#include "PrimaryFrame.h"


PrimaryFrame::PrimaryFrame()
    : wxFrame(NULL, wxID_ANY, "Semantic DB 4")
{
    // Set up the menu:
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_New, "&New", "Create a new file");
    menuFile->Append(ID_Open, "&Open", "Open a file");
    menuFile->Append(ID_Save, "&Save", "Save a file");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    m_starting_highest_insert_menu_id = ID_Command_Insert_Text + 1;  // A little ugly, and dangerous to hard code this in here!
    m_current_highest_insert_menu_id = m_starting_highest_insert_menu_id;
    wxMenu* menuInsert = new wxMenu;

    wxMenu* menuInsertBuiltIn = new wxMenu;
    m_current_highest_insert_menu_id = PopulateMenu(menuInsertBuiltIn, m_current_highest_insert_menu_id, fn_map.list_of_statements, m_insert_menu_map, "%s statement");
 
    menuInsert->AppendSubMenu(menuInsertBuiltIn, "Built in statements", "Insert built in statement");

    wxMenu* menuInsertInfix = new wxMenu;
    wxMenu* menuInsertInfix1 = new wxMenu;
    m_current_highest_insert_menu_id = PopulateMenu(menuInsertInfix1, m_current_highest_insert_menu_id, fn_map.list_of_infix_type1, m_insert_menu_map, "Infix %s operator");
 
    wxMenu* menuInsertInfix2 = new wxMenu;
    m_current_highest_insert_menu_id = PopulateMenu(menuInsertInfix2, m_current_highest_insert_menu_id, fn_map.list_of_infix_type2, m_insert_menu_map, "Infix %s operator");
    menuInsertInfix->AppendSubMenu(menuInsertInfix1, "Type 1", "Insert infix operator, type 1");
    menuInsertInfix->AppendSubMenu(menuInsertInfix2, "Type 2", "Insert infix operator, type 2");
    // menuInsert->AppendSubMenu(menuInsertInfix, "Infix operator", "Insert infix operator"); // Shifted below menuInsertLearnRule.

    // menuInsert->Append(ID_Insert_Learn_Rule, "Learn rule", "Insert learn rule");
    wxMenu* menuInsertLearnRule = new wxMenu;
    m_current_highest_insert_menu_id = PopulateMenu(menuInsertLearnRule, m_current_highest_insert_menu_id, fn_map.list_of_learn_rules, m_insert_menu_map, "Insert %s learn rule");
    menuInsert->AppendSubMenu(menuInsertLearnRule, "Learn rule", "Insert learn rule");
    menuInsert->AppendSubMenu(menuInsertInfix, "Infix operator", "Insert infix operator");

    // menuInsert->Append(ID_Insert_Misc, "Misc", "Insert miscellanous element");
    wxMenu* menuInsertMisc = new wxMenu;
    m_current_highest_insert_menu_id = PopulateMenu(menuInsertMisc, m_current_highest_insert_menu_id, fn_map.list_of_filtered_misc_elements, m_insert_menu_map, "Insert misc element");
    menuInsert->AppendSubMenu(menuInsertMisc, "Misc", "Insert miscellanous element");
    menuInsert->AppendSeparator();

    // menuInsert->Append(ID_Insert_Built_In_Op, "Built in operator", "Insert built in operator"); // Sub menu, normal vs compound
    // wxMenu* menuInsertBuiltInOp = new wxMenu;
    // m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_built_in, m_usage_menu_map, m_usage_label_menu_map, "Built in operator", "Normal", "Usage for %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsert, m_current_highest_insert_menu_id, fn_map.set_built_in, m_insert_menu_map, m_insert_label_menu_map, "Built in operator", "Normal", "Insert %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsert, m_current_highest_insert_menu_id, fn_map.set_compound_built_in, m_insert_menu_map, m_insert_label_menu_map, "Built in operator", "Compound", "Insert %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsert, m_current_highest_insert_menu_id, fn_map.set_compound_context_built_in, m_insert_menu_map, m_insert_label_menu_map, "Built in operator", "Compound context", "Insert %s operator");


    // menuInsert->Append(ID_Insert_Sigmoid_Op, "Sigmoid operator", "Insert sigmoid operator"); // Sub menu, normal vs compound
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsert, m_current_highest_insert_menu_id, fn_map.set_sigmoids, m_insert_menu_map, m_insert_label_menu_map, "Sigmoid operator", "Normal", "Insert %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsert, m_current_highest_insert_menu_id, fn_map.set_compound_sigmoids, m_insert_menu_map, m_insert_label_menu_map, "Sigmoid operator", "Compound", "Insert %s operator");

    // menuInsert->Append(ID_Insert_Ket_Op, "Ket operator", "Insert ket operator"); // Sub menu, normal vs compound
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsert, m_current_highest_insert_menu_id, fn_map.set_ket_fn, m_insert_menu_map, m_insert_label_menu_map, "Ket operator", "Normal", "Insert %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsert, m_current_highest_insert_menu_id, fn_map.set_compound_ket_fn, m_insert_menu_map, m_insert_label_menu_map, "Ket operator", "Compound", "Insert %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsert, m_current_highest_insert_menu_id, fn_map.set_context_ket_fn, m_insert_menu_map, m_insert_label_menu_map, "Ket operator", "Context", "Insert %s operator");

    // menuInsert->Append(ID_Insert_Superposition_Op, "Superposition operator", "Insert superposition operator"); // Sub menu, normal vs compound
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsert, m_current_highest_insert_menu_id, fn_map.set_sp_fn, m_insert_menu_map, m_insert_label_menu_map, "Superposition operator", "Normal", "Insert %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsert, m_current_highest_insert_menu_id, fn_map.set_compound_sp_fn, m_insert_menu_map, m_insert_label_menu_map, "Superposition operator", "Compound", "Insert %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsert, m_current_highest_insert_menu_id, fn_map.set_compound_context_sp_fn, m_insert_menu_map, m_insert_label_menu_map, "Superposition operator", "Compound context", "Insert %s operator");

    // menuInsert->Append(ID_Insert_Sequence_Op, "Sequence operator", "Insert sequence operator"); // Sub menu, normal vs compound
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsert, m_current_highest_insert_menu_id, fn_map.set_seq_fn, m_insert_menu_map, m_insert_label_menu_map, "Sequence operator", "Normal", "Insert %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsert, m_current_highest_insert_menu_id, fn_map.set_context_seq_fn, m_insert_menu_map, m_insert_label_menu_map, "Sequence operator", "Context", "Insert %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsert, m_current_highest_insert_menu_id, fn_map.set_compound_seq_fn, m_insert_menu_map, m_insert_label_menu_map, "Sequence operator", "Compound", "Insert %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsert, m_current_highest_insert_menu_id, fn_map.set_compound_context_seq_fn, m_insert_menu_map, m_insert_label_menu_map, "Sequence operator", "Compound context", "Insert %s operator");

    // menuInsert->Append(ID_Insert_Function_Op, "Function operator", "Insert function operator"); // Sub menu, 1,2,3,4

    wxMenu* menuInsertFunctionOp = new wxMenu;
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsertFunctionOp, m_current_highest_insert_menu_id, fn_map.set_whitelist_1, m_insert_menu_map, m_insert_label_menu_map, "Normal", "1 param", "Insert %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsertFunctionOp, m_current_highest_insert_menu_id, fn_map.set_whitelist_2, m_insert_menu_map, m_insert_label_menu_map, "Normal", "2 param", "Insert %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsertFunctionOp, m_current_highest_insert_menu_id, fn_map.set_whitelist_3, m_insert_menu_map, m_insert_label_menu_map, "Normal", "3 param", "Insert %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsertFunctionOp, m_current_highest_insert_menu_id, fn_map.set_whitelist_4, m_insert_menu_map, m_insert_label_menu_map, "Normal", "4 param", "Insert %s operator");

    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsertFunctionOp, m_current_highest_insert_menu_id, fn_map.set_context_whitelist_1, m_insert_menu_map, m_insert_label_menu_map, "Context", "1 param", "Insert %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsertFunctionOp, m_current_highest_insert_menu_id, fn_map.set_context_whitelist_2, m_insert_menu_map, m_insert_label_menu_map, "Context", "2 param", "Insert %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsertFunctionOp, m_current_highest_insert_menu_id, fn_map.set_context_whitelist_3, m_insert_menu_map, m_insert_label_menu_map, "Context", "3 param", "Insert %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsertFunctionOp, m_current_highest_insert_menu_id, fn_map.set_context_whitelist_4, m_insert_menu_map, m_insert_label_menu_map, "Context", "4 param", "Insert %s operator");
    menuInsert->AppendSubMenu(menuInsertFunctionOp, "Function operator");

    menuInsert->AppendSeparator();
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsert, m_current_highest_insert_menu_id, fn_map.set_simple_operators, m_insert_menu_map, m_insert_label_menu_map, "General operator", "Simple", "Insert %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsert, m_current_highest_insert_menu_id, fn_map.set_compound_operators, m_insert_menu_map, m_insert_label_menu_map, "General operator", "Compound", "Insert %s operator");
    m_current_highest_insert_menu_id = PopulateSubMenu(menuInsert, m_current_highest_insert_menu_id, fn_map.set_function_operators, m_insert_menu_map, m_insert_label_menu_map, "General operator", "Function", "Insert %s operator");



    // Populate Usage menu:
    m_starting_highest_usage_menu_id = m_current_highest_insert_menu_id + 2;
    m_current_highest_usage_menu_id = m_starting_highest_usage_menu_id;
    wxMenu* menuUsage = new wxMenu;
    wxMenu* menuUsageStatements = new wxMenu;
    m_current_highest_usage_menu_id = PopulateMenu(menuUsageStatements, m_current_highest_usage_menu_id, fn_map.list_of_statements, m_usage_menu_map, "Usage for %s statement");
    menuUsage->AppendSubMenu(menuUsageStatements, "Built in statements", "Usage for built in statements");

    wxMenu* menuUsageLearnRule = new wxMenu;
    m_current_highest_usage_menu_id = PopulateMenu(menuUsageLearnRule, m_current_highest_usage_menu_id, fn_map.list_of_learn_rules, m_usage_menu_map, "Usage for %s learn rule");
    menuUsage->AppendSubMenu(menuUsageLearnRule, "Learn rules", "Usage for learn rules");

    wxMenu* menuUsageInfix1 = new wxMenu;
    m_current_highest_usage_menu_id = PopulateMenu(menuUsageInfix1, m_current_highest_usage_menu_id, fn_map.list_of_infix_type1, m_usage_menu_map, "Usage for %s infix type 1 operator");
    menuUsage->AppendSubMenu(menuUsageInfix1, "Infix type 1", "Usage for infix type 1 operators");

    wxMenu* menuUsageInfix2 = new wxMenu;
    m_current_highest_usage_menu_id = PopulateMenu(menuUsageInfix2, m_current_highest_usage_menu_id, fn_map.list_of_infix_type2, m_usage_menu_map, "Usage for %s infix type 2 operator");
    menuUsage->AppendSubMenu(menuUsageInfix2, "Infix type 2", "Usage for infix type 2 operators");

    wxMenu* menuUsageMisc = new wxMenu;
    m_current_highest_usage_menu_id = PopulateMenu(menuUsageMisc, m_current_highest_usage_menu_id, fn_map.list_of_misc_elements, m_usage_menu_map, "Usage for %s objects");
    menuUsage->AppendSubMenu(menuUsageMisc, "Misc", "Usage for miscellanous objects");

    wxMenu* menuUsageObjects = new wxMenu;
    m_current_highest_usage_menu_id = PopulateMenu(menuUsageObjects, m_current_highest_usage_menu_id, fn_map.list_of_object_types, m_usage_menu_map, "Usage for %s object");
    menuUsage->AppendSubMenu(menuUsageObjects, "Object types", "Usage for object types");

    wxMenu* menuUsageOperatorTypes = new wxMenu;
    m_current_highest_usage_menu_id = PopulateMenu(menuUsageOperatorTypes, m_current_highest_usage_menu_id, fn_map.list_of_operator_types, m_usage_menu_map, "Usage for %s operators");
    menuUsage->AppendSubMenu(menuUsageOperatorTypes, "Operator types", "Usage for operator types");
    menuUsage->AppendSeparator();

    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_built_in, m_usage_menu_map, m_usage_label_menu_map, "Built in operator", "Normal", "Usage for %s operator");
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_compound_built_in, m_usage_menu_map, m_usage_label_menu_map, "Built in operator", "Compound", "Usage for %s operator");
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_compound_context_built_in, m_usage_menu_map, m_usage_label_menu_map, "Built in operator", "Compound context", "Usage for %s operator");

    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_sigmoids, m_usage_menu_map, m_usage_label_menu_map, "Sigmoid operator", "Normal", "Usage for %s operator");
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_compound_sigmoids, m_usage_menu_map, m_usage_label_menu_map, "Sigmoid operator", "Compound", "Usage for %s operator");

    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_ket_fn, m_usage_menu_map, m_usage_label_menu_map, "Ket operator", "Normal", "Usage for %s operator");
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_compound_ket_fn, m_usage_menu_map, m_usage_label_menu_map, "Ket operator", "Compound", "Usage for %s operator");
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_context_ket_fn, m_usage_menu_map, m_usage_label_menu_map, "Ket operator", "Context", "Usage for %s operator");

    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_sp_fn, m_usage_menu_map, m_usage_label_menu_map, "Superposition operator", "Normal", "Usage for %s operator");
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_compound_sp_fn, m_usage_menu_map, m_usage_label_menu_map, "Superposition operator", "Compound", "Usage for %s operator");
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_compound_context_sp_fn, m_usage_menu_map, m_usage_label_menu_map, "Superposition operator", "Compound context", "Usage for %s operator");

    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_seq_fn, m_usage_menu_map, m_usage_label_menu_map, "Sequence operator", "Normal", "Usage for %s operator");
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_context_seq_fn, m_usage_menu_map, m_usage_label_menu_map, "Sequence operator", "Context", "Usage for %s operator");
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_compound_seq_fn, m_usage_menu_map, m_usage_label_menu_map, "Sequence operator", "Compound", "Usage for %s operator");
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_compound_context_seq_fn, m_usage_menu_map, m_usage_label_menu_map, "Sequence operator", "Compound context", "Usage for %s operator");

    wxMenu* menuUsageFunctionOp = new wxMenu;
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsageFunctionOp, m_current_highest_usage_menu_id, fn_map.set_whitelist_1, m_usage_menu_map, m_usage_label_menu_map, "Normal", "1 param", "Usage for %s operator");
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsageFunctionOp, m_current_highest_usage_menu_id, fn_map.set_whitelist_2, m_usage_menu_map, m_usage_label_menu_map, "Normal", "2 param", "Usage for %s operator");
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsageFunctionOp, m_current_highest_usage_menu_id, fn_map.set_whitelist_3, m_usage_menu_map, m_usage_label_menu_map, "Normal", "3 param", "Usage for %s operator");
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsageFunctionOp, m_current_highest_usage_menu_id, fn_map.set_whitelist_4, m_usage_menu_map, m_usage_label_menu_map, "Normal", "4 param", "Usage for %s operator");

    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsageFunctionOp, m_current_highest_usage_menu_id, fn_map.set_context_whitelist_1, m_usage_menu_map, m_usage_label_menu_map, "Context", "1 param", "Usage for %s operator");
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsageFunctionOp, m_current_highest_usage_menu_id, fn_map.set_context_whitelist_2, m_usage_menu_map, m_usage_label_menu_map, "Context", "2 param", "Usage for %s operator");
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsageFunctionOp, m_current_highest_usage_menu_id, fn_map.set_context_whitelist_3, m_usage_menu_map, m_usage_label_menu_map, "Context", "3 param", "Usage for %s operator");
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsageFunctionOp, m_current_highest_usage_menu_id, fn_map.set_context_whitelist_4, m_usage_menu_map, m_usage_label_menu_map, "Context", "4 param", "Usage for %s operator");
    menuUsage->AppendSubMenu(menuUsageFunctionOp, "Function operator");

    menuUsage->AppendSeparator();
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_simple_operators, m_usage_menu_map, m_usage_label_menu_map, "General operator", "Simple", "Usage for %s operator");
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_compound_operators, m_usage_menu_map, m_usage_label_menu_map, "General operator", "Compound", "Usage for %s operator");
    m_current_highest_usage_menu_id = PopulateSubMenu(menuUsage, m_current_highest_usage_menu_id, fn_map.set_function_operators, m_usage_menu_map, m_usage_label_menu_map, "General operator", "Function", "Usage for %s operator");

    menuUsage->AppendSeparator();
    menuUsage->Append(ID_Usage_Search_Operator, "Search Operators ... ", "Search for an operator");
    menuUsage->AppendSeparator();
    menuUsage->Append(ID_Usage_Generate_Docs, "Generate docs ... ", "Generate usage documentation");

    wxMenu* menuInsertWindow = new wxMenu;
    menuInsertWindow->Append(ID_Insert_Window_Learn_Rules, "Learn Rules", "Insert a learn rule");
    menuInsertWindow->Append(ID_Insert_Window_Type1, "Infix type 1", "Insert an infix operator");
    menuInsertWindow->Append(ID_Insert_Window_Type2, "Infix type 2", "Insert an infix operator");
    menuInsertWindow->AppendSeparator();
    menuInsertWindow->Append(ID_Insert_Window_Simple, "Simple operator", "Insert a simple operator");
    menuInsertWindow->Append(ID_Insert_Window_Compound, "Compound operator", "Insert a compound operator");
    menuInsertWindow->Append(ID_Insert_Window_Function, "Function operator", "Insert a function operator");
    menuInsertWindow->AppendSeparator();
    menuInsertWindow->Append(ID_Insert_Window_Known_Kets, "Known kets", "Insert known kets");
    menuInsertWindow->Append(ID_Insert_Window_Known_Literal_Operators, "Known literal operators", "Insert known literal operators");
    // menuInsertWindow->AppendSeparator();

    // wxMenu* menuWindow = new wxMenu;
    m_menuWindow = new wxMenu;
    m_menuWindow->Append(ID_Help_Ket_Map, "Ket Map", "Show ket map");
    m_menuWindow->AppendSeparator();
    m_menuWindow->AppendRadioItem(ID_Window_Command, "Command", "Show the command window");
    m_menuWindow->AppendRadioItem(ID_Window_Edit, "Edit", "Show the edit window");
    

    wxMenu* menuVisualize = new wxMenu;
    menuVisualize->Append(ID_Visualize_Active_Table, "Active Table", "Generate active table");

    wxMenu* menuExamples = new wxMenu;
    menuExamples->Append(ID_Example_Fibonacci, "Fibonacci", "Open Fibonacci example");
    menuExamples->Append(ID_Example_Temperature, "Temperature conversion", "Open temperature conversion example");
    menuExamples->Append(ID_Example_Bottles, "Bottles of beer", "Open bottles of beer example");
    menuExamples->Append(ID_Example_Plurals, "Plurals", "Open plurals example");
    menuExamples->Append(ID_Example_Relations, "Family relations", "Open family relations example");
    menuExamples->Append(ID_Example_Numbers, "Numbers to words", "Open numbers to words example");
    menuExamples->Append(ID_Example_Monkey, "Prolog monkey", "Open prolog monkey example");
    menuExamples->Append(ID_Example_Chemistry, "Simple chemistry", "Open simple chemistry example");
    menuExamples->Append(ID_Example_Ant, "Walking ant", "Open walking ant example");
    menuExamples->Append(ID_Example_Sequences, "Predicting sequences", "Open predicting sequences example");
    menuExamples->AppendSeparator();
    menuExamples->Append(ID_Example_More, "More ... ", "Open more examples");

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(ID_Help_Usage, "Open web usage", "Open web based usage info");
    menuHelp->Append(ID_Help_Website, "Open website", "Open project website");
    menuHelp->AppendSeparator();
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuInsert, "Insert");
    menuBar->Append(menuInsertWindow, "Insert Window");
    menuBar->Append(m_menuWindow, "Window");
    menuBar->Append(menuVisualize, "Visualize");
    menuBar->Append(menuExamples, "Examples");
    menuBar->Append(menuUsage, "Usage");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
    CreateStatusBar(2);
    SetStatusText(DEFAULT_STATUS_BAR_TEXT, 1);

    // Set up the panel:
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // Create the wxAUINotebook widget:
    // wxAuiNotebook* auiNotebook = new wxAuiNotebook(panel, wxID_ANY);
    m_auiNotebook = new wxAuiNotebook(panel, wxID_ANY);
    m_auiNotebook->Hide();


    m_frame_commandPanel = new CommandPanel(panel, wxID_ANY);
    m_frame_commandPanel->InsertText(EXAMPLE_STARTING_TEXT);
    m_frame_commandPanel->Show();
    // m_frame_commandPanel->Hide();

    m_frame_edit_panel = new EditPanel(panel, wxID_ANY);
    m_frame_edit_panel->Hide();
    // m_frame_edit_panel->Show();

    // Add some sample pages:
    // Don't need sample pages for now:
    /*
    wxTextCtrl* textCtrl1 = new wxTextCtrl(m_auiNotebook, wxID_ANY, "Tab 1 Contents");
    m_auiNotebook->AddPage(textCtrl1, "Tab 1");
    wxTextCtrl* textCtrl2 = new wxTextCtrl(m_auiNotebook, wxID_ANY, "Tab 2 Contents");
    m_auiNotebook->AddPage(textCtrl2, "Tab 2");
    */

    // Set up the sizers:
    // Set up the sizer for the panel
    m_panelSizer = new wxBoxSizer(wxHORIZONTAL);
    // panelSizer->Add(m_auiNotebook, 1, wxEXPAND);
    m_panelSizer->Add(m_frame_commandPanel, 1, wxEXPAND);
    // m_panelSizer->Add(new ResultPanel(panel));  // Just testing ResultPanel.
    panel->SetSizer(m_panelSizer);


    // Set up the sizer for the frame and resize the frame
    // according to its contents
    m_topSizer = new wxBoxSizer(wxHORIZONTAL);
    m_topSizer->SetMinSize(650, 600);
    m_topSizer->Add(panel, 1, wxEXPAND);
    SetSizerAndFit(m_topSizer);



    // Bind our events:
    // Bind(wxEVT_MENU, &PrimaryFrame::OnAbout, this, wxID_ABOUT);
    // Bind(wxEVT_MENU, &PrimaryFrame::ShowSimpleAboutDialog, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &PrimaryFrame::ShowPrettyAboutDialog, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &PrimaryFrame::OnNew, this, ID_New);
    Bind(wxEVT_MENU, &PrimaryFrame::OnOpen, this, ID_Open);
    Bind(wxEVT_MENU, &PrimaryFrame::OnSave, this, ID_Save);
    Bind(wxEVT_MENU, &PrimaryFrame::SelectKnownKet, this, ID_Insert_Window_Known_Kets);
    Bind(wxEVT_MENU, &PrimaryFrame::SelectKnownOperator, this, ID_Insert_Window_Known_Literal_Operators);
    Bind(wxEVT_MENU, &PrimaryFrame::SelectFromLearnRules, this, ID_Insert_Window_Learn_Rules);
    Bind(wxEVT_MENU, &PrimaryFrame::SelectFromInfix1, this, ID_Insert_Window_Type1);
    Bind(wxEVT_MENU, &PrimaryFrame::SelectFromInfix2, this, ID_Insert_Window_Type2);
    Bind(wxEVT_MENU, &PrimaryFrame::SelectFromSimple, this, ID_Insert_Window_Simple);
    Bind(wxEVT_MENU, &PrimaryFrame::SelectFromCompound, this, ID_Insert_Window_Compound);
    Bind(wxEVT_MENU, &PrimaryFrame::SelectFromFunction, this, ID_Insert_Window_Function);
    Bind(wxEVT_MENU, &PrimaryFrame::InsertObject, this, m_starting_highest_insert_menu_id, m_current_highest_insert_menu_id);
    Bind(wxEVT_MENU, &PrimaryFrame::UsageForOperator, this, m_starting_highest_usage_menu_id, m_current_highest_usage_menu_id);
    Bind(wxEVT_MENU, &PrimaryFrame::ShowKetMap, this, ID_Help_Ket_Map);  // This ID looks wrong! Fix.
    Bind(wxEVT_MENU, &PrimaryFrame::SwitchWindow, this, ID_Window_Command);
    Bind(wxEVT_MENU, &PrimaryFrame::SwitchWindow, this, ID_Window_Edit);
    Bind(wxEVT_MENU, &PrimaryFrame::InvokeActiveTable, this, ID_Visualize_Active_Table);
    Bind(wxEVT_MENU, &PrimaryFrame::SearchForOperator, this, ID_Usage_Search_Operator);
    Bind(wxEVT_MENU, &PrimaryFrame::GenerateDocs, this, ID_Usage_Generate_Docs);
    Bind(wxEVT_MENU, &PrimaryFrame::OpenExampleWebpage, this, ID_Example_Fibonacci, ID_Example_More);
    Bind(wxEVT_MENU, &PrimaryFrame::OpenWebUsage, this, ID_Help_Usage);
    Bind(wxEVT_MENU, &PrimaryFrame::OpenWebsite, this, ID_Help_Website);
    Bind(wxEVT_MENU, &PrimaryFrame::OnExit, this, wxID_EXIT);

}

// Do we want a version that uses fn_map maps, instead of sets?
int PrimaryFrame::PopulateMenu(wxMenu* menu, int starting_id, std::set<ulong>& our_map, std::map<int, wxString>& menu_map, wxString status_text)
{
    int current_id = starting_id;
    std::set<wxString> sorted_map;
    for (ulong idx : our_map)
    {
        wxString wxs = ket_map.get_str(idx);
        sorted_map.insert(wxs);
    }
    for (wxString wxs : sorted_map)
    {
        if (wxs == "&&")
        {
            menu->Append(current_id, "&&&&", wxString::Format(status_text, wxs));  // Handle special case of && in a menu.
        }
        else
        {
            menu->Append(current_id, wxs, wxString::Format(status_text, wxs));
        }
        menu_map[current_id] = wxs;
        current_id++;
    }
    return current_id;
}

int PrimaryFrame::PopulateSubMenu(wxMenu* parent_menu, int starting_id, std::set<ulong>& our_map, std::map<int, wxString>& menu_map, std::map<wxString, wxMenu*>& label_menu_map, wxString menu_label, wxString sub_menu_label, wxString sub_sub_menu_status_text)
{
    int current_id = starting_id;
    wxMenu* current_menu;
    bool new_menu = true;
    if (label_menu_map.find(menu_label) == label_menu_map.end())
    {
        current_menu = new wxMenu;
        label_menu_map[menu_label] = current_menu;
    }
    else
    {
        current_menu = label_menu_map[menu_label];
        new_menu = false;
    }
    wxMenu* sub_menu = new wxMenu;
    current_id = PopulateMenu(sub_menu, current_id, our_map, menu_map, sub_sub_menu_status_text);
    current_menu->AppendSubMenu(sub_menu, sub_menu_label);
    if (new_menu)
    {
        parent_menu->AppendSubMenu(current_menu, menu_label);
    }
    return current_id;
}

int PrimaryFrame::PopulateMenu(wxMenu* menu, int starting_id, std::vector<std::string>& our_list, std::map<int, wxString>& menu_map, wxString status_text)
{
    int current_id = starting_id;
    for (const auto& s : our_list)
    {
        if (s == "&&")
        {
            menu->Append(current_id, "&&&&", wxString::Format(status_text, s));  // Handle special case of && in a menu.
        }
        else
        {
            menu->Append(current_id, s, wxString::Format(status_text, s));
        }
        menu_map[current_id] = wxString(s);
        current_id++;
    }
    return current_id;
}

int PrimaryFrame::PopulateSubMenu(wxMenu* parent_menu, int starting_id, std::vector<std::string>& our_list, std::map<int, wxString>& menu_map, std::map<wxString, wxMenu*>& label_menu_map, wxString menu_label, wxString sub_menu_label, wxString sub_sub_menu_status_text)
{
    int current_id = starting_id;
    wxMenu* current_menu;
    bool new_menu = true;
    if (label_menu_map.find(menu_label) == label_menu_map.end())
    {
        current_menu = new wxMenu;
        label_menu_map[menu_label] = current_menu;
    }
    else
    {
        current_menu = label_menu_map[menu_label];
        new_menu = false;
    }
    wxMenu* sub_menu = new wxMenu;
    current_id = PopulateMenu(sub_menu, current_id, our_list, menu_map, sub_sub_menu_status_text);
    current_menu->AppendSubMenu(sub_menu, sub_menu_label);
    if (new_menu)
    {
        parent_menu->AppendSubMenu(current_menu, menu_label);
    }
    return current_id;
}

void PrimaryFrame::OnExit(wxCommandEvent& event)
{
    m_frame_edit_panel->DeleteAllPages();
    Close(true);
}
void PrimaryFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",  // Remove later!
        "About Hello World", wxOK | wxICON_INFORMATION);
}


void PrimaryFrame::ShowSimpleAboutDialog(wxCommandEvent& event)
{
    wxAboutDialogInfo info;
    info.SetName("FirstApp");
    info.SetVersion("0.0.1");
    info.SetDescription("This program will be something great!\nBy Garry Morrison");
    info.SetCopyright("(C) 2021");
    info.SetWebSite("http://semantic-db.org");
    // info.AddDeveloper("Garry Morrison");
    wxAboutBox(info);
}

void PrimaryFrame::ShowPrettyAboutDialog(wxCommandEvent& event)
{
    AppAbout* dlg = new AppAbout(this);
}

void PrimaryFrame::OnNew(wxCommandEvent& event)
{
    CreateNewFileDialog* new_file_dialog = new CreateNewFileDialog(this);
    
    wxString file_name = new_file_dialog->GetFilename();
    if (file_name.IsEmpty())
    {
        return;
    }
    wxString starting_code;
    wxString context_name = new_file_dialog->GetContextname();
    if (!context_name.IsEmpty())
    {
        starting_code += "|context> => |" + context_name + ">\n\n";
    }

    // wxTextCtrl* textCtrlLocal;
    LexerTextCtrl* textCtrlLocal;
    if (m_frame_edit_panel->TabLabelExists(file_name))
    {
        if (wxMessageBox(file_name + " has not been saved! Proceed?", "Please confirm", wxICON_QUESTION | wxYES_NO, this) == wxNO)
        {
            return;
        }
        // textCtrlLocal = new wxTextCtrl(m_frame_edit_panel, wxID_ANY, starting_code, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER);
        textCtrlLocal = new LexerTextCtrl(m_frame_edit_panel, wxID_ANY, starting_code, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER);
        m_frame_edit_panel->ModifyPage(textCtrlLocal, file_name, true);
    }
    else
    {
        // textCtrlLocal = new wxTextCtrl(m_frame_edit_panel, wxID_ANY, starting_code, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER);
        textCtrlLocal = new LexerTextCtrl(m_frame_edit_panel, wxID_ANY, starting_code, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER);
        m_frame_edit_panel->AddPage(textCtrlLocal, file_name, true);
        m_open_file_text_ctrl[file_name] = textCtrlLocal;  // Probably a memory leak if we open the same file twice?
    }

    m_command_window_active = false;
    m_edit_window_active = true;
    m_panelSizer->Detach(0); // remove previous panel
    m_frame_commandPanel->Hide();
    m_panelSizer->Prepend(m_frame_edit_panel, 1, wxGROW);
    m_frame_edit_panel->Show();
    m_panelSizer->Layout();
    m_menuWindow->Check(ID_Window_Edit, true);
}

void PrimaryFrame::OnOpen(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, "Open sw file", "", "", "sw file (*.sw;*.swc;*.sw3;*.sw4;*.swe)|*.sw;*.swc;*.sw3;*.sw4;*.swe|Text file (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;
    wxFileInputStream input_stream(openFileDialog.GetPath());
    if (!input_stream.IsOk())
    {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
        return;
    }

    wxString file_content;
    wxTextInputStream text(input_stream, wxT("\x09"), wxConvUTF8);  // Check these settings are correct later.
    while (input_stream.IsOk() && !input_stream.Eof())
    {
        file_content.Append(text.ReadLine());
        file_content.Append("\n");  // There must be a better way to keep newlines in the text!
    }
    
    wxString file_name = openFileDialog.GetFilename();  // Check here if we already know this file name, before creating a new wxTextCtrl.
    // wxTextCtrl* textCtrlLocal; 
    LexerTextCtrl* textCtrlLocal;
    if (m_frame_edit_panel->TabLabelExists(file_name))
    {
        if (wxMessageBox(file_name + " has not been saved! Proceed?", "Please confirm", wxICON_QUESTION | wxYES_NO, this) == wxNO)
        {
            return;
        }
        // textCtrlLocal = new wxTextCtrl(m_frame_edit_panel, wxID_ANY, file_content, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER | wxTE_RICH2);
        textCtrlLocal = new LexerTextCtrl(m_frame_edit_panel, wxID_ANY, file_content, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER | wxTE_RICH2);
        m_frame_edit_panel->ModifyPage(textCtrlLocal, file_name, true);
    }
    else
    {
        // textCtrlLocal = new wxTextCtrl(m_frame_edit_panel, wxID_ANY, file_content, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER | wxTE_RICH2);
        textCtrlLocal = new LexerTextCtrl(m_frame_edit_panel, wxID_ANY, file_content, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER | wxTE_RICH2); m_frame_edit_panel->AddPage(textCtrlLocal, file_name, true);
        m_open_file_text_ctrl[file_name] = textCtrlLocal;  // Probably a memory leak if we open the same file twice?
    }

    m_command_window_active = false;
    m_edit_window_active = true;
    m_panelSizer->Detach(0); // remove previous panel
    m_frame_commandPanel->Hide();
    // m_panelSizer->Prepend(m_auiNotebook, 1, wxGROW);
    // m_auiNotebook->Show();
    m_panelSizer->Prepend(m_frame_edit_panel, 1, wxGROW);
    m_frame_edit_panel->Show();
    m_panelSizer->Layout();
    m_menuWindow->Check(ID_Window_Edit, true);  // Maybe store the full menu, not just the menuWindow menu?
}

void PrimaryFrame::OnSave(wxCommandEvent& event)
{
    wxString default_filename = ".sw4";
    if (m_edit_window_active)
    {
        default_filename = m_frame_edit_panel->GetTabLabel();
    }
    wxFileDialog saveFileDialog(this, "Save sw file", "", default_filename, "sw file (*.sw;*.swc;*.sw3;*.sw4;*.swe)|*.sw;*.swc;*.sw3;*.sw4;*.swe|Text file (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    if (m_command_window_active)
    {
        m_frame_commandPanel->SaveFile(saveFileDialog.GetPath());
    }
    else if (m_edit_window_active)
    {
        m_frame_edit_panel->SaveFile(saveFileDialog.GetPath());
    }
}

void PrimaryFrame::SelectKnownKet(wxCommandEvent& event)
{
    unsigned int d = m_insert_window_open_count;
    SelectFromKetDialog* select_ket_dialog = new SelectFromKetDialog(this, wxPoint(d * 40, d * 40));
    m_insert_window_open_count++;

    select_ket_dialog->Bind(EVT_KET_WINDOW_CLICK, &PrimaryFrame::OnSelectKetDialogItem, this);
}

void PrimaryFrame::OnSelectKetDialogItem(wxCommandEvent& event)
{
    InsertKet(event.GetString());
}


void PrimaryFrame::SelectKnownOperator(wxCommandEvent& event)
{
    unsigned int d = m_insert_window_open_count;
    SelectFromLiteralOpDialog* select_op_dialog = new SelectFromLiteralOpDialog(this, wxPoint(d * 40, d * 40));
    m_insert_window_open_count++;

    select_op_dialog->Bind(EVT_LITERALOP_WINDOW_CLICK, &PrimaryFrame::OnSelectLiteralOpDialogItem, this);
}

void PrimaryFrame::OnSelectLiteralOpDialogItem(wxCommandEvent& event)
{
    InsertSimpleOperator(event.GetString());
}

void PrimaryFrame::SelectFromLearnRules(wxCommandEvent& event)
{
    wxArrayString list_options;
    for (const auto& the_learn_rule : fn_map.list_of_learn_rules)
    {
        list_options.Add(the_learn_rule);
    }
    unsigned int d = m_insert_window_open_count;  // Just an alias.
    SelectFromListDialog* select_dlg = new SelectFromListDialog(this, "Select learn rule", list_options, wxPoint(d * 40, d * 40));
    m_insert_window_open_count++;

    select_dlg->Bind(wxEVT_LISTBOX, [=](wxCommandEvent& event) {
        int the_selection = event.GetSelection();
        if (the_selection == wxNOT_FOUND)
        {
            return;
        }
        wxString the_learn_rule = list_options[the_selection];  // Need to check bounds?
        InsertLearnRule(the_learn_rule);
        select_dlg->DeselectAll();
        });

    select_dlg->Bind(wxEVT_LISTBOX_DCLICK, [=](wxCommandEvent& event) {
        int the_selection = event.GetSelection();
        if (the_selection == wxNOT_FOUND)
        {
            return;
        }
        wxString the_learn_rule = list_options[the_selection];  // Need to check bounds?
        InsertLearnRule(the_learn_rule);
        });
}

void PrimaryFrame::SelectFromInfix1(wxCommandEvent& event)
{
    wxArrayString list_options;
    for (const auto& the_op : fn_map.list_of_infix_type1)
    {
        list_options.Add(the_op);
    }
    unsigned int d = m_insert_window_open_count;  // Just an alias.
    SelectFromListDialog* select_dlg = new SelectFromListDialog(this, "Select infix type 1 operator", list_options, wxPoint(d * 40, d * 40));
    m_insert_window_open_count++;

    select_dlg->Bind(wxEVT_LISTBOX, [=](wxCommandEvent& event) {
        int the_selection = event.GetSelection();
        if (the_selection == wxNOT_FOUND)
        {
            return;
        }
        wxString the_op = list_options[the_selection];  // Need to check bounds?
        InsertInfixOperator(the_op);
        select_dlg->DeselectAll();
        });

    select_dlg->Bind(wxEVT_LISTBOX_DCLICK, [=](wxCommandEvent& event) {
        int the_selection = event.GetSelection();
        if (the_selection == wxNOT_FOUND)
        {
            return;
        }
        wxString the_op = list_options[the_selection];  // Need to check bounds?
        InsertInfixOperator(the_op);
        });
}

void PrimaryFrame::SelectFromInfix2(wxCommandEvent& event)
{
    wxArrayString list_options;
    for (const auto& the_op : fn_map.list_of_infix_type2)
    {
        list_options.Add(the_op);
    }
    unsigned int d = m_insert_window_open_count;  // Just an alias.
    SelectFromListDialog* select_dlg = new SelectFromListDialog(this, "Select infix type 2 operator", list_options, wxPoint(d * 40, d * 40));
    m_insert_window_open_count++;

    select_dlg->Bind(wxEVT_LISTBOX, [=](wxCommandEvent& event) {
        int the_selection = event.GetSelection();
        if (the_selection == wxNOT_FOUND)
        {
            return;
        }
        wxString the_op = list_options[the_selection];  // Need to check bounds?
        InsertInfixOperator(the_op);
        select_dlg->DeselectAll();
        });

    select_dlg->Bind(wxEVT_LISTBOX_DCLICK, [=](wxCommandEvent& event) {
        int the_selection = event.GetSelection();
        if (the_selection == wxNOT_FOUND)
        {
            return;
        }
        wxString the_op = list_options[the_selection];  // Need to check bounds?
        InsertInfixOperator(the_op);
        });
}

void PrimaryFrame::SelectFromSimple(wxCommandEvent& event)
{
    wxArrayString list_options;
    for (const auto& idx : fn_map.set_simple_operators)
    {
        list_options.Add(ket_map.get_str(idx));
    }
    list_options.Sort(false);  // We need to sort them!
    unsigned int d = m_insert_window_open_count;  // Just an alias.
    SelectFromListDialog* select_dlg = new SelectFromListDialog(this, "Select simple operator", list_options, wxPoint(d * 40, d * 40));
    m_insert_window_open_count++;

    select_dlg->Bind(wxEVT_LISTBOX, [=](wxCommandEvent& event) {
        int the_selection = event.GetSelection();
        if (the_selection == wxNOT_FOUND)
        {
            return;
        }
        wxString the_op = list_options[the_selection];  // Need to check bounds?
        InsertSimpleOperator(the_op);
        select_dlg->DeselectAll();
        });

    select_dlg->Bind(wxEVT_LISTBOX_DCLICK, [=](wxCommandEvent& event) {
        int the_selection = event.GetSelection();
        if (the_selection == wxNOT_FOUND)
        {
            return;
        }
        wxString the_op = list_options[the_selection];  // Need to check bounds?
        InsertSimpleOperator(the_op);
        });
}

void PrimaryFrame::SelectFromCompound(wxCommandEvent& event)
{
    wxArrayString list_options;
    for (const auto& idx : fn_map.set_compound_operators)
    {
        list_options.Add(ket_map.get_str(idx));
    }
    list_options.Sort(false);  // We need to sort them!
    unsigned int d = m_insert_window_open_count;  // Just an alias.
    SelectFromListDialog* select_dlg = new SelectFromListDialog(this, "Select compound operator", list_options, wxPoint(d * 40, d * 40));
    m_insert_window_open_count++;

    select_dlg->Bind(wxEVT_LISTBOX, [=](wxCommandEvent& event) {
        int the_selection = event.GetSelection();
        if (the_selection == wxNOT_FOUND)
        {
            return;
        }
        wxString the_op = list_options[the_selection];  // Need to check bounds?
        InsertCompoundOperator(the_op);
        select_dlg->DeselectAll();
        });

    select_dlg->Bind(wxEVT_LISTBOX_DCLICK, [=](wxCommandEvent& event) {
        int the_selection = event.GetSelection();
        if (the_selection == wxNOT_FOUND)
        {
            return;
        }
        wxString the_op = list_options[the_selection];  // Need to check bounds?
        InsertCompoundOperator(the_op);
        });
}

void PrimaryFrame::SelectFromFunction(wxCommandEvent& event)
{
    wxArrayString list_options;
    for (const auto& idx : fn_map.set_function_operators)
    {
        list_options.Add(ket_map.get_str(idx));
    }
    list_options.Sort(false);  // We need to sort them!
    unsigned int d = m_insert_window_open_count;  // Just an alias.
    SelectFromListDialog* select_dlg = new SelectFromListDialog(this, "Select function operator", list_options, wxPoint(d * 40, d * 40));
    m_insert_window_open_count++;

    select_dlg->Bind(wxEVT_LISTBOX, [=](wxCommandEvent& event) {
        int the_selection = event.GetSelection();
        if (the_selection == wxNOT_FOUND)
        {
            return;
        }
        wxString the_op = list_options[the_selection];  // Need to check bounds?
        InsertFunctionOperator(the_op);
        select_dlg->DeselectAll();
        });

    select_dlg->Bind(wxEVT_LISTBOX_DCLICK, [=](wxCommandEvent& event) {
        int the_selection = event.GetSelection();
        if (the_selection == wxNOT_FOUND)
        {
            return;
        }
        wxString the_op = list_options[the_selection];  // Need to check bounds?
        InsertFunctionOperator(the_op);
        });
}


void PrimaryFrame::InsertObject(wxCommandEvent& event)
{
    std::string the_operator = m_insert_menu_map[event.GetId()].ToStdString();
    ulong idx = ket_map.get_idx(the_operator);
    if (fn_map.set_simple_operators.find(idx) != fn_map.set_simple_operators.end())  // Note the precedence. If an operator is simple, and compound, it will be considered simple.
    {
        InsertSimpleOperator(the_operator);
    }
    else if (fn_map.set_compound_operators.find(idx) != fn_map.set_compound_operators.end())  // If an operator is compound and function, it will be considered compound. Maybe make smarter later.
    {
        InsertCompoundOperator(the_operator);
    }
    else if (fn_map.set_function_operators.find(idx) != fn_map.set_function_operators.end())
    {
        InsertFunctionOperator(the_operator);
    }
    else if (std::find(fn_map.list_of_statements.begin(), fn_map.list_of_statements.end(), the_operator) != fn_map.list_of_statements.end())
    {
        InsertStatement(the_operator);
    }
    else if (std::find(fn_map.list_of_learn_rules.begin(), fn_map.list_of_learn_rules.end(), the_operator) != fn_map.list_of_learn_rules.end())
    {
        InsertLearnRule(the_operator);
    }
    else if (std::find(fn_map.list_of_infix_type1.begin(), fn_map.list_of_infix_type1.end(), the_operator) != fn_map.list_of_infix_type1.end())
    {
        InsertInfixOperator(the_operator);
    }
    else if (std::find(fn_map.list_of_infix_type2.begin(), fn_map.list_of_infix_type2.end(), the_operator) != fn_map.list_of_infix_type2.end())
    {
        InsertInfixOperator(the_operator);
    }
    else if (the_operator == "|>" || the_operator == "|*>" || the_operator == "|_self>")
    {
        InsertKet(the_operator);
    }
    else if (the_operator == "comment")
    {
        InsertComment();
    }
    else if (the_operator == "|context>")
    {
        InsertStatement("context");
    }
    else if (the_operator == "if-then machine")
    {
        IfThenMachineDialog* if_then_dialog = new IfThenMachineDialog(this);
        if_then_dialog->Bind(EVT_INSERT_IFTHEN_MACHINE, &PrimaryFrame::OnIfThenInsert, this);
    }
    else if (the_operator == "if-then operator")
    {
        IfThenOperatorDialog* if_then_op_dialog = new IfThenOperatorDialog(this);
        if_then_op_dialog->Bind(EVT_INSERT_IFTHEN_OPERATOR, &PrimaryFrame::OnIfThenInsert, this);
    }
    else
    {
        wxMessageBox(wxString::Format("Special case %s, will handle later.", the_operator));
        InsertText(the_operator);  // Later handle all the special cases.
    }
}

void PrimaryFrame::OnIfThenInsert(wxCommandEvent& event)
{
    InsertText(event.GetString());
}

void PrimaryFrame::UsageForOperator(wxCommandEvent& event)
{
    std::string the_operator = m_usage_menu_map[event.GetId()].ToStdString();
    if (!operator_usage_map.usage_is_defined(the_operator))
    {
        if (operator_usage_map.usage_is_defined(" " + the_operator + " "))  // For symbolic operators, the usage is of form " => ", instead of just "=>".
        {
            the_operator = " " + the_operator + " ";
        }
        else
        {
            wxMessageBox("No usage info available for operator: " + the_operator);
            return;
        }
    }
    UsageFrame* dlg = new UsageFrame(this, the_operator);

}



void PrimaryFrame::ShowKetMap(wxCommandEvent& event)
{
    KetMapDialog* dlg = new KetMapDialog(this);
}

void PrimaryFrame::SwitchWindow(wxCommandEvent& event)
{
    // wxMessageBox("ID: " + std::to_string(event.GetId()));
    if (event.GetId() == ID_Window_Command)
    {
        m_panelSizer->Detach(0); // remove previous panel
        m_auiNotebook->Hide();
        m_frame_edit_panel->Hide();
        m_panelSizer->Prepend(m_frame_commandPanel, 1, wxGROW);
        m_frame_commandPanel->Show();
        m_frame_commandPanel->UpdateContextSelector();
        m_command_window_active = true;
        m_edit_window_active = false;
    }
    if (event.GetId() == ID_Window_Edit)
    {
        m_panelSizer->Detach(0); // remove previous panel
        m_frame_commandPanel->Hide();
        // m_panelSizer->Prepend(m_auiNotebook, 1, wxGROW);
        // m_auiNotebook->Show();
        m_panelSizer->Prepend(m_frame_edit_panel, 1, wxGROW);
        m_frame_edit_panel->Show();
        m_frame_edit_panel->UpdateContextSelector();
        m_command_window_active = false;
        m_edit_window_active = true;
    }
    m_panelSizer->Layout();
}

void PrimaryFrame::InvokeActiveTable(wxCommandEvent& event)
{
    ActiveTableDialog* active_table = new ActiveTableDialog(this);
}

void PrimaryFrame::SearchForOperator(wxCommandEvent& event)
{
    SearchForOperatorDialog* search_for_operator = new SearchForOperatorDialog(this);
}

void PrimaryFrame::GenerateDocs(wxCommandEvent& event)
{
    // wxMessageBox("Place holder for Generate Docs");
    GenerateDocsDialog* generate_usage_docs = new GenerateDocsDialog(this);
}

void PrimaryFrame::OpenExampleWebpage(wxCommandEvent& event)
{
    wxString webpage;
    switch (event.GetId())
    {
    case ID_Example_Fibonacci: {
        webpage = "http://semantic-db.org/example-fibonacci.html";
        break;
    }
    case ID_Example_Temperature: {
        webpage = "http://semantic-db.org/example-temperature-conversion.html";
        break;
    }
    case ID_Example_Bottles: {
        webpage = "http://semantic-db.org/example-bottles-of-beer.html";
        break;
    }
    case ID_Example_Plurals: {
        webpage = "http://semantic-db.org/example-plural.html";
        break;
    }
    case ID_Example_Relations: {
        webpage = "http://semantic-db.org/example-family-relations.html";
        break;
    }
    case ID_Example_Numbers: {
        webpage = "http://semantic-db.org/example-numbers-to-words.html";
        break;
    }
    case ID_Example_Monkey: {
        webpage = "http://semantic-db.org/example-prolog-monkey.html";
        break;
    }
    case ID_Example_Chemistry: {
        webpage = "http://semantic-db.org/example-simple-chemistry.html";
        break;
    }
    case ID_Example_Ant: {
        webpage = "http://semantic-db.org/example-walking-ant.html";
        break;
    }
    case ID_Example_Sequences: {
        webpage = "http://semantic-db.org/example-predicting-sequences.html";
        break;
    }
    case ID_Example_More: {
        webpage = "http://semantic-db.org/examples.html";
        break;
    }
    }
    if (webpage.IsEmpty() || !wxLaunchDefaultBrowser(webpage))
        wxLogError("Failed to open browser.");
}

void PrimaryFrame::OpenWebUsage(wxCommandEvent& event)
{
    if (!wxLaunchDefaultBrowser(APP_USAGE_WEBSITE))
        wxLogError("Failed to open browser.");
}

void PrimaryFrame::OpenWebsite(wxCommandEvent& event)
{
    if (!wxLaunchDefaultBrowser(APP_WEBSITE))
        wxLogError("Failed to open browser.");
}

void PrimaryFrame::InsertText(const wxString& wxs)
{
    if (m_command_window_active)
    {
        m_frame_commandPanel->InsertText(wxs);
    }
    else if (m_edit_window_active)
    {
        m_frame_edit_panel->InsertText(wxs);
    }
}

void PrimaryFrame::InsertStatement(const wxString& wxs)
{
    if (m_command_window_active)
    {
        m_frame_commandPanel->InsertStatement(wxs);
    }
    else if (m_edit_window_active)
    {
        m_frame_edit_panel->InsertStatement(wxs);
    }
}

void PrimaryFrame::InsertLearnRule(const wxString& wxs)
{
    if (m_command_window_active)
    {
        m_frame_commandPanel->InsertLearnRule(wxs);
    }
    else if (m_edit_window_active)
    {
        m_frame_edit_panel->InsertLearnRule(wxs);
    }
}

void PrimaryFrame::InsertInfixOperator(const wxString& wxs)
{
    if (m_command_window_active)
    {
        m_frame_commandPanel->InsertInfixOperator(wxs);
    }
    else if (m_edit_window_active)
    {
        m_frame_edit_panel->InsertInfixOperator(wxs);
    }
}

void PrimaryFrame::InsertSimpleOperator(const wxString& wxs)
{
    if (m_command_window_active)
    {
        m_frame_commandPanel->InsertSimpleOperator(wxs);
    }
    else if (m_edit_window_active)
    {
        m_frame_edit_panel->InsertSimpleOperator(wxs);
    }
}

void PrimaryFrame::InsertCompoundOperator(const wxString& wxs)
{
    if (m_command_window_active)
    {
        m_frame_commandPanel->InsertCompoundOperator(wxs);
    }
    else if (m_edit_window_active)
    {
        m_frame_edit_panel->InsertCompoundOperator(wxs);
    }
}

void PrimaryFrame::InsertFunctionOperator(const wxString& wxs)
{
    if (m_command_window_active)
    {
        m_frame_commandPanel->InsertFunctionOperator(wxs);
    }
    else if (m_edit_window_active)
    {
        m_frame_edit_panel->InsertFunctionOperator(wxs);
    }
}

void PrimaryFrame::InsertKet(const wxString& wxs)
{
    if (m_command_window_active)
    {
        m_frame_commandPanel->InsertKet(wxs);
    }
    else if (m_edit_window_active)
    {
        m_frame_edit_panel->InsertKet(wxs);
    }
}

void PrimaryFrame::InsertComment()
{
    if (m_command_window_active)
    {
        m_frame_commandPanel->InsertComment();
    }
    else if (m_edit_window_active)
    {
        m_frame_edit_panel->InsertComment();
    }
}

PrimaryFrame::~PrimaryFrame()
{}
