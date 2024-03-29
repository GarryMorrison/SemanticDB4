//
// Semantic DB 4
// Created 2023/4/19
// Updated 2023/4/21
// Author Garry Morrison
// License GPL v3
//

#include "GenerateDocs2.h"

// Constructor:
GenerateDocs2::GenerateDocs2(bool overwrite_yes_to_all, bool overwrite_warn, bool overwrite_dont_warn, std::string template_path, std::string examples_path, std::string destination_path)
{
	std::map<std::string, std::string> settings;
	std::map<std::string, std::string> name_vs_location;

	// Seed our settings map with starting variables:
	settings["$settings-file$"] = "template-settings.txt";
	settings["$overwrite-yes-to-all$"] = bool_to_string(overwrite_yes_to_all);
	settings["$overwrite-warn$"] = bool_to_string(overwrite_warn);
	settings["$overwrite-dont-warn$"] = bool_to_string(overwrite_dont_warn);
	settings["$template-path$"] = template_path;
	settings["$examples-path$"] = examples_path;
	settings["$destination-path$"] = destination_path;

	
	// Get and store the current date:
	wxDateTime current_date = current_date.UNow();
	settings["$creation-date$"] = current_date.FormatISODate().ToStdString();

	// Now load settings from file (we make use of $settings-file$ in this function):
	populate_settings(settings);

	// Load data into $menu-structure$, and object vs locations:
	populate_menu(settings, name_vs_location);

	// Use $menu-structure$ and $creation-date$ to fill out our index page, and then write to the destination file:
	populate_and_write_index(settings, name_vs_location);

	// Fill out and write our operator usage pages to the desired locations (specified in name_vs_location map):
	populate_and_write_operators(settings, name_vs_location);

	// Fill out and write our sw example pages to the desired locations (specified in name_vs_location map):
	populate_and_write_examples(settings, name_vs_location);

	// Copy our required helper files:
	copy_css_and_images(settings);
}

void GenerateDocs2::populate_settings(std::map<std::string, std::string>& settings)
{
	std::string template_path = settings["$template-path$"];
	std::string settings_file = settings["$settings-file$"];
	wxFileName tmp_file(template_path, settings_file);
	wxTextFile tfile(tmp_file.GetFullPath());
	if (!tfile.Exists())
	{
		wxMessageBox("In populate-settings, paths file:\n" + tmp_file.GetFullPath() + "\ndoes not exist!");
	}
	else
	{
		tfile.Open();
		std::vector<std::string> element_paths_vec = split_on_first(tfile.GetFirstLine().ToStdString(), " ");
		if (element_paths_vec.size() == 2)
		{
			std::string element = element_paths_vec[0];
			std::string path = element_paths_vec[1];
			settings[element] = normalize_path_separator(path);
		}
		while (!tfile.Eof())
		{
			element_paths_vec = split_on_first(tfile.GetNextLine().ToStdString(), " ");
			if (element_paths_vec.size() == 2)
			{
				std::string element = element_paths_vec[0];
				std::string path = element_paths_vec[1];
				settings[element] = normalize_path_separator(path);
			}
		}
	}
}

