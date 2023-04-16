//
// Semantic DB 4
// Created 2023/4/12
// Updated 2023/4/16
// Author Garry Morrison
// License GPL v3
//

#include "GenerateDocs.h"


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
	const std::string escape_html_chars = settings_map["escape-html-chars"];
	const std::string use_linkify = settings_map["use-linkify"];
	const std::string source_css_path = settings_map["$source-css-path$"];
	const std::string source_image_path = settings_map["$source-image-path$"];
	const std::string destination_css_path = settings_map["$destination-css-path$"];
	const std::string destination_image_path = settings_map["$destination-image-path$"];

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

	// Insert current date, and css and image paths:
	string_replace_all(file_contents, "$creation-date$", current_date_str);
	string_replace_all(file_contents, "$destination-css-path$", destination_css_path);
	string_replace_all(file_contents, "$destination-image-path$", destination_image_path);

	// Load the operator template string:
	working_file = wxFileName(template_path, operator_template);
	std::string operator_template_str = read_file(working_file.GetFullPath()).ToStdString();
	
	// Insert current date, and home, css and image paths:
	string_replace_all(operator_template_str, "$creation-date$", current_date_str);
	string_replace_all(operator_template_str, "$home-file$", index_template);
	string_replace_all(operator_template_str, "$destination-css-path$", destination_css_path);
	string_replace_all(operator_template_str, "$destination-image-path$", destination_image_path);
	bool escape_html = false;
	if (escape_html_chars == "yes")
	{
		escape_html = true;
	}
	// Testing the code before scaling up:
	populate_and_write_operator_template(operator_template_str, "is-mbr", destination_path.ToStdString(), normalize_path_separator("testing/foo/bah"), destination_file_extension, yes_to_all, warn, dont_warn, escape_html);
	populate_and_write_operator_template(operator_template_str, "if-else", destination_path.ToStdString(), normalize_path_separator("testing/foo/bah"), destination_file_extension, yes_to_all, warn, dont_warn, escape_html);
	populate_and_write_operator_template(operator_template_str, " => ", destination_path.ToStdString(), normalize_path_separator("testing/foo/bah"), destination_file_extension, yes_to_all, warn, dont_warn, escape_html);
	populate_and_write_operator_template(operator_template_str, " +=> ", destination_path.ToStdString(), normalize_path_separator("testing/foo/bah"), destination_file_extension, yes_to_all, warn, dont_warn, escape_html);

	// Load the example template string:
	working_file = wxFileName(template_path, example_template);
	std::string example_template_str = read_file(working_file.GetFullPath()).ToStdString();

	// Insert current date, and home, css and image paths:
	string_replace_all(example_template_str, "$creation-date$", current_date_str);
	string_replace_all(example_template_str, "$home-file$", index_template);
	string_replace_all(example_template_str, "$destination-css-path$", destination_css_path);
	string_replace_all(example_template_str, "$destination-image-path$", destination_image_path);
	return;


	// Populate Language Elements menu:
	populate_list(file_contents, "$language-elements-statements-list$", fn_map.list_of_statements, settings_map, list_element_template_str, destination_file_extension, false, destination_path.ToStdString(), operator_template_str, yes_to_all, warn, dont_warn);
	populate_list(file_contents, "$language-elements-learn-rules-list$", fn_map.list_of_learn_rules_spaces, settings_map, list_element_template_str, destination_file_extension, false, destination_path.ToStdString(), operator_template_str, yes_to_all, warn, dont_warn);
	populate_list(file_contents, "$language-elements-infix-type-1-list$", fn_map.list_of_infix_type1_spaces, settings_map, list_element_template_str, destination_file_extension, false, destination_path.ToStdString(), operator_template_str, yes_to_all, warn, dont_warn);
	populate_list(file_contents, "$language-elements-infix-type-2-list$", fn_map.list_of_infix_type2_spaces, settings_map, list_element_template_str, destination_file_extension, false, destination_path.ToStdString(), operator_template_str, yes_to_all, warn, dont_warn);
	populate_list(file_contents, "$language-elements-miscellaneous-elements-list$", fn_map.list_of_misc_elements, settings_map, list_element_template_str, destination_file_extension, false, destination_path.ToStdString(), operator_template_str, yes_to_all, warn, dont_warn);
	populate_list(file_contents, "$language-elements-object-types-list$", fn_map.list_of_object_types, settings_map, list_element_template_str, destination_file_extension, false, destination_path.ToStdString(), operator_template_str, yes_to_all, warn, dont_warn);
	populate_list(file_contents, "$language-elements-operator-types-list$", fn_map.list_of_operator_types, settings_map, list_element_template_str, destination_file_extension, false, destination_path.ToStdString(), operator_template_str, yes_to_all, warn, dont_warn);

	// Populate examples menu:
	std::vector<std::string> list_of_sw_examples = scan_directory(examples_path);
	populate_list(file_contents, "$examples-list$", list_of_sw_examples, settings_map, list_element_template_str, destination_file_extension, true, destination_path.ToStdString(), example_template_str, yes_to_all, warn, dont_warn);

	// Now write it to disk:
	write_file(destination_path, index_template, file_contents, yes_to_all, warn, dont_warn);

	// Copy css files:
	copy_binary_files(template_path.ToStdString(), source_css_path, destination_path.ToStdString(), destination_css_path, yes_to_all, warn, dont_warn);

	// Copy image files:
	copy_binary_files(template_path.ToStdString(), source_image_path, destination_path.ToStdString(), destination_image_path, yes_to_all, warn, dont_warn);

	wxMessageBox("Generate Docs invoked\nDate: " + current_date_str + "\ntemplate file: " + tmp_file.GetFullPath() + "\nfile contents:\n" + file_contents);
	// wxMessageBox("Generate Docs invoked\nDate: " + current_date_str + "\ntemplate file: " + tmp_file.GetFullPath() + "\npopulated list:\n" + populated_list);
}

