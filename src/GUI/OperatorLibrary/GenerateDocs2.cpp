//
// Semantic DB 4
// Created 2023/4/19
// Updated 2023/4/19
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
	settings["$overwrite-warn"] = bool_to_string(overwrite_warn);
	settings["$overwrite-dont-warn$"] = bool_to_string(overwrite_dont_warn);
	settings["$template-path$"] = template_path;
	settings["$examples-path$"] = examples_path;
	settings["$destination-path$"] = destination_path;

	// Get and store the current date:
	wxDateTime current_date = current_date.UNow();
	settings["$current-date$"] = current_date.FormatISODate().ToStdString();

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

}

void GenerateDocs2::populate_and_write_index(std::map<std::string, std::string>& settings, std::map<std::string, std::string>& name_vs_location)
{

}

void GenerateDocs2::populate_and_write_operators(std::map<std::string, std::string>& settings, std::map<std::string, std::string>& name_vs_location)
{

}

void GenerateDocs2::populate_and_write_examples(std::map<std::string, std::string>& settings, std::map<std::string, std::string>& name_vs_location)
{

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
	std::filesystem::path sub_path(source_path);
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

std::vector<std::string> GenerateDocs2::scan_directory(const std::string directory_name)
{
	std::vector<std::string> directory_list;
	wxDir our_sw_dir(directory_name);
	if (!our_sw_dir.IsOpened())
	{
		wxMessageBox("Scan directory, directory:\n" + directory_name + "\ndoes not exist!");
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


// Destructor:
GenerateDocs2::~GenerateDocs2()
{
}
