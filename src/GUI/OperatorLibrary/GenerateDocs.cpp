//
// Semantic DB 4
// Created 2023/4/12
// Updated 2023/4/12
// Author Garry Morrison
// License GPL v3
//

#include "GenerateDocs.h"

GenerateDocs::GenerateDocs(bool text, bool html, bool linkify, bool yes_to_all, bool warn, bool dont_warn, wxString template_path, wxString examples_path, wxString destination_path)
{
	// Define our template files:
	const wxString list_element_template = "list-element-template.html";
	const wxString index_template = "index-template.html";
	const wxString operator_template = "operator-template.html";
	const wxString example_template = "example-template.html";
	
	wxFileName working_file;
	working_file = wxFileName(template_path, list_element_template);
	std::string list_element_template_str = read_file(working_file.GetFullPath()).ToStdString();
	// std::string populated_list = generate_list(fn_map.list_of_statements, list_element_template_str);
	// std::string populated_list = generate_list(fn_map.list_of_learn_rules, list_element_template_str);
	std::string populated_list;

	// Get the current date:
	wxDateTime current_date = current_date.UNow();
	std::string current_date_str = current_date.FormatISODate().ToStdString(); // Tidy up the std::string vs wxString mess!

	// wxFileName tmp_file(template_path, list_element_template);
	// wxFileName tmp_file(template_path, example_template);
	wxFileName tmp_file(template_path, index_template);
	std::string file_contents = read_file(tmp_file.GetFullPath()).ToStdString();

	// Insert current date:
	string_replace_all(file_contents, "$creation-date$", current_date_str);
	
	// Populate Language Elements menu:
	populated_list = generate_list(fn_map.list_of_statements, list_element_template_str);
	string_replace_all(file_contents, "$language-elements-statements-list$", populated_list);

	populated_list = generate_list(fn_map.list_of_learn_rules, list_element_template_str);
	string_replace_all(file_contents, "$language-elements-learn-rules-list$", populated_list);

	populated_list = generate_list(fn_map.list_of_infix_type1, list_element_template_str);
	string_replace_all(file_contents, "$language-elements-infix-type-1-list$", populated_list);

	populated_list = generate_list(fn_map.list_of_infix_type2, list_element_template_str);
	string_replace_all(file_contents, "$language-elements-infix-type-2-list$", populated_list);

	populated_list = generate_list(fn_map.list_of_misc_elements, list_element_template_str);
	string_replace_all(file_contents, "$language-elements-miscellaneous-elements-list$", populated_list);

	populated_list = generate_list(fn_map.list_of_object_types, list_element_template_str);
	string_replace_all(file_contents, "$language-elements-object-types-list$", populated_list);

	populated_list = generate_list(fn_map.list_of_operator_types, list_element_template_str);
	string_replace_all(file_contents, "$language-elements-operator-types-list$", populated_list);


	wxMessageBox("Generate Docs invoked\nDate: " + current_date_str + "\ntemplate file: " + tmp_file.GetFullPath() + "\nfile contents:\n" + file_contents);
	// wxMessageBox("Generate Docs invoked\nDate: " + current_date_str + "\ntemplate file: " + tmp_file.GetFullPath() + "\npopulated list:\n" + populated_list);
}

wxString GenerateDocs::read_file(const wxString our_filename)
{
	wxString file_text;
	wxTextFile tfile(our_filename);
	if (!tfile.Exists())
	{
		wxMessageBox("File does not exist!");
	}
	else
	{
		tfile.Open(our_filename);
		file_text = tfile.GetFirstLine();
		while (!tfile.Eof())
		{
			file_text += "\n" + tfile.GetNextLine();
		}
	}
	return file_text;
}

std::string GenerateDocs::escape_html_chars(const std::string& source)
{
	std::string result = source;
	string_replace_all(result, ">", "&gt;");
	string_replace_all(result, "<", "&lt;");
	return result;
}

std::string GenerateDocs::generate_list(const std::vector<std::string>& list_of_elements, const std::string& list_element_template)
{
	std::string result;
	for (const auto& s : list_of_elements)
	{
		std::string tmp_str = list_element_template;
		string_replace_all(tmp_str, "$list-element-label$", escape_html_chars(s));
		result += "\n" + tmp_str;
	}
	return result;
}

GenerateDocs::~GenerateDocs()
{}