std::string GenerateDocs::normalize_path_separator(const std::string source_path)
{
	std::filesystem::path windows_path(source_path);
	return windows_path.make_preferred().string();
}

std::string GenerateDocs::get_inverse_path(const std::string source_path)
{
	if (source_path.empty())
	{
		return source_path;
	}
	std::filesystem::path sub_path(source_path);
	std::filesystem::path inverse_sub_path;
	for (const auto& p : sub_path)
	{
		inverse_sub_path.append("..");
	}
	return inverse_sub_path.string() + normalize_path_separator("/");
}

void GenerateDocs::write_file(const wxString file_path, const wxString file_name, const wxString file_body, bool overwrite_yes_to_all, bool overwrite_warn, bool overwrite_no)
{
	if (!wxFileName::Mkdir(file_path, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL))
	{
		wxMessageBox("Failed to create directory: " + file_path);
		return;
	}
	wxFileName working_file(file_path, file_name);
	wxString working_file_str = working_file.GetFullPath();
	wxTextFile tfile(working_file_str);
	bool will_write_file = false;
	if (!tfile.Exists())
	{
		will_write_file = true;
	}
	if (overwrite_yes_to_all)
	{
		wxMessageBox("Will overwrite file");
		will_write_file = true;
	}
	if (overwrite_warn && tfile.Exists())
	{
		
		wxMessageDialog* dlg = new wxMessageDialog(NULL, "Do you want to overwrite file: " + file_name + "?", "Overwrite File", wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
		if (dlg->ShowModal() == wxID_YES)
		{
			wxMessageBox("File overwritten");
			will_write_file = true;
		}
		else
		{
			wxMessageBox("File skipped");
			will_write_file = false;
		}
	}
	if (overwrite_no)
	{
		wxMessageBox("Will not overwrite file");
		will_write_file = false;
	}
	if (will_write_file)
	{
		if (tfile.Exists())
		{
			tfile.Open();
			tfile.Clear();
		}
		else
		{
			tfile.Create();
		}
		wxStringTokenizer tokenizer(file_body, "\n"); // Is there a better way to extract lines from a string?
		while (tokenizer.HasMoreTokens())
		{
			wxString line = tokenizer.GetNextToken();
			tfile.AddLine(line);
		}
		tfile.Write();
		tfile.Close();
	}
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

wxString GenerateDocs::read_file(const wxString file_path, const wxString file_name)
{
	wxString file_text;
	wxFileName working_file(file_path, file_name);
	wxString working_file_str = working_file.GetFullPath();
	wxTextFile tfile(working_file_str);
	if (!tfile.Exists())
	{
		wxMessageBox("File:\n" + file_name + "\ndoes not exist!");
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
			our_map[element] = normalize_path_separator(path);
		}
		while (!tfile.Eof())
		{
			element_paths_vec = split_on_first(tfile.GetNextLine().ToStdString(), " ");
			if (element_paths_vec.size() == 2)
			{
				std::string element = element_paths_vec[0];
				std::string path = element_paths_vec[1];
				our_map[element] = normalize_path_separator(path);
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

std::string GenerateDocs::escape_html_chars(const std::string& source, bool invoke)
{
	if (!invoke)
	{
		return source;
	}
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

void GenerateDocs::populate_list(std::string& file_contents, const std::string list_element, const std::vector<std::string>& list_of_elements, const std::map<std::string, std::string>& paths_map, const std::string list_element_template_str, const std::string extension, bool strip_extension_bool, const std::string destination_path, const std::string template_str, bool overwrite_yes_to_all, bool overwrite_warn, bool overwrite_no)
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

std::string GenerateDocs::wrap_lines_in_html_p(const std::string& source_str)
{
	std::vector<std::string> string_lines = split(source_str, "\n");
	std::string result;
	for (const auto& line : string_lines)
	{
		result += "<p>" + line + "</p>\n";
	}
	return result;
}


void GenerateDocs::populate_and_write_operator_template(const std::string template_str, const std::string name, const std::string destination_path, const std::string destination_sub_path, const std::string extension, bool overwrite_yes_to_all, bool overwrite_warn, bool overwrite_no, bool escape_html)
{
	std::string local_template_str = template_str;
	string_replace_all(local_template_str, "$operator-name$", escape_html_chars(name, escape_html));
	if (!operator_usage_map.usage_is_defined(name))
	{
		wxMessageBox("No usage info available for operator: " + name);
		return;
	}
	OpUsageInfo* usageInfo = operator_usage_map.get_usage_info(name);
	if (!usageInfo)
	{
		wxMessageBox("No usage info found.");
		return;
	}
	string_replace_all(local_template_str, "$operator-description$", escape_html_chars(usageInfo->Description, escape_html));
	string_replace_all(local_template_str, "$operator-examples$", escape_html_chars(usageInfo->Examples, escape_html));
	string_replace_all(local_template_str, "$operator-see-also$", escape_html_chars(usageInfo->SeeAlso, escape_html));

	std::vector<std::string> operator_types = fn_map.get_operator_types(name);
	std::string operator_types_str = join(operator_types, ", ");
	wxMessageBox("operator types: " + operator_types_str);
	string_replace_all(local_template_str, "$operator-type$", operator_types_str);

	std::string inverse_sub_path = get_inverse_path(destination_sub_path);
	string_replace_all(local_template_str, "$operator-home-path-prefix$", inverse_sub_path);
	string_replace_all(local_template_str, "$operator-css-path-prefix$", inverse_sub_path);

	std::filesystem::path full_destination_path(destination_path);
	full_destination_path.append(destination_sub_path);
	std::string full_destination_path_str = full_destination_path.string();
	// wxMessageBox("full_destination_path_str: " + full_destination_path_str);
	wxMessageBox(local_template_str);
	write_file(full_destination_path_str, escape_infix_operators(name) + extension, local_template_str, overwrite_yes_to_all, overwrite_warn, overwrite_no);
}

void GenerateDocs::populate_and_write_example_template(std::string& template_str, const std::string name, const std::string source_path, const std::string destination_path, bool overwrite_yes_to_all, bool overwrite_warn, bool overwrite_no)
{

	wxMessageBox(template_str);
}



// std::vector<std::string> GenerateDocs::scan_directory(const wxString file_path, const wxString directory_name)
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

void GenerateDocs::copy_files(const std::string source_path, const std::string source_sub_path, const std::string destination_path, const std::string destination_sub_path, bool overwrite_yes_to_all, bool overwrite_warn, bool overwrite_no)
{
	std::filesystem::path full_source_path(source_path);
	full_source_path.append(source_sub_path);
	std::string full_source_path_str = full_source_path.string();

	// Check if source directory exists:
	if (!std::filesystem::exists(full_source_path))
	{
		wxMessageBox("Copy files failed to open source dir: " + full_source_path_str);
		return;
	}

	std::filesystem::path full_destination_path(destination_path);
	full_destination_path.append(destination_sub_path);
	std::string full_destination_path_str = full_destination_path.string();

	// First check if directory exists:
	if (!std::filesystem::exists(full_destination_path))
	{
		// If not, create it:
		if (std::filesystem::create_directory(full_destination_path))
		{
			wxMessageBox("Copy files created destination dir: " + full_destination_path_str);
		}
		else
		{
			wxMessageBox("Copy files failed to create destination dir: " + full_destination_path_str);
			return;
		}
	}

	wxMessageBox(full_source_path_str + "\n" + full_destination_path_str);

	std::vector<std::string> source_css_files = scan_directory(full_source_path_str);
	for (const auto& f : source_css_files)
	{
		wxMessageBox(f);
		wxString css_body = read_file(full_source_path_str, f);
		write_file(full_destination_path_str, f, css_body, overwrite_yes_to_all, overwrite_warn, overwrite_no);
	}
}

void GenerateDocs::copy_binary_files(const std::string source_path, const std::string source_sub_path, const std::string destination_path, const std::string destination_sub_path, bool overwrite_yes_to_all, bool overwrite_warn, bool overwrite_no)
{
	std::filesystem::path full_source_path(source_path);
	full_source_path.append(source_sub_path);
	std::string full_source_path_str = full_source_path.string();

	// Check if source directory exists:
	if (!std::filesystem::exists(full_source_path))
	{
		wxMessageBox("Copy files failed to open source dir: " + full_source_path_str);
		return;
	}

	std::filesystem::path full_destination_path(destination_path);
	full_destination_path.append(destination_sub_path);
	std::string full_destination_path_str = full_destination_path.string();

	// First check if directory exists:
	if (!std::filesystem::exists(full_destination_path))
	{
		// If not, create it:
		if (std::filesystem::create_directory(full_destination_path))
		{
			wxMessageBox("Copy files created destination dir: " + full_destination_path_str);
		}
		else
		{
			wxMessageBox("Copy files failed to create destination dir: " + full_destination_path_str);
			return;
		}
	}

	wxMessageBox(full_source_path_str + "\n" + full_destination_path_str);

	std::vector<std::string> source_files = scan_directory(full_source_path_str);
	for (const auto& f : source_files)
	{
		wxMessageBox(f);
		std::filesystem::path source_file(full_source_path);
		source_file.append(f);

		std::filesystem::path destination_file(full_destination_path);
		destination_file.append(f);

		std::error_code ec;

		if (overwrite_yes_to_all)
		{
			std::filesystem::copy_file(source_file, destination_file, std::filesystem::copy_options::overwrite_existing, ec);
		}
		else if (overwrite_warn)
		{
			if (std::filesystem::exists(destination_file))
			{
				wxMessageDialog* dlg = new wxMessageDialog(NULL, "Do you want to overwrite file: " + destination_file.string() + "?", "Overwrite File", wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
				if (dlg->ShowModal() == wxID_YES)
				{
					std::filesystem::copy_file(source_file, destination_file, std::filesystem::copy_options::overwrite_existing, ec);
					wxMessageBox("File overwritten");
				}
				else
				{
					wxMessageBox("File skipped");
				}
			}
			else
			{
				std::filesystem::copy_file(source_file, destination_file, std::filesystem::copy_options::skip_existing, ec);
			}
		}
		else if (overwrite_no)
		{
			std::filesystem::copy_file(source_file, destination_file, std::filesystem::copy_options::skip_existing, ec);
		}
	}
}

GenerateDocs::~GenerateDocs()
{}