void GenerateDocs2::populate_menu(std::map<std::string, std::string>& settings, std::map<std::string, std::string>& name_vs_location)
{
	// Load our variables:
	std::string template_path = settings["$template-path$"];
	std::string examples_path = settings["$examples-path$"];
	std::string list_element_template = settings["$list-element-template$"];
	std::string menu_template = settings["$menu-template$"];

	std::string menu_template_string = read_text_file(template_path, menu_template);
	settings["$list-element-string$"] = strip_trailing_white_space(read_text_file(template_path, list_element_template));

	std::vector<std::string> sw_files = scan_directory(examples_path);
	
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-language-elements-statements-list$", "$menu-language-elements-statements-path$", fn_map.list_of_statements);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-language-elements-learn-rules-list$", "$menu-language-elements-learn-rules-path$", fn_map.list_of_learn_rules_spaces);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-language-elements-infix-type-1-list$", "$menu-language-elements-infix-type-1-path$", fn_map.list_of_infix_type1_spaces);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-language-elements-infix-type-2-list$", "$menu-language-elements-infix-type-2-path$", fn_map.list_of_infix_type2_spaces);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-language-elements-miscellaneous-elements-list$", "$menu-language-elements-miscellaneous-elements-path$", fn_map.list_of_misc_elements);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-language-elements-object-types-list$", "$menu-language-elements-object-types-path$", fn_map.list_of_object_types);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-language-elements-operator-types-list$", "$menu-language-elements-operator-types-path$", fn_map.list_of_operator_types);

	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-core-normal-list$", "$menu-operators-core-normal-path$", fn_map.set_built_in);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-core-compound-list$", "$menu-operators-core-compound-path$", fn_map.set_compound_built_in);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-core-compound-context-list$", "$menu-operators-core-compound-context-path$", fn_map.set_compound_context_built_in);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-sigmoid-normal-list$", "$menu-operators-sigmoid-normal-path$", fn_map.set_sigmoids);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-sigmoid-compound-list$", "$menu-operators-sigmoid-compound-path$", fn_map.set_compound_sigmoids);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-ket-normal-list$", "$menu-operators-ket-normal-path$", fn_map.set_ket_fn);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-ket-compound-list$", "$menu-operators-ket-compound-path$", fn_map.set_compound_ket_fn);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-ket-context-list$", "$menu-operators-ket-context-path$", fn_map.set_context_ket_fn);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-superposition-normal-list$", "$menu-operators-superposition-normal-path$", fn_map.set_sp_fn);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-superposition-compound-list$", "$menu-operators-superposition-compound-path$", fn_map.set_compound_sp_fn);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-superposition-compound-context-list$", "$menu-operators-superposition-compound-context-path$", fn_map.set_compound_context_sp_fn);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-sequence-normal-list$", "$menu-operators-sequence-normal-path$", fn_map.set_seq_fn);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-sequence-context-list$", "$menu-operators-sequence-context-path$", fn_map.set_context_seq_fn);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-sequence-compound-list$", "$menu-operators-sequence-compound-path$", fn_map.set_compound_seq_fn);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-sequnece-compound-context-list$", "$menu-operators-sequence-compound-context-path$", fn_map.set_compound_context_seq_fn);

	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-function-normal-1-parameter-list$", "$menu-operators-function-normal-1-parameter-path$", fn_map.set_whitelist_1);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-function-normal-2-parameter-list$", "$menu-operators-function-normal-2-parameter-path$", fn_map.set_whitelist_2);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-function-normal-3-parameter-list$", "$menu-operators-function-normal-3-parameter-path$", fn_map.set_whitelist_3);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-function-normal-4-parameter-list$", "$menu-operators-function-normal-4-parameter-path$", fn_map.set_whitelist_4);

	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-function-context-1-parameter-list$", "$menu-operators-function-context-1-parameter-path$", fn_map.set_context_whitelist_1);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-function-context-2-parameter-list$", "$menu-operators-function-context-2-parameter-path$", fn_map.set_context_whitelist_2);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-function-context-3-parameter-list$", "$menu-operators-function-context-3-parameter-path$", fn_map.set_context_whitelist_3);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-function-context-4-parameter-list$", "$menu-operators-function-context-4-parameter-path$", fn_map.set_context_whitelist_4);
	
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-all-simple-list$", "$menu-operators-all-simple-path$", fn_map.set_simple_operators);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-all-compound-list$", "$menu-operators-all-compound-path$", fn_map.set_compound_operators);
	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-operators-all-function-list$", "$menu-operators-all-function-path$", fn_map.set_function_operators);

	generate_list_and_populate_name_vs_location(settings, name_vs_location, "$menu-examples-list$", "$menu-examples-path$", sw_files);

	string_replace_all(menu_template_string, "$menu-language-elements-statements-list$", settings["$menu-language-elements-statements-list$"]);
	string_replace_all(menu_template_string, "$menu-language-elements-learn-rules-list$", settings["$menu-language-elements-learn-rules-list$"]);
	string_replace_all(menu_template_string, "$menu-language-elements-infix-type-1-list$", settings["$menu-language-elements-infix-type-1-list$"]);
	string_replace_all(menu_template_string, "$menu-language-elements-infix-type-2-list$", settings["$menu-language-elements-infix-type-2-list$"]);
	string_replace_all(menu_template_string, "$menu-language-elements-miscellaneous-elements-list$", settings["$menu-language-elements-miscellaneous-elements-list$"]);
	string_replace_all(menu_template_string, "$menu-language-elements-object-types-list$", settings["$menu-language-elements-object-types-list$"]);
	string_replace_all(menu_template_string, "$menu-language-elements-operator-types-list$", settings["$menu-language-elements-operator-types-list$"]);

	string_replace_all(menu_template_string, "$menu-operators-core-normal-list$", settings["$menu-operators-core-normal-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-core-compound-list$", settings["$menu-operators-core-compound-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-core-compound-context-list$", settings["$menu-operators-core-compound-context-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-sigmoid-normal-list$", settings["$menu-operators-sigmoid-normal-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-sigmoid-compound-list$", settings["$menu-operators-sigmoid-compound-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-ket-normal-list$", settings["$menu-operators-ket-normal-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-ket-compound-list$", settings["$menu-operators-ket-compound-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-ket-context-list$", settings["$menu-operators-ket-context-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-superposition-normal-list$", settings["$menu-operators-superposition-normal-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-superposition-compound-list$", settings["$menu-operators-superposition-compound-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-superposition-compound-context-list$", settings["$menu-operators-superposition-compound-context-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-sequence-normal-list$", settings["$menu-operators-sequence-normal-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-sequence-context-list$", settings["$menu-operators-sequence-context-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-sequence-compound-list$", settings["$menu-operators-sequence-compound-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-sequence-compound-context-list$", settings["$menu-operators-sequence-compound-context-list$"]);

	string_replace_all(menu_template_string, "$menu-operators-function-normal-1-parameter-list$", settings["$menu-operators-function-normal-1-parameter-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-function-normal-2-parameter-list$", settings["$menu-operators-function-normal-2-parameter-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-function-normal-3-parameter-list$", settings["$menu-operators-function-normal-3-parameter-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-function-normal-4-parameter-list$", settings["$menu-operators-function-normal-4-parameter-list$"]);
	
	string_replace_all(menu_template_string, "$menu-operators-function-context-1-parameter-list$", settings["$menu-operators-function-context-1-parameter-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-function-context-2-parameter-list$", settings["$menu-operators-function-context-2-parameter-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-function-context-3-parameter-list$", settings["$menu-operators-function-context-3-parameter-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-function-context-4-parameter-list$", settings["$menu-operators-function-context-4-parameter-list$"]);

	string_replace_all(menu_template_string, "$menu-operators-all-simple-list$", settings["$menu-operators-all-simple-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-all-compound-list$", settings["$menu-operators-all-compound-list$"]);
	string_replace_all(menu_template_string, "$menu-operators-all-function-list$", settings["$menu-operators-all-function-list$"]);

	string_replace_all(menu_template_string, "$menu-examples-list$", settings["$menu-examples-list$"]);
	string_replace_all(menu_template_string, "$menu-website-link$", settings["$menu-website-link$"]);
	string_replace_all(menu_template_string, "$menu-github-link$", settings["$menu-github-link$"]);


	settings["$menu-structure$"] = menu_template_string;
}

void GenerateDocs2::populate_and_write_index(std::map<std::string, std::string>& settings, std::map<std::string, std::string>& name_vs_location)
{
	// Load our variables:
	std::string template_path = settings["$template-path$"];
	std::string destination_path = settings["$destination-path$"];
	std::string destination_css_path = settings["$destination-css-path$"];
	std::string destination_image_path = settings["$destination-image-path$"];
	bool overwrite_yes_to_all = string_to_bool(settings["$overwrite-yes-to-all$"]);
	bool overwrite_warn = string_to_bool(settings["$overwrite-warn$"]);
	bool overwrite_dont_warn = string_to_bool(settings["$overwrite-dont-warn$"]);

	std::string index_template = settings["$index-template$"];
	std::string destination_index_file_name = settings["$destination-index-file-name$"];
	std::string index_str = read_text_file(template_path, index_template);

	// Now write them into our index file:
	string_replace_all(index_str, "$menu-structure$", settings["$menu-structure$"]);
	string_replace_all(index_str, "$inverse-path$", "");
	string_replace_all(index_str, "$destination-css-path$", settings["$destination-css-path$"]);
	string_replace_all(index_str, "$destination-image-path$", settings["$destination-image-path$"]);
	string_replace_all(index_str, "$creation-date$", settings["$creation-date$"]);
	wxMessageBox(index_str);
	write_text_file(destination_path, destination_index_file_name, index_str, overwrite_yes_to_all, overwrite_warn, overwrite_dont_warn);
}

void GenerateDocs2::populate_and_write_operators(std::map<std::string, std::string>& settings, std::map<std::string, std::string>& name_vs_location)
{
	// Load our variables:
	std::string template_path = settings["$template-path$"];
	std::string destination_path = settings["$destination-path$"];
	std::string destination_css_path = settings["$destination-css-path$"];
	std::string destination_image_path = settings["$destination-image-path$"];
	std::string destination_file_extension = settings["$destination-file-extension$"];
	bool overwrite_yes_to_all = string_to_bool(settings["$overwrite-yes-to-all$"]);
	bool overwrite_warn = string_to_bool(settings["$overwrite-warn$"]);
	bool overwrite_dont_warn = string_to_bool(settings["$overwrite-dont-warn$"]);
	bool escape_html = string_to_bool(settings["$html-escape-operator-fields$"]);
	bool linkify_operator_example_field = string_to_bool(settings["$linkify-operator-example-field$"]);
	bool linkify_operator_see_also_field = string_to_bool(settings["$linkify-operator-see-also-field$"]);

	std::string operator_template = settings["$operator-template$"];
	std::string operator_str = read_text_file(template_path, operator_template);

	// Now write into our template string the variables that are universal to all operators:
	string_replace_all(operator_str, "$menu-structure$", settings["$menu-structure$"]);
	string_replace_all(operator_str, "$destination-index-file-name$", settings["$destination-index-file-name$"]);
	string_replace_all(operator_str, "$destination-css-path$", settings["$destination-css-path$"]);
	string_replace_all(operator_str, "$destination-image-path$", settings["$destination-image-path$"]);
	string_replace_all(operator_str, "$creation-date$", settings["$creation-date$"]);

	// int loop_count = 0;
	// int max_count = 2;
	for (const auto& it : name_vs_location)
	{
		std::string name = it.first;
		std::string location = it.second;
		std::string inverse_path = get_inverse_path(location);
		std::string local_operator_str = operator_str;

		if (name.empty())
		{
			continue;
		}

		if (!operator_usage_map.usage_is_defined(name))
		{
			if (fn_map.list_of_operator_and_statement_names.find(name) != fn_map.list_of_operator_and_statement_names.end()) // This should filter out sw examples.
			{
				wxMessageBox("No usage info available for operator: " + name);
			}
			continue;
		}
		OpUsageInfo* usageInfo = operator_usage_map.get_usage_info(name);
		if (!usageInfo)
		{
			wxMessageBox("No usage info found for: " + name);
			continue;
		}
		string_replace_all(local_operator_str, "$inverse-path$", inverse_path);
		string_replace_all(local_operator_str, "$operator-name$", escape_html_chars(name, escape_html));
		string_replace_all(local_operator_str, "$operator-description$", escape_html_chars(usageInfo->Description, escape_html));
		string_replace_all(local_operator_str, "$operator-examples$", html_linkify_and_escape(usageInfo->Examples, inverse_path, settings, name_vs_location, linkify_operator_example_field, escape_html));
		string_replace_all(local_operator_str, "$operator-see-also$", html_linkify_and_escape(usageInfo->SeeAlso, inverse_path, settings, name_vs_location, linkify_operator_see_also_field, escape_html));

		std::string operator_types_str = join(fn_map.get_operator_types(name), ", ");
		string_replace_all(local_operator_str, "$operator-type$", operator_types_str);

		// wxMessageBox(local_operator_str);

		// Now write it to disk:
		std::filesystem::path full_destination_path(destination_path);
		full_destination_path.append(location);
		std::string filename = escape_infix_operators(name) + destination_file_extension;
		// wxMessageBox("full destination path: " + full_destination_path.string() + "\nfilename: " + filename);

		write_text_file(full_destination_path.string(), filename, local_operator_str, overwrite_yes_to_all, overwrite_warn, overwrite_dont_warn);

		/*
		if (loop_count >= max_count)
		{
			break;
		}
		loop_count++;
		*/
	}

	// wxMessageBox(operator_str);
}

void GenerateDocs2::populate_and_write_examples(std::map<std::string, std::string>& settings, std::map<std::string, std::string>& name_vs_location)
{
	// Load our variables:
	std::string template_path = settings["$template-path$"];
	std::string examples_path = settings["$examples-path$"];
	std::string destination_path = settings["$destination-path$"];
	std::string destination_css_path = settings["$destination-css-path$"];
	std::string destination_image_path = settings["$destination-image-path$"];
	std::string destination_file_extension = settings["$destination-file-extension$"];
	bool overwrite_yes_to_all = string_to_bool(settings["$overwrite-yes-to-all$"]);
	bool overwrite_warn = string_to_bool(settings["$overwrite-warn$"]);
	bool overwrite_dont_warn = string_to_bool(settings["$overwrite-dont-warn$"]);
	bool escape_html = string_to_bool(settings["$html-escape-example-fields$"]);
	bool linkify = string_to_bool(settings["$linkify-example-body-field$"]);
	bool strip_name_extension = string_to_bool(settings["$strip-extensions-for-menu-items$"]);

	if (examples_path.empty())  // Directory not specified, so can't load our examples.
	{
		return;
	}

	std::string example_template = settings["$example-template$"];
	std::string example_str = read_text_file(template_path, example_template);
	std::vector<std::string> sw_files = scan_directory(examples_path);

	if (sw_files.empty())  // If no files in the given directory, we can't do anything, so return.
	{
		return;
	}

	// Now write into our template string the variables that are universal to all operators:
	string_replace_all(example_str, "$menu-structure$", settings["$menu-structure$"]);
	string_replace_all(example_str, "$destination-index-file-name$", settings["$destination-index-file-name$"]);
	string_replace_all(example_str, "$destination-css-path$", settings["$destination-css-path$"]);
	string_replace_all(example_str, "$destination-image-path$", settings["$destination-image-path$"]);
	string_replace_all(example_str, "$creation-date$", settings["$creation-date$"]);

	// int loop_count = 0;
	// int max_count = 5;
	for (const auto& name : sw_files)
	{
		std::string local_example_str = example_str;
		std::string reference_name = name;
		if (strip_name_extension)
		{
			reference_name = strip_extension(name);
		}
		std::string location = name_vs_location[reference_name];  // Yeah, all examples should have the same path, but just in case we load from our map.
		std::string inverse_path = get_inverse_path(location);
		std::string raw_example_body = read_text_file(examples_path, name);
		std::string example_body = html_linkify_and_escape(raw_example_body, inverse_path, settings, name_vs_location, linkify, escape_html);

		string_replace_all(local_example_str, "$inverse-path$", inverse_path);
		string_replace_all(local_example_str, "$example-name$", reference_name);
		string_replace_all(local_example_str, "$example-body$", example_body);
		string_replace_all(local_example_str, "$example-link-to-raw-file$", name);

		// wxMessageBox(local_example_str);

		// Now write it to disk:
		std::filesystem::path full_destination_path(destination_path);
		full_destination_path.append(location);
		std::string filename = reference_name + destination_file_extension;
		// wxMessageBox("full destination path: " + full_destination_path.string() + "\nfilename: " + filename);

		write_text_file(full_destination_path.string(), filename, local_example_str, overwrite_yes_to_all, overwrite_warn, overwrite_dont_warn);
		write_text_file(full_destination_path.string(), name, raw_example_body, overwrite_yes_to_all, overwrite_warn, overwrite_dont_warn);

		/*
		if (loop_count >= max_count)
		{
			break;
		}
		loop_count++;
		*/
	}

	// wxMessageBox(example_str);
}

void GenerateDocs2::copy_css_and_images(std::map<std::string, std::string>& settings)
{
	// Load our variables:
	std::string template_path = settings["$template-path$"];
	std::string source_css_path = settings["$source-css-path$"];
	std::string source_image_path = settings["$source-image-path$"];
	std::string destination_path = settings["$destination-path$"];
	std::string destination_css_path = settings["$destination-css-path$"];
	std::string destination_image_path = settings["$destination-image-path$"];
	bool overwrite_yes_to_all = string_to_bool(settings["$overwrite-yes-to-all$"]);
	bool overwrite_warn = string_to_bool(settings["$overwrite-warn$"]);
	bool overwrite_dont_warn = string_to_bool(settings["$overwrite-dont-warn$"]);

	// Copy css files:
	copy_binary_files(template_path, source_css_path, destination_path, destination_css_path, overwrite_yes_to_all, overwrite_warn, overwrite_dont_warn);

	// Copy image files:
	copy_binary_files(template_path, source_image_path, destination_path, destination_image_path, overwrite_yes_to_all, overwrite_warn, overwrite_dont_warn);
}

void GenerateDocs2::generate_list_and_populate_name_vs_location(std::map<std::string, std::string>& settings, std::map<std::string, std::string>& name_vs_location, const std::string list_var, const std::string path_var, std::vector<std::string>& object_vec)
{
	// Load our variables:
	std::string list_element_string = settings["$list-element-string$"];
	std::string path = settings[path_var];
	bool strip_name_extension = string_to_bool(settings["$strip-extensions-for-menu-items$"]);
	bool html_escape_menu_item = string_to_bool(settings["$html-escape-menu-items$"]);

	// string_replace_all(list_element_string, "$object-reference-path$", path);
	string_replace_all(list_element_string, "$object-reference-extension$", settings["$destination-file-extension$"]);

	std::string list;

	// Loop through our vector:
	for (const auto& name : object_vec)
	{
		std::string local_list_element_string = list_element_string;
		std::string reference_name = name;
		if (strip_name_extension)
		{
			reference_name = smart_strip_extension(name);
		}
		std::string label_name = reference_name;
		if (html_escape_menu_item)
		{
			label_name = escape_html_chars(reference_name);
		}
		string_replace_all(local_list_element_string, "$object-label-name$", label_name);
		string_replace_all(local_list_element_string, "$object-reference-name$", escape_infix_operators(reference_name));

		// If name is not already in the name vs location map, then insert it:
		// This is so we only save an object to one file location.
		if (name_vs_location.find(reference_name) == name_vs_location.end())
		{
			name_vs_location[reference_name] = path;
		}
		string_replace_all(local_list_element_string, "$object-reference-path$", name_vs_location[reference_name]);

		list += "\n" + local_list_element_string;
	}
	// wxMessageBox(list);
	settings[list_var] = list;
}

void GenerateDocs2::generate_list_and_populate_name_vs_location(std::map<std::string, std::string>& settings, std::map<std::string, std::string>& name_vs_location, const std::string list_var, const std::string path_var, std::set<ulong>& object_set)
{
	std::vector<std::string> object_vec;
	for (ulong idx : object_set)
	{
		std::string name = ket_map.get_str(idx);
		object_vec.push_back(name);
	}
	
	std::sort(object_vec.begin(), object_vec.end());  // Sort object vector.
	generate_list_and_populate_name_vs_location(settings, name_vs_location, list_var, path_var, object_vec);
}

std::string GenerateDocs2::bool_to_string(bool value)
{
	if (value)
	{
		return "yes";
	}
	return "no";
}

bool GenerateDocs2::string_to_bool(const std::string s)
{
	if (s == "yes")
	{
		return true;
	}
	return false;
}

std::string GenerateDocs2::normalize_path_separator(const std::string source_path)
{
	std::filesystem::path windows_path(source_path);
	return windows_path.make_preferred().string();
}

std::string GenerateDocs2::get_inverse_path(const std::string source_path)
{
	if (source_path.empty())
	{
		return source_path;
	}

	// Remove trailing directory separator:
	std::string directory = source_path;
	while ((directory.back() == '/') || (directory.back() == '\\'))
	{
		directory.erase(directory.size() - 1);
	}
	
	std::filesystem::path sub_path(directory);
	std::filesystem::path inverse_sub_path;
	for (const auto& p : sub_path)
	{
		inverse_sub_path.append("..");
	}
	return inverse_sub_path.string() + normalize_path_separator("/");
}

std::string GenerateDocs2::strip_extension(const std::string our_filename)
{
	std::filesystem::path file_name(our_filename);
	file_name.replace_extension("");
	return file_name.string();
}

std::string GenerateDocs2::smart_strip_extension(const std::string our_filename)
{
	if (our_filename != escape_infix_operators(our_filename))  // A little hackish, but should do the job!
	{
		return our_filename;
	}
	std::filesystem::path file_name(our_filename);
	file_name.replace_extension("");
	return file_name.string();
}

std::vector<std::string> GenerateDocs2::scan_directory(const std::string directory_name)
{
	std::vector<std::string> directory_list;
	if (directory_name.empty())  // If directory name is not specified we can't do anything, so return the empty vector.
	{
		return directory_list;
	}

	wxDir our_sw_dir(directory_name);
	if (!our_sw_dir.IsOpened())
	{
		wxMessageBox("Scan directory, directory: \"" + directory_name + "\" does not exist!");
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

void GenerateDocs2::write_text_file(const std::string& file_path, const std::string& file_name, const std::string& file_body, bool overwrite_yes_to_all, bool overwrite_warn, bool overwrite_no)
{
	if (!wxFileName::Mkdir(file_path, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL))
	{
		wxMessageBox("Write text file failed to create directory: " + file_path);
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
		// wxMessageBox("Will overwrite file");
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
	if (overwrite_no && tfile.Exists())
	{
		// wxMessageBox("Will not overwrite file");
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
		std::vector<std::string> lines = split(file_body, "\n");
		for (const auto& line : lines)
		{
			tfile.AddLine(line);
		}
		tfile.Write();
		tfile.Close();
	}
}

std::string GenerateDocs2::read_text_file(const std::string& file_path, const std::string& file_name)
{
	wxFileName working_file(file_path, file_name);
	wxTextFile tfile(working_file.GetFullPath());

	wxString file_text;
	if (!tfile.Exists())
	{
		wxMessageBox("Read text file error, file:\n" + file_name + "\ndoes not exist!");
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
	return file_text.ToStdString();
}

void GenerateDocs2::copy_binary_files(const std::string source_path, const std::string source_sub_path, const std::string destination_path, const std::string destination_sub_path, bool overwrite_yes_to_all, bool overwrite_warn, bool overwrite_no)
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


std::string GenerateDocs2::escape_infix_operators(const std::string& raw_string)
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

std::string GenerateDocs2::escape_html_chars(const std::string& source, bool invoke)
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

std::string GenerateDocs2::strip_trailing_white_space(const std::string source, const char* t)
{
	std::string s = source;
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}


std::string GenerateDocs2::html_linkify_and_escape(const std::string& source, const std::string& inverse_path, std::map<std::string, std::string>& settings, std::map<std::string, std::string>& name_vs_location, bool linkify, bool escape)
{
	// Handle a couple of easy cases:
	if (!linkify && !escape)
	{
		return source;
	}
	if (!linkify && escape)
	{
		return escape_html_chars(source, true);
	}

	// Load our variables:
	std::string template_path = settings["$template-path$"];
	std::string linkify_template = settings["$linkify-template$"];
	std::string destination_file_extension = settings["$destination-file-extension$"];

	std::string linkify_template_str = strip_trailing_white_space(read_text_file(template_path, linkify_template));

	if (linkify_template_str.empty())  // If we don't have a linkify-template we can't do any processing of the source text, so return it.
	{
		return source;
	}

	string_replace_all(linkify_template_str, "$inverse-path$", inverse_path);
	string_replace_all(linkify_template_str, "$object-reference-extension$", destination_file_extension);

	std::set<char> split_chars = { ' ', ',', '\n', '[', '(' };
	std::vector<std::string> tokens = split_on_chars(source, split_chars);  // Split our source text into tokens.

	std::string result;
	for (const auto& token : tokens)
	{
		if (token.empty())  // Just a guard, so we don't do token[0] on a zero length string.
		{
			continue;
		}
		if (split_chars.find(token[0]) != split_chars.end())
		{
			result += token;  // We don't need to html escape the split chars, since < or > are not members.
			continue;
		}
		if (name_vs_location.find(token) != name_vs_location.end())
		{
			std::string local_linkify_template_str = linkify_template_str;
			string_replace_all(local_linkify_template_str, "$object-reference-path$", normalize_path_separator(name_vs_location[token]));
			string_replace_all(local_linkify_template_str, "$object-reference-name$", escape_infix_operators(token));
			string_replace_all(local_linkify_template_str, "$object-label-name$", escape_html_chars(token, escape));
			result += local_linkify_template_str;
		} else if (name_vs_location.find(" " + token + " ") != name_vs_location.end())
		{
			std::string local_linkify_template_str = linkify_template_str;
			std::string token2 = " " + token + " ";
			string_replace_all(local_linkify_template_str, "$object-reference-path$", normalize_path_separator(name_vs_location[token2]));
			string_replace_all(local_linkify_template_str, "$object-reference-name$", escape_infix_operators(token2));
			string_replace_all(local_linkify_template_str, "$object-label-name$", escape_html_chars(token, escape));
			result += local_linkify_template_str;
		}
		else
		{
			result += escape_html_chars(token, escape);
		}
	}

	return result;
}

// Destructor:
GenerateDocs2::~GenerateDocs2()
{
}
