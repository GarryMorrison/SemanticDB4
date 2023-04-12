//
// Semantic DB 4
// Created 2023/4/12
// Updated 2023/4/12
// Author Garry Morrison
// License GPL v3
//

#pragma once
#include "../../SDB.h"
#include <wx/datetime.h>
#include <wx/textfile.h>

class GenerateDocs
{
public:
    // Constructor:
    GenerateDocs(bool text, bool html, bool linkify, bool yes_to_all, bool warn, bool dont_warn, wxString template_path, wxString examples_path, wxString destination_path);

    // Destructor:
    ~GenerateDocs();
private:

    wxString read_file(const wxString our_filename);
    std::string escape_html_chars(const std::string& source);
    std::string generate_list(const std::vector<std::string>& list_of_elements, const std::string& list_element_template);
};
