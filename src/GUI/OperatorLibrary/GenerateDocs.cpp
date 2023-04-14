//
// Semantic DB 4
// Created 2023/4/12
// Updated 2023/4/14
// Author Garry Morrison
// License GPL v3
//

#include "GenerateDocs.h"

// GenerateDocs::GenerateDocs(bool text, bool html, bool linkify, bool yes_to_all, bool warn, bool dont_warn, wxString template_path, wxString examples_path, wxString destination_path)
GenerateDocs::GenerateDocs(bool yes_to_all, bool warn, bool dont_warn, wxString template_path, wxString examples_path, wxString destination_path)
{
	// Load our substitution element paths:
	wxString settings_file = "template-settings.txt";
	std::map<std::string, std::string> settings_map = populate_settings_map(template_path, settings_file);
	if (settings_map.empty())
	{
		wxMessageBox("Settings file is empty!");
		return;
	}

	// Define our template files:
	const std::string index_template = settings_map["index-template"];
	const std::string operator_template = settings_map["operator-template"];
	const std::string example_template = settings_map["example-template"];
	const std::string list_element_template = settings_map["list-element-template"];
	const std::string linkify_template = settings_map["linkify-template"];

	// Load some settings:
	const std::string destination_file_extension = settings_map["destination-file-extension"];
	const std::string use_linkify = settings_map["use-linkify"];
	const std::string css_path = settings_map["css-path"];
	const std::string image_path = settings_map["image-path"];

	// Load the list element template string:
	wxFileName working_file;
	working_file = wxFileName(template_path, list_element_template);
	std::string list_element_template_str = read_file(working_file.GetFullPath()).ToStdString();

	// Get the current date:
	wxDateTime current_date = current_date.UNow();
	std::string current_date_str = current_date.FormatISODate().ToStdString(); // Tidy up the std::string vs wxString mess!

	// Load the index file contents:
	wxFileName tmp_file(template_path, index_template);
	std::string file_contents = read_file(tmp_file.GetFullPath()).ToStdString();

	// Insert current date:
	string_replace_all(file_contents, "$creation-date$", current_date_str);
	
	// Populate Language Elements menu:
	populate_list(file_contents, "$language-elements-statements-list$", fn_map.list_of_statements, settings_map, list_element_template_str, destination_file_extension);
	populate_list(file_contents, "$language-elements-learn-rules-list$", fn_map.list_of_learn_rules_spaces, settings_map, list_element_template_str, destination_file_extension);
	populate_list(file_contents, "$language-elements-infix-type-1-list$", fn_map.list_of_infix_type1_spaces, settings_map, list_element_template_str, destination_file_extension);
	populate_list(file_contents, "$language-elements-infix-type-2-list$", fn_map.list_of_infix_type2_spaces, settings_map, list_element_template_str, destination_file_extension);
	populate_list(file_contents, "$language-elements-miscellaneous-elements-list$", fn_map.list_of_misc_elements, settings_map, list_element_template_str, destination_file_extension);
	populate_list(file_contents, "$language-elements-object-types-list$", fn_map.list_of_object_types, settings_map, list_element_template_str, destination_file_extension);
	populate_list(file_contents, "$language-elements-operator-types-list$", fn_map.list_of_operator_types, settings_map, list_element_template_str, destination_file_extension);

	// Populate examples menu:
	std::vector<std::string> list_of_sw_examples = scan_directory(examples_path);
	populate_list(file_contents, "$examples-list$", list_of_sw_examples, settings_map, list_element_template_str, destination_file_extension, true);

	wxMessageBox("Generate Docs invoked\nDate: " + current_date_str + "\ntemplate file: " + tmp_file.GetFullPath() + "\nfile contents:\n" + file_contents);
	// wxMessageBox("Generate Docs invoked\nDate: " + current_date_str + "\ntemplate file: " + tmp_file.GetFullPath() + "\npopulated list:\n" + populated_list);
}

wxString GenerateDocs::read_file(const wxString our_filename)
{
	wxString file_text;
	wxTextFile tfile(our_filename);
	if (!tfile.Exists())
	{
		wxMessageBox("File:\n" + our_filename + "\ndoes not exist!");
	}
	else
	{
		tfile.Open();
		file_text = tfile.GetFirstLine();
		while (!tfile.Eof())
		{
			file_text += "\n" + tfile.GetNextLine();
		}
	}
	return file_text;
}

std::map<std::string, std::string> GenerateDocs::populate_settings_map(wxString template_path, wxString settings_file)
{
	std::map<std::string, std::string> our_map;
	wxFileName tmp_file(template_path, settings_file);
	wxTextFile tfile(tmp_file.GetFullPath());
	if (!tfile.Exists())
	{
		wxMessageBox("Paths file:\n" + tmp_file.GetFullPath() + "\ndoes not exist!");
	}
	else
	{
		tfile.Open();
		std::vector<std::string> element_paths_vec = split_on_first(tfile.GetFirstLine().ToStdString(), " ");
		if (element_paths_vec.size() == 2)
		{
			std::string element = element_paths_vec[0];
			std::string path = element_paths_vec[1];
			our_map[element] = path;
		}
		while (!tfile.Eof())
		{
			element_paths_vec = split_on_first(tfile.GetNextLine().ToStdString(), " ");
			if (element_paths_vec.size() == 2)
			{
				std::string element = element_paths_vec[0];
				std::string path = element_paths_vec[1];
				our_map[element] = path;
			}
		}
	}
	return our_map;
}

