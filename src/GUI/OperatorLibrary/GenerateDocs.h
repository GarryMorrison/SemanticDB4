//
// Semantic DB 4
// Created 2023/4/12
// Updated 2023/4/14
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../../SDB.h"
#include <wx/datetime.h>
#include <wx/textfile.h>
#include <wx/dir.h>
#include <map>
#include <filesystem>
#include <wx/msgdlg.h>
#include <wx/tokenzr.h>

class GenerateDocs
{
public:
    // Constructor:
    // GenerateDocs(bool text, bool html, bool linkify, bool yes_to_all, bool warn, bool dont_warn, wxString template_path, wxString examples_path, wxString destination_path);
    GenerateDocs(bool yes_to_all, bool warn, bool dont_warn, wxString template_path, wxString examples_path, wxString destination_path);

    // Destructor:
    ~GenerateDocs();
private:
    std::string normalize_path_separator(const std::string source_path);
    std::map<std::string, std::string> populate_settings_map(wxString template_path, wxString settings_file);

    wxString read_file(const wxString our_filename);
    wxString read_file(const wxString file_path, const wxString file_name);
    void write_file(const wxString file_path, const wxString file_name, const wxString file_body, bool overwrite_yes_to_all, bool overwrite_warn, bool overwrite_no);
    std::string escape_infix_operators(const std::string& raw_string);
    std::string escape_html_chars(const std::string& source);
    std::string generate_list(const std::vector<std::string>& list_of_elements, const std::string& list_element_template);
    void populate_list(std::string& file_contents, const std::string list_element, const std::vector<std::string>& list_of_elements, const std::map<std::string, std::string>& paths_map, const std::string list_element_template_str, const std::string extension, bool strip_extension_bool = false);
    std::vector<std::string> scan_directory(const wxString directory_name);
    // std::vector<std::string> scan_directory(const wxString file_path, const wxString directory_name);
    wxString strip_extension(const wxString our_filename);

    void copy_files(const std::string source_path, const std::string source_sub_path, const std::string destination_path, const std::string destination_sub_path, bool overwrite_yes_to_all, bool overwrite_warn, bool overwrite_no);
    void copy_binary_files(const std::string source_path, const std::string source_sub_path, const std::string destination_path, const std::string destination_sub_path, bool overwrite_yes_to_all, bool overwrite_warn, bool overwrite_no);
};

