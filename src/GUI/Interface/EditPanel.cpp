//
// Semantic DB 4
// Created 2022/1/8
// Updated 2022/1/8
// Author Garry Morrison
// License GPL v3
//

#include "EditPanel.h"
extern SDB::Driver driver;

EditPanel::EditPanel(wxPanel* parent, wxWindowID id)
	: wxPanel(parent, id, wxDefaultPosition, wxSize(400, 300), 0)
{
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

	wxButton* run_button = new wxButton(this, ID_Edit_Run, "Run");
	wxButton* dump_button = new wxButton(this, ID_Edit_Dump, "Dump");
	hbox->AddSpacer(10);
	hbox->Add(run_button);
	hbox->AddSpacer(10);
	hbox->Add(dump_button);

	vbox->AddSpacer(5);
	// vbox->Add(run_button, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	vbox->Add(hbox);
	vbox->AddSpacer(5);

	m_aui_notebook = new wxAuiNotebook(this, wxID_ANY);
	
	// Sample content:
	// m_text_ctrl = new wxTextCtrl(m_aui_notebook, wxID_ANY, "Enter your code here ... \n");
	m_text_ctrl = new wxTextCtrl(m_aui_notebook, wxID_ANY, "|context> => |Hello world>\n\nprint |Hello world!>\n", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	// m_text_ctrl = new wxTextCtrl(m_aui_notebook, wxID_ANY, "|context> => |Hello world>\n\nprint |Hello world!>\n");
	m_aui_notebook->AddPage(m_text_ctrl, "hello-world.sw4", true);

	vbox->Add(m_aui_notebook, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);
	vbox->AddSpacer(10);
	SetSizerAndFit(vbox);
	// Layout();

	run_button->Bind(wxEVT_BUTTON, &EditPanel::OnRunButtonDown, this);
	dump_button->Bind(wxEVT_BUTTON, &EditPanel::OnDumpButtonDown, this);
}

void EditPanel::OnRunButtonDown(wxCommandEvent& event)  // Add a timer too??
{
	wxWindow* current_page = m_aui_notebook->GetCurrentPage();
	wxTextCtrl* current_text_ctrl = (wxTextCtrl*)current_page;
	std::string current_text = current_text_ctrl->GetValue().ToStdString();
	// wxMessageBox("Current text:\n" + current_text);
	Timer_ms the_timer;
	std::stringstream buffer;
	std::streambuf* old_buffer = std::cout.rdbuf(buffer.rdbuf());
	driver.result.clear();
	bool parse_success = driver.parse_string(current_text + "\n");
	std::string captured_text = buffer.str();
	std::cout.rdbuf(old_buffer);
	// wxMessageBox("Captured text:\n" + captured_text);
	if (!parse_success)
	{
		wxMessageBox("Parse failed!");
		return;
	}
	std::string result_string = driver.result.to_string();
	OutputFrame* output_frame = new OutputFrame(this, "Output Window", captured_text, result_string);
	the_timer.Stop();
	long long run_time = the_timer.GetTime();
	output_frame->SetRunTime(run_time);
}

void EditPanel::OnDumpButtonDown(wxCommandEvent& event)
{
	std::stringstream buffer;
	context.print_universe(true, buffer);
	std::string captured_text = buffer.str();
	wxString title = wxString::Format("Dump of the current context \"%s\"", driver.context.get_context_name());
	DumpFrame* dump_frame = new DumpFrame(this, title, captured_text);
}

void EditPanel::AddPage(wxWindow* page, const wxString& caption, bool select)
{
	m_aui_notebook->AddPage(page, caption, select);
}

EditPanel::~EditPanel()
{}