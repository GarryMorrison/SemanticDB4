//
// Semantic DB 4
// Created 2022/1/8
// Updated 2022/2/11
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
	wxButton* reset_button = new wxButton(this, ID_Edit_Reset, "Reset");
	hbox->AddSpacer(10);
	hbox->Add(run_button);
	hbox->AddSpacer(10);
	hbox->Add(dump_button);
	hbox->AddSpacer(10);
	hbox->Add(reset_button);

	vbox->AddSpacer(5);
	// vbox->Add(run_button, wxSizerFlags(0).Left().Border(wxLEFT | wxRIGHT, 10));
	vbox->Add(hbox);
	vbox->AddSpacer(5);

	m_aui_notebook = new wxAuiNotebook(this, wxID_ANY);
	
	// Sample content:
	// m_text_ctrl = new wxTextCtrl(m_aui_notebook, wxID_ANY, "Enter your code here ... \n");
	m_text_ctrl = new wxTextCtrl(m_aui_notebook, wxID_ANY, EDIT_STARTING_TEXT, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER);
	// m_text_ctrl = new wxTextCtrl(m_aui_notebook, wxID_ANY, "|context> => |Hello world>\n\nprint |Hello world!>\n");
	m_aui_notebook->AddPage(m_text_ctrl, "hello-world.sw4", true);

	vbox->Add(m_aui_notebook, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);
	vbox->AddSpacer(10);
	SetSizerAndFit(vbox);
	// Layout();

	run_button->Bind(wxEVT_BUTTON, &EditPanel::OnRunButtonDown, this);
	dump_button->Bind(wxEVT_BUTTON, &EditPanel::OnDumpButtonDown, this);
	reset_button->Bind(wxEVT_BUTTON, &EditPanel::OnResetButtonDown, this);
	m_aui_notebook->Bind(wxEVT_AUINOTEBOOK_PAGE_CHANGED, &EditPanel::OnPageChange, this);
	// m_text_ctrl->Bind(wxEVT_TEXT, &EditPanel::OnPageEdit, this); // Seems slow!
	m_text_ctrl->Bind(wxEVT_TEXT_ENTER, &EditPanel::OnPageEdit, this);  // Hopefully faster.
	m_aui_notebook->Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &EditPanel::OnPageClose, this);
}

void EditPanel::OnRunButtonDown(wxCommandEvent& event)  // Add a timer too??
{
	wxWindow* current_page = m_aui_notebook->GetCurrentPage();
	wxTextCtrl* current_text_ctrl = (wxTextCtrl*)current_page;
	std::string current_text = current_text_ctrl->GetValue().ToStdString();
	std::string current_tab = m_aui_notebook->GetPageText(m_aui_notebook->GetSelection()).ToStdString();
	if (string_ends_with(current_tab, SW_EXPERIMENT_EXTENSION))  // If the current file has experiment extension, then parse the experiment.
	{
		ParseExperiment(current_text);
		return;
	}
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
	the_timer.Stop();  // Maybe shift this before non-parse related work.
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

void EditPanel::OnResetButtonDown(wxCommandEvent& event)
{
	wxString reset_context_text = wxString::Format("Are you really sure you want to erase the current context \"%s\"?\nAll knowledge in this context will be deleted!", driver.context.get_context_name());
	ResetContextDialog* dlg = new ResetContextDialog(this, "Reset context", reset_context_text);
	if (dlg->ShowModal() == wxID_OK)
	{
		driver.context.reset_current_context();
	}
}

void EditPanel::OnPageChange(wxCommandEvent& event)
{
	m_text_ctrl = (wxTextCtrl*)(m_aui_notebook->GetCurrentPage());
	m_current_tab = m_aui_notebook->GetPageText(m_aui_notebook->GetSelection());
	if (m_unsaved_tabs.find(m_current_tab) == m_unsaved_tabs.end())  // This tab is new to us, so add it to the unsaved_tabs map.
	{
		m_unsaved_tabs[m_current_tab] = false;
		m_text_ctrl->Bind(wxEVT_TEXT_ENTER, &EditPanel::OnPageEdit, this);  // Does this bug out anywhere?? Probably!
	}
}

void EditPanel::OnPageEdit(wxCommandEvent& event)
{
	if (m_unsaved_tabs.find(m_current_tab) != m_unsaved_tabs.end())
	{
		if (m_unsaved_tabs[m_current_tab])
		{
			event.Skip();
			return;  // Page known to be edited, so do nothing.
		}
	}
	m_current_tab = m_aui_notebook->GetPageText(m_aui_notebook->GetSelection());  // Page newly edited, so let's update some things.
	m_unsaved_tabs[m_current_tab] = true;
	wxString star_tab = "*" + m_current_tab;
	m_aui_notebook->SetPageText(m_aui_notebook->GetSelection(), star_tab);
	event.Skip();
}

void EditPanel::OnPageClose(wxCommandEvent& event)
{
	wxString current_tab = GetTabLabel();
	if (m_unsaved_tabs.find(current_tab) != m_unsaved_tabs.end())
	{
		if (m_unsaved_tabs[current_tab])
		{
			m_unsaved_tabs.erase(current_tab);
			if (wxMessageBox(current_tab + " has not been saved! Save?", "Save?", wxICON_QUESTION | wxYES_NO, this) == wxNO)
			{
				return;
			}
			else
			{
				wxFileDialog saveFileDialog(this, "Save sw file", "", current_tab, "sw file (*.sw;*.swc;*.sw3;*.sw4)|*.sw;*.swc;*.sw3;*.sw4|Text file (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
				if (saveFileDialog.ShowModal() == wxID_CANCEL)
				{
					return;
				}
				SaveFile(saveFileDialog.GetPath());
			}
			return;
		}
		m_unsaved_tabs.erase(current_tab);
	}
}

void EditPanel::AddPage(wxWindow* page, const wxString& caption, bool select)
{
	m_aui_notebook->AddPage(page, caption, select);
}


void EditPanel::ModifyPage(wxWindow* page, const wxString& caption, bool select)
{
	size_t page_count = m_aui_notebook->GetPageCount();
	wxString star_tab_label = "*" + caption;
	for (size_t i = 0; i < page_count; i++)
	{
		if (m_aui_notebook->GetPageText(i) == caption || m_aui_notebook->GetPageText(i) == star_tab_label)  // Page tab exists.
		{
			m_aui_notebook->DeletePage(i);
			m_aui_notebook->InsertPage(i, page, caption, select);
			return;
		}
	}
}

wxString EditPanel::GetTabLabel()
{
	wxString tab_label = m_aui_notebook->GetPageText(m_aui_notebook->GetSelection());
	if (tab_label.StartsWith("*"))
	{
		return tab_label.AfterFirst('*');
	}
	return tab_label;
}

bool EditPanel::TabLabelExists(const wxString& tab_label)
{
	size_t page_count = m_aui_notebook->GetPageCount();
	wxString star_tab_label = "*" + tab_label;
	for (size_t i = 0; i < page_count; i++)
	{
		if (m_aui_notebook->GetPageText(i) == tab_label || m_aui_notebook->GetPageText(i) == star_tab_label)
		{
			return true;  // Page tab exists.
		}
	}
	return false;  // Page tab is new.
}

void EditPanel::SaveFile(const wxString& filename)
{
	// wxMessageBox("Edit panel SaveFile: " + filename);
	wxWindow* current_page = m_aui_notebook->GetCurrentPage();
	wxTextCtrl* current_text_ctrl = (wxTextCtrl*)current_page;
	wxString current_text = current_text_ctrl->GetValue();
	wxFileOutputStream output_stream(filename);
	if (!output_stream.IsOk())
	{
		wxLogError("Cannot save to file '%s'.", filename);
		return;
	}
	wxTextOutputStream text(output_stream);
	text.WriteString(current_text);
	m_current_tab = m_aui_notebook->GetPageText(m_aui_notebook->GetSelection());
	if (m_current_tab.StartsWith("*"))
	{
		m_current_tab = m_current_tab.AfterFirst('*');
		if (m_unsaved_tabs.find(m_current_tab) != m_unsaved_tabs.end())
		{
			m_aui_notebook->SetPageText(m_aui_notebook->GetSelection(), m_current_tab);
			m_unsaved_tabs[m_current_tab] = false;
		}
	}
}

void EditPanel::WriteText(const wxString& text)
{
	m_text_ctrl->WriteText(text);
}

void EditPanel::InsertText(const wxString& wxs)
{
	m_text_ctrl->WriteText(wxs);
}

void EditPanel::InsertStatement(const wxString& wxs)
{
	std::string statement_name = wxs.ToStdString();
	if (operator_usage_map.has_statement_prototype(statement_name))
	{
		m_text_ctrl->WriteText(operator_usage_map.statement_prototypes[statement_name]);
	}
}

void EditPanel::InsertLearnRule(const wxString& wxs)
{
	m_text_ctrl->WriteText(wxs + " ");
}

void EditPanel::InsertInfixOperator(const wxString& wxs)
{
	m_text_ctrl->WriteText(wxs + " ");
}

void EditPanel::InsertSimpleOperator(const wxString& wxs)
{
	m_text_ctrl->WriteText(wxs + " ");
}

void EditPanel::InsertCompoundOperator(const wxString& wxs)
{
	m_text_ctrl->WriteText(wxs + "[ ] ");
	m_text_ctrl->SetInsertionPoint(m_text_ctrl->GetInsertionPoint() - 3);
}

void EditPanel::InsertFunctionOperator(const wxString& wxs)
{
	m_text_ctrl->WriteText(wxs + "( ) ");
	m_text_ctrl->SetInsertionPoint(m_text_ctrl->GetInsertionPoint() - 3);
}

void EditPanel::InsertKet(const wxString& wxs)
{
	m_text_ctrl->WriteText(wxs + " ");
}

void EditPanel::InsertComment()
{
	m_text_ctrl->WriteText("\n--  ");
}

void EditPanel::ParseExperiment(const std::string& commands)  // Is EditPanel the best location for this code??
{
	for (const auto& line : split(commands, "\n"))
	{
		if (line == "" || string_starts_with(line, "--"))  // Comment line
		{
			continue;
		}
		else if (line == "exit")   // Exit experiment
		{
			return;
		}
		else if (line == "dump")   // Dump current context
		{
			// wxMessageBox("dump current context");
			std::stringstream buffer;
			context.print_universe(true, buffer);
			std::string captured_text = buffer.str();
			wxString title = wxString::Format("Dump of the current context \"%s\"", driver.context.get_context_name());
			DumpFrame* dump_frame = new DumpFrame(this, title, captured_text);
		}
		else if (line == "reset")  // reset current context
		{
			// wxMessageBox("reset current context");
			driver.context.reset_current_context();
		}
		else if (line == "reset all")  // reset all knowledge
		{
			// wxMessageBox("reset all!");
			driver.context.reset();
		}
		else if (line == "line")   // Insert a horizontal line
		{
			wxMessageBox("Insert a horizontal line");  // I don't think we want this feature!
		}
		else
		{
			std::vector<std::string> split_command = split_on_first(line, " ");
			if (split_command.size() != 2)  // If split_command is not length 2, then continue to next command.
			{
				continue;
			}
			std::string head = split_command[0];
			std::string tail = split_command[1];
			if (head == "context")  // Switch to context "tail".
			{
				// wxMessageBox("Switch to context: " + tail);
				driver.context.set(tail);
			}
			else if (head == "load")  // Load a file. Also, check if file is already in the tabs.
			{
				// wxMessageBox("Load file: " + tail);
				int current_page_idx = m_aui_notebook->GetSelection();
				wxFileDialog openFileDialog(this, "Open sw file", "", tail, "sw file (*.sw;*.swc;*.sw3;*.sw4)|*.sw;*.swc;*.sw3;*.sw4|Text file (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
				if (openFileDialog.ShowModal() == wxID_CANCEL)
					return;
				wxFileInputStream input_stream(openFileDialog.GetPath());
				if (!input_stream.IsOk())
				{
					wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
					return;    // Maybe prompt for continue vs exit?
				}
				wxString file_content;
				wxTextInputStream text(input_stream, wxT("\x09"), wxConvUTF8);  // Check these settings are correct later.
				while (input_stream.IsOk() && !input_stream.Eof())
				{
					file_content.Append(text.ReadLine());
					file_content.Append("\n");  // There must be a better way to keep newlines in the text!
				}
				wxTextCtrl* textCtrlLocal = new wxTextCtrl(this, wxID_ANY, file_content, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
				AddPage(textCtrlLocal, tail, false);
				m_aui_notebook->SetSelection(current_page_idx);
			}
			else if (head == "webload")  // Load a remote file
			{
				// wxMessageBox("Webload url: " + tail);
				wxURL url(tail);
				if (url.GetError() == wxURL_NOERR)
				{
					wxString htmldata;
					wxInputStream* in = url.GetInputStream();

					if (in && in->IsOk())
					{
						wxStringOutputStream html_stream(&htmldata);
						in->Read(html_stream);
						// wxLogMessage(htmldata);
						wxTextCtrl* textCtrlLocal = new wxTextCtrl(this, wxID_ANY, htmldata, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
						std::string cleaned_filename = std::filesystem::path(tail).filename().string();
						AddPage(textCtrlLocal, cleaned_filename, false);
					}
					else
					{
						wxMessageBox("Failed to web load: " + tail);
					}
					delete in;
				}
			}
			else if (head == "run")  // Run the given file
			{
				// wxMessageBox("Run file: " + tail);
				size_t notebook_page_count = m_aui_notebook->GetPageCount();
				int matching_page_idx = -1;
				for (size_t i = 0; i < notebook_page_count; i++)
				{
					if (m_aui_notebook->GetPageText(i) == tail)  // If more than one tab has the same name, then stop on first match.
					{
						matching_page_idx = i;
						break;
					}
				}
				if (matching_page_idx == -1)
				{
					wxLogError("File not open '%s'.", tail);
					return;
				}
				wxWindow* run_page = m_aui_notebook->GetPage(matching_page_idx);
				wxTextCtrl* current_text_ctrl = (wxTextCtrl*)run_page;
				std::string current_text = current_text_ctrl->GetValue().ToStdString();
				Timer_ms the_timer;
				std::stringstream buffer;
				std::streambuf* old_buffer = std::cout.rdbuf(buffer.rdbuf());
				driver.result.clear();
				bool parse_success = driver.parse_string(current_text + "\n");
				std::string captured_text = buffer.str();
				std::cout.rdbuf(old_buffer);
				if (!parse_success)
				{
					wxMessageBox("Parse failed!");
					return;
				}
				std::string result_string = driver.result.to_string();
				OutputFrame* output_frame = new OutputFrame(this, "Output Window", captured_text, result_string);
				the_timer.Stop();  // Maybe shift this before non-parse related work.
				long long run_time = the_timer.GetTime();
				output_frame->SetRunTime(run_time);
			}
			else if (head == "save")
			{
				// wxMessageBox("Save current context to file: " + tail);
				wxFileDialog saveFileDialog(this, "Save sw file", "", tail, "sw file (*.sw;*.swc;*.sw3;*.sw4)|*.sw;*.swc;*.sw3;*.sw4|Text file (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
				if (saveFileDialog.ShowModal() == wxID_CANCEL)
				{
					return;
				}
				wxFileOutputStream output_stream(saveFileDialog.GetPath());
				if (!output_stream.IsOk())
				{
					wxLogError("Cannot save to file '%s'.", saveFileDialog.GetPath());
					return;
				}
				wxTextOutputStream text(output_stream);
				std::stringstream buffer;
				context.print_universe(true, buffer);
				std::string current_text = buffer.str();
				text.WriteString(current_text);
				wxTextCtrl* textCtrlLocal = new wxTextCtrl(this, wxID_ANY, current_text, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
				AddPage(textCtrlLocal, tail, false);
			}
			else if (head == "save-as-dot")  // Save current context as a dot file for use with graphviz.
			{
				// wxMessageBox("Save as dot, file: " + tail);
				if (!string_ends_with(tail, ".dot"))
				{
					wxMessageBox("Dot file has incorrect extension: " + tail);
					return;
				}
				std::string dot_file = context_to_dot(driver.context);
				wxFileDialog saveFileDialog(this, "Save dot file", "", tail, "dot file (*.dot)|*.dot", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
				if (saveFileDialog.ShowModal() == wxID_CANCEL)
				{
					return;
				}
				wxFileOutputStream output_stream(saveFileDialog.GetPath());
				if (!output_stream.IsOk())
				{
					wxLogError("Cannot save to file '%s'.", saveFileDialog.GetPath());
					return;
				}
				wxTextOutputStream text(output_stream);
				text.WriteString(dot_file);
			}
			else  // Not a valid command, so continue to the next command. Should we put up a dialog?
			{
				continue;
			}
		}
	}
}


EditPanel::~EditPanel()
{}