std::string GenerateDocs::escape_infix_operators(const std::string& raw_string)
{
	if (raw_string == " + ") { return "infix_plus"; }
	if (raw_string == " - ") { return "infix_minus"; }
	if (raw_string == " _ ") { return "infix_merge"; }
	if (raw_string == " __ ") { return "infix_smerge"; }
	if (raw_string == " :_ ") { return "infix_colon_merge"; }
	if (raw_string == " . ") { return "infix_seq"; }
	if (raw_string == " => ") { return "learn_rule"; }
	if (raw_string == " _=> ") { return "non_empty_learn_rule"; }
	if (raw_string == " +=> ") { return "add_learn_rule"; }
	if (raw_string == " .=> ") { return "seq_learn_rule"; }
	if (raw_string == " #=> ") { return "stored_learn_rule"; }
	if (raw_string == " !=> ") { return "memoize_learn_rule"; }
	if (raw_string == " == ") { return "infix_equal"; }
	if (raw_string == " != ") { return "infix_not_equal"; }
	if (raw_string == " >= ") { return "infix_greater_equal"; }
	if (raw_string == " > ") { return "infix_greater"; }
	if (raw_string == " <= ") { return "infix_less_equal"; }
	if (raw_string == " < ") { return "infix_less"; }
	if (raw_string == " && ") { return "infix_and"; }
	if (raw_string == " || ") { return "infix_or"; }
	if (raw_string == " ++ ") { return "infix_double_plus"; }
	if (raw_string == " -- ") { return "infix_double_minus"; }
	if (raw_string == " ** ") { return "infix_double_mult"; }
	if (raw_string == " // ") { return "infix_double_div"; }
	if (raw_string == " %% ") { return "infix_double_mod"; }
	if (raw_string == " ^^ ") { return "infix_double_pow"; }
	if (raw_string == " .. ") { return "infix_range"; }
	if (raw_string == "|*>") { return "misc_star_ket"; }
	if (raw_string == "|category: *>") { return "misc_category_ket"; }
	if (raw_string == "|_self>") { return "misc_self_ket"; }
	if (raw_string == "(*,*)") { return "misc_star_params"; }
	if (raw_string == "|__self>") { return "misc_multi_self_ket"; }
	if (raw_string == "|context>") { return "misc_context_ket"; }
	if (raw_string == "|>") { return "misc_empty_ket"; }
	return raw_string;
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

void GenerateDocs::populate_list(std::string& file_contents, const std::string list_element, const std::vector<std::string>& list_of_elements, const std::map<std::string, std::string>& paths_map, const std::string list_element_template_str, const std::string extension, bool strip_extension_bool )
{
	std::string list_element_path = "";
	if (paths_map.find(list_element) != paths_map.end())
	{
		list_element_path = paths_map.at(list_element);
	}
	std::string generated_list;
	for (const auto& s : list_of_elements)
	{
		std::string tmp_str = list_element_template_str;
		if (strip_extension_bool)
		{
			string_replace_all(tmp_str, "$list-element-path$", list_element_path + strip_extension(escape_infix_operators(s)).ToStdString() + extension);
			string_replace_all(tmp_str, "$list-element-label$", strip_extension(escape_html_chars(s)).ToStdString());
		}
		else
		{
			string_replace_all(tmp_str, "$list-element-path$", list_element_path + escape_infix_operators(s) + extension);
			string_replace_all(tmp_str, "$list-element-label$", escape_html_chars(s));
		}
		generated_list += "\n" + tmp_str;
	}
	// wxMessageBox(list_element + "\n" + generated_list);
	string_replace_all(file_contents, list_element, generated_list);
}

std::vector<std::string> GenerateDocs::scan_directory(const wxString directory_name)
{
	std::vector<std::string> directory_list;
	wxDir our_sw_dir(directory_name);
	if (!our_sw_dir.IsOpened())
	{
		wxMessageBox("Directory:\n" + directory_name + "\ndoes not exist!");
		return directory_list;
	}
	wxString filename;
	bool have_file = our_sw_dir.GetFirst(&filename);
	while (have_file)
	{
		directory_list.push_back(filename.ToStdString());
		have_file = our_sw_dir.GetNext(&filename);
	}
	return directory_list;
}

wxString GenerateDocs::strip_extension(const wxString our_filename)
{
	return our_filename.BeforeLast('.');
}

GenerateDocs::~GenerateDocs()
{}
