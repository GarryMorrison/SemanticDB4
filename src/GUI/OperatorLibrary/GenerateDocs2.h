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
#include <wx/datetime.h>


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

    std::string bool_to_string(bool value);
    bool string_to_bool(const std::string s);

    std::string normalize_path_separator(const std::string source_path);
    std::string get_inverse_path(const std::string source_path);
    std::string strip_extension(const std::string our_filename);

    std::vector<std::string> scan_directory(const std::string directory_name);
    void copy_binary_files(const std::string source_path, const std::string source_sub_path, const std::string destination_path, const std::string destination_sub_path, bool overwrite_yes_to_all, bool overwrite_warn, bool overwrite_no);
};

