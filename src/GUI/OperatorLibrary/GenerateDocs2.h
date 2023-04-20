//
// Semantic DB 4
// Created 2023/4/19
// Updated 2023/4/19
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../../SDB.h"
#include <map>
#include <filesystem>
#include <algorithm>
#include <wx/datetime.h>
#include <wx/dir.h>
#include <wx/msgdlg.h>
#include <wx/tokenzr.h>


class GenerateDocs2
{
public:
    // Constructor:
    GenerateDocs2(bool overwrite_yes_to_all, bool overwrite_warn, bool overwrite_dont_warn, std::string template_path, std::string examples_path, std::string destination_path);

    // Destructor:
    ~GenerateDocs2();
private:
    void populate_settings(std::map<std::string, std::string>& settings);
    void populate_menu(std::map<std::string, std::string>& settings, std::map<std::string, std::string>& name_vs_location);
    void populate_and_write_index(std::map<std::string, std::string>& settings, std::map<std::string, std::string>& name_vs_location);
    void populate_and_write_operators(std::map<std::string, std::string>& settings, std::map<std::string, std::string>& name_vs_location);
    void populate_and_write_examples(std::map<std::string, std::string>& settings, std::map<std::string, std::string>& name_vs_location);
    void copy_css_and_images(std::map<std::string, std::string>& settings);
    void generate_list_and_populate_name_vs_location(std::map<std::string, std::string>& settings, std::map<std::string, std::string>& name_vs_location, const std::string list_var, const std::string path_var, std::vector<std::string>& object_vec);
    void generate_list_and_populate_name_vs_location(std::map<std::string, std::string>& settings, std::map<std::string, std::string>& name_vs_location, const std::string list_var, const std::string path_var, std::set<ulong>& object_set);

    std::string bool_to_string(bool value);
    bool string_to_bool(const std::string s);

    std::string normalize_path_separator(const std::string source_path);
    std::string get_inverse_path(const std::string source_path);
    std::string strip_extension(const std::string our_filename);

    std::vector<std::string> scan_directory(const std::string directory_name);
    void write_text_file(const std::string& file_path, const std::string& file_name, const std::string& file_body, bool overwrite_yes_to_all, bool overwrite_warn, bool overwrite_no);
    std::string read_text_file(const std::string& file_path, const std::string& file_name);
    void copy_binary_files(const std::string source_path, const std::string source_sub_path, const std::string destination_path, const std::string destination_sub_path, bool overwrite_yes_to_all, bool overwrite_warn, bool overwrite_no);

    std::string escape_infix_operators(const std::string& raw_string);
    std::string escape_html_chars(const std::string& source, bool invoke = true);
};

