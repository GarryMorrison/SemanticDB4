//
// Semantic DB 4
// Created 2023/6/3
// Updated 2023/6/3
// Author Garry Morrison
// License GPL v3
//


#include <iostream>
#include <fstream>
#include <time.h>
#include <filesystem>
#include <map>
#include <sstream>
#include "DocsGenerator.h"


namespace fs = std::filesystem;

DocsGenerator docs_generator;
extern FunctionOperatorMap fn_map;
extern OperatorUsageMap operator_usage_map;

const std::string docs_index_page =
        "<html>\n"
        "<head>\n"
        "<title>Semantic DB 3.1.1 usage information</title>\n"
        "<style type=\"text/css\">\n"
        " a {text-decoration:none;}\n"
        "</style>\n"
        "</head>\n"
        "<body>\n"
        "<h3>Semantic DB 3.1.1 usage information</h3>\n"
        "Welcome to the Semantic DB 3.1.1 usage page. Below are brief descriptions of the components of the SDB language.\n"
        "The corresponding github repo is <a href=\"https://github.com/GarryMorrison/SemanticDB3.1\">available here</a>.\n"
        // "<hr>\n"
        "$body$\n"
        // "<hr>\n"
        "by Garry Morrison<br>\n"
        "email: garry -at- semantic-db.org<br>\n"
        "updated: $date-time$\n"
        "\n</body>\n</html>\n";

const std::string docs_statement_page =
        "<html>\n"
        "<head>\n"
        "<title>$statement-type$: $statement-name$</title>\n"
        "<style type=\"text/css\">\n"
        " a {text-decoration:none;}\n"
        "pre {\n"
        "\tpadding: 0.1em 0.5em 0.3em 0.7em;\n"
        "\tborder-left: 11px solid #ccc;\n"
        "\tmargin: 1.7em 0 1.7em 0.3em;\n"
        "\toverflow: auto;\n"
        "\twidth: 93%;\n"
        "}\n"
        "</style>\n"
        "</head>\n"
        "<body>\n"
        "<h3>$statement-type$: $statement-name$</h3>\n"
        // "<hr>\n"
        "<pre>\n"
        "$statement-usage$"
        "</pre>\n"
        // "<hr>\n"
        "<a href=\"../index.html\">Home</a><br>\n"
        "</body>\n"
        "</html>";


const std::string docs_operator_page =
        "<html>\n"
        "<head>\n"
        "<title>$operator-type$: $operator-name$</title>\n"
        "<style type=\"text/css\">\n"
        " a {text-decoration:none;}\n"
        "pre {\n"
        "\tpadding: 0.1em 0.5em 0.3em 0.7em;\n"
        "\tborder-left: 11px solid #ccc;\n"
        "\tmargin: 1.7em 0 1.7em 0.3em;\n"
        "\toverflow: auto;\n"
        "\twidth: 93%;\n"
        "}\n"
        "</style>\n"
        "</head>\n"
        "<body>\n"
        "<h3>$operator-type$: $operator-name$</h3>\n"
        // "<hr>\n"
        "<pre>\n"
        "$operator-usage$"
        "</pre>\n"
        // "<hr>\n"
        "<a href=\"../index.html\">Home</a><br>\n"
        "</body>\n"
        "</html>";

const std::string docs_sw3_page =
        "<html>\n"
        "<head>\n"
        "<title>$sw3-type$: $sw3-name$</title>\n"
        "<style type=\"text/css\">\n"
        " a {text-decoration:none;}\n"
        "pre {\n"
        "\tpadding: 0.1em 0.5em 0.3em 0.7em;\n"
        "\tborder-left: 11px solid #ccc;\n"
        "\tmargin: 1.7em 0 1.7em 0.3em;\n"
        "\toverflow: auto;\n"
        "\twidth: 93%;\n"
        "}\n"
        "</style>\n"
        "</head>\n"
        "<body>\n"
        "<h3>$sw3-type$: $sw3-name$</h3>\n"
        "\nRaw file <a href=\"$sw3-name$\">here.</a>\n"
        // "<hr>\n"
        "<pre>"
        "$sw3-code$"
        "</pre>\n"
        // "<hr>\n"
        "<a href=\"../index.html\">Home</a><br>\n"
        "</body>\n"
        "</html>";


std::string escape_infix_operators(const std::string &raw_string) {
    if (raw_string == " + ") { return "infix_plus"; }
    if (raw_string == " - ") { return "infix_minus"; }
    if (raw_string == " _ ") { return "infix_merge"; }
    if (raw_string == " __ ") { return "infix_smerge"; }
    if (raw_string == " :_ ") { return "infix_colon_merge"; }
    if (raw_string == " . ") { return "infix_seq"; }
    if (raw_string == " => ") { return "learn_rule"; }
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

std::string linkify_operators(std::map<std::string, std::string> &operator_locations, const std::string &source_usage) {
    std::string usage = source_usage;  // Just copy it, since we want to modify it in place.
    for (const auto &iter: operator_locations) {
        if (iter.first[0] == ' ' && iter.first.back() == ' ') {  // I'm not convinced we want this. Now we have switched off underlines, yeah, we do.
            std::string new_str = iter.first.substr(1, iter.first.size() - 2);
            std::string html_link = "<a href=\"../" + iter.second + "/" + escape_infix_operators(iter.first) + ".html\">" + new_str + "</a>";
            std::string from = " " + new_str + " ";
            std::string to = " " + html_link + " ";
            string_replace_all(usage, from, to);
        }
        std::string html_link = "<a href=\"../" + iter.second + "/" + escape_infix_operators(iter.first) + ".html\">" + iter.first + "</a>";

        std::string from = " " + iter.first + " ";  // Potentially add more of these later. Or do it in a more intelligent way?
        std::string to = " " + html_link + " ";
        string_replace_all(usage, from, to);

        from = " " + iter.first + "[";
        to = " " + html_link + "[";
        string_replace_all(usage, from, to);

        from = " " + iter.first + "(";
        to = " " + html_link + "(";
        string_replace_all(usage, from, to);

        from = "\n" + iter.first + "(";
        to = "\n" + html_link + "(";
        string_replace_all(usage, from, to);

        from = "(" + iter.first + " ";
        to = "(" + html_link + " ";
        string_replace_all(usage, from, to);

        from = " " + iter.first + ",";
        to = " " + html_link + ",";
        string_replace_all(usage, from, to);

        from = " " + iter.first + "\n";  // We need usage + "\n" for this to work consistently.
        to = " " + html_link + "\n";
        string_replace_all(usage, from, to);

        from = " " + iter.first + "^";
        to = " " + html_link + "^";
        string_replace_all(usage, from, to);

        from = "(" + iter.first + "|";
        to = "(" + html_link + "|";
        string_replace_all(usage, from, to);

        from = "|op: " + iter.first + ">";
        to = "|op: " + html_link + ">";
        string_replace_all(usage, from, to);

        from = "|ops: " + iter.first + " ";
        to = "|ops: " + html_link + " ";
        string_replace_all(usage, from, to);

        from = " " + iter.first + ">";  // Does this one work, or bug out?
        to = " " + html_link + ">";
        string_replace_all(usage, from, to);

    }
    return usage;
}

std::string generate_statement_usage_docs(std::map<std::string, std::string> &operator_locations, const std::string &header, const std::string &dest_dir, const std::string &dir, std::vector<std::string> &built_in_statements) {
    std::string section;

    // Create destination directory:
    std::string working_dir = dest_dir + dir;
    try {
        std::cout << "Creating: " << working_dir << std::endl;
        fs::create_directories(working_dir);
    } catch (std::exception& e) {
        std::cout << "Failed to create: " << working_dir << std::endl;
        std::cout << "Reason: " << e.what() << std::endl;
        return section;
    }

    section = "<dl>\n    <dt><b>" + header + "</b></dt>\n";

    // Now learn the statements:
    for (const auto &str: built_in_statements) {
        if (operator_usage_map.usage_is_defined(str)) {
            std::string statement_file = dir + "/" + escape_infix_operators(str) + ".html";
            section += "        <dd><a href=\"" + statement_file + "\">" + str + "</a></dd>\n";

            std::string usage = operator_usage_map.get_usage(str) + "\n";

            // Write operator usage info to file:
            std::ofstream myfile;
            myfile.open(dest_dir + statement_file);
            if (myfile.is_open()) {
                std::string html_usage = docs_statement_page;
                std::string linked_operator_usage = linkify_operators(operator_locations, usage);
                string_replace_all(html_usage, "$statement-type$", header);
                string_replace_all(html_usage, "$statement-name$", str);
                string_replace_all(html_usage, "$statement-usage$", linked_operator_usage);

                myfile << html_usage;
                myfile.close();
            } else {
                std::cout << "Unable to open file: " << dest_dir + statement_file << std::endl;
            }
        } else {
            section += "        <dd>" + str + "</dd>\n";
        }
    }
    return section + "</dl>\n";
}


template <class T>
std::string generate_operator_usage_docs(std::map<std::string, std::string> &operator_locations, const std::string &header, const std::string &dest_dir, const std::string &dir, T& our_map) {
    std::string section;

    // Create destination directory:
    std::string working_dir = dest_dir + dir;
    try {
        std::cout << "Creating: " << working_dir << std::endl;
        fs::create_directories(working_dir);
    } catch (std::exception& e) {
        std::cout << "Failed to create: " << working_dir << std::endl;
        std::cout << "Reason: " << e.what() << std::endl;
        return section;
    }

    section = "<dl>\n    <dt><b>" + header + "</b></dt>\n";

    // Now learn and sort the corresponding operators:
    std::vector<std::string> tmp_sorted;
    for (const auto &it: our_map) {
        tmp_sorted.push_back(ket_map.get_str(it.first));
    }
    std::sort(tmp_sorted.begin(), tmp_sorted.end());
    for (const auto &str: tmp_sorted) {
        if (operator_usage_map.usage_is_defined(str)) {
            std::string operator_file = dir + "/" + str + ".html";
            section += "        <dd><a href=\"" + operator_file + "\">" + str + "</a></dd>\n";

            std::string usage = operator_usage_map.get_usage(str) + "\n";

            // Write operator usage info to file:
            std::ofstream myfile;
            myfile.open(dest_dir + operator_file);
            if (myfile.is_open()) {
                std::string html_usage = docs_operator_page;
                std::string linked_operator_usage = linkify_operators(operator_locations, usage);
                string_replace_all(html_usage, "$operator-type$", header);
                string_replace_all(html_usage, "$operator-name$", str);
                string_replace_all(html_usage, "$operator-usage$", linked_operator_usage);

                myfile << html_usage;
                myfile.close();
            } else {
                std::cout << "Unable to open file: " << dest_dir + operator_file << std::endl;
            }
        } else {
            section += "        <dd>" + str + "</dd>\n";
        }
    }
    return section + "</dl>\n";
}

std::string generate_sw_section(std::map<std::string, std::string> &operator_locations, const std::string &header, const std::string &dest_dir, const std::string &dir, std::vector<fs::path> &sw3_files) {
    std::string section;

    // Create destination directory:
    std::string working_dir = dest_dir + dir;
    try {
        std::cout << "Creating: " << working_dir << std::endl;
        fs::create_directories(working_dir);
    } catch (std::exception& e) {
        std::cout << "Failed to create: " << working_dir << std::endl;
        std::cout << "Reason: " << e.what() << std::endl;
        return section;
    }

    section = "<dl>\n    <dt><b>" + header + "</b></dt>\n";

    std::vector<std::string> tmp_sorted;
    std::map<std::string, fs::path> sw3_path_map;
    for (const auto &file: sw3_files) {
        std::string my_filename = file.filename().c_str();
        tmp_sorted.push_back(my_filename);
        sw3_path_map[my_filename] = file;
    }
    std::sort(tmp_sorted.begin(), tmp_sorted.end());
    for (const auto &str: tmp_sorted) {
        section += "        <dd><a href=\"" + dir + "/" + str + ".html\">" + str + "</a></dd>\n";
        fs::path source_file = sw3_path_map[str];
        fs::path target_file = working_dir + "/" + str;
        fs::copy(source_file, target_file, fs::copy_options::overwrite_existing);

        std::string code;
        std::ifstream source_stream;
        source_stream.open(source_file);
        if (source_stream.is_open()) {
            std::stringstream buffer;
            buffer << source_stream.rdbuf();
            code = buffer.str();
            source_stream.close();
        } else {
            std::cout << "Unable to open file: " << source_file << std::endl;
        }

        // Now linkify the code:
        std::string linked_code = linkify_operators(operator_locations, code);

        // Now sub in the variables:
        std::string html_usage = docs_sw3_page;
        string_replace_all(html_usage, "$sw3-type$", header);
        string_replace_all(html_usage, "$sw3-name$", str);
        string_replace_all(html_usage, "$sw3-code$", linked_code);

        // Write operator usage info to file:
        std::string dot_html = ".html";
        std::ofstream myfile;
        myfile.open(target_file.c_str() + dot_html);
        if (myfile.is_open()) {
            myfile << html_usage;
            myfile.close();
        } else {
            std::cout << "Unable to open file: " << target_file.c_str() + dot_html << std::endl;
        }
    }
    return section + "</dl>\n";
}

template <class T>
void learn_locations(std::map<std::string, std::string> &operator_locations, const std::string &location, T& our_map) {
    for (const auto &iter: our_map) {
        std::string op = ket_map.get_str(iter.first);
        if (operator_usage_map.usage_is_defined(op)) {  // Only store locations of operators with usage info. This prevents links to 404 pages.
            operator_locations[op] = location;
        }
    }
}

void DocsGenerator::generate(const std::string& dir) {
    std::cout << "Generating docs in: " << dir << std::endl;

    // Find .sw3 files to include in the html documentation:
    std::cout << "Would you like to include .sw3 files? (y/n): ";
    std::vector<fs::path> sw3_files;
    std::map<std::string, std::string> operator_locations;
    char answer;
    std::cin >> answer;
    if (answer == 'y') {
        std::string sw3_dir;
        std::cout << "Please enter the sw3 directory: ";
        std::cin >> sw3_dir;

        std::cout << "Found:" << std::endl;
        for (const auto &entry: fs::directory_iterator(sw3_dir)) {
            if (entry.path().extension() == ".sw3") {
                std::cout << "    " << entry.path() << std::endl;
                sw3_files.push_back(entry.path());
                operator_locations[entry.path().filename().c_str()] = "sw-examples";
            }
        }
        std::cout << std::endl;
    }

    std::string dest_dir = dir + "/docs/usage3/";

    // Create destination directory:
    try {
        std::cout << "Creating: " << dest_dir << std::endl;
        fs::create_directories(dest_dir);
    } catch (std::exception& e) {
        std::cout << "Failed to create: " << dest_dir << std::endl;
        std::cout << "Reason: " << e.what() << std::endl;
        return;
    }

    // Generate html page:
    std::string body;

    // Learn operator locations:

    // First, learn built in statements:
    std::vector<std::string> built_in_statements{ "if", "if-else", "for", "sfor" , "while", "bound function", "operators" };
    operator_locations["if"] = "built-in-statement";
    operator_locations["if-else"] = "built-in-statement";
    operator_locations["for"] = "built-in-statement";
    operator_locations["sfor"] = "built-in-statement";
    operator_locations["while"] = "built-in-statement";
    operator_locations["bound function"] = "built-in-statement";
    operator_locations["operators"] = "built-in-statement";

    // Now, learn infix operators, type 1:
    std::vector<std::string> infix_operators{ " + ", " - ", " _ ", " __ ", " :_ ", " . " };
    operator_locations[" + "] = "infix_operator";
    operator_locations[" - "] = "infix_operator";
    operator_locations[" _ "] = "infix_operator";
    operator_locations[" __ "] = "infix_operator";
    operator_locations[" :_ "] = "infix_operator";
    operator_locations[" . "] = "infix_operator";

    // Now, learn infix operators, type 2:
    std::vector<std::string> infix_operators2{ " == ", " != ", " >= ", " > ", " <= ", " < ", " && ", " || ", " ++ ", " -- ", " ** ", " // ", " %% ", " ^^ ", " .. "};
    operator_locations[" == "] = "infix_operator";
    operator_locations[" != "] = "infix_operator";
    operator_locations[" >= "] = "infix_operator";
    operator_locations[" > "] = "infix_operator";
    operator_locations[" <= "] = "infix_operator";
    operator_locations[" < "] = "infix_operator";
    operator_locations[" && "] = "infix_operator";
    operator_locations[" || "] = "infix_operator";
    operator_locations[" ++ "] = "infix_operator";
    operator_locations[" -- "] = "infix_operator";
    operator_locations[" ** "] = "infix_operator";
    operator_locations[" // "] = "infix_operator";
    operator_locations[" %% "] = "infix_operator";
    operator_locations[" ^^ "] = "infix_operator";
    operator_locations[" .. "] = "infix_operator";

    // Now, learn learn rules:
    std::vector<std::string> learn_rules{ " => ", " +=> ", " .=> ", " #=> ", " !=> "};
    operator_locations[" => "] = "learn_rule";
    operator_locations[" +=> "] = "learn_rule";
    operator_locations[" .=> "] = "learn_rule";
    operator_locations[" #=> "] = "learn_rule";
    operator_locations[" !=> "] = "learn_rule";

    // Now, learn misc components:
    std::vector<std::string> misc_components{ "|>", "comment", "label descent", "|*>", "|category: *>", "|_self>", "(*,*)", "|__self>", "|context>", "supported-ops", "dump", "if-then machine" };
    operator_locations["|>"] = "misc";
    operator_locations["comment"] = "misc";
    operator_locations["label descent"] = "misc";
    operator_locations["|*>"] = "misc";
    operator_locations["|category: *>"] = "misc";
    operator_locations["|_self>"] = "misc";
    operator_locations["(*,*)"] = "misc";
    operator_locations["|__self>"] = "misc";
    operator_locations["|context>"] = "misc";
    operator_locations["supported-ops"] = "misc";
    operator_locations["dump"] = "misc";
    operator_locations["if-then machine"] = "misc";

    // Now, learn object types:
    std::vector<std::string> object_types{"ket", "superposition", "sequence"};
    operator_locations["ket"] = "object_type";
    operator_locations["superposition"] = "object_type";
    operator_locations["sequence"] = "object_type";

    // Now, learn operator types:
    std::vector<std::string> operator_types{"sigmoid", "numeric", "simple", "compound", "function", "bracket", "powered", "op-sequence"};
    operator_locations["sigmoid"] = "operator_type";
    operator_locations["numeric"] = "operator_type";
    operator_locations["simple"] = "operator_type";
    operator_locations["compound"] = "operator_type";
    operator_locations["function"] = "operator_type";
    operator_locations["bracket"] = "operator_type";
    operator_locations["powered"] = "operator_type";
    operator_locations["op-sequence"] = "operator_type";

    // Now, learn our operators:
    // NB: the locations must match those used in the next section.
    learn_locations(operator_locations, "built-in", fn_map.built_in);
    learn_locations(operator_locations, "compound-built-in", fn_map.compound_built_in);
    learn_locations(operator_locations, "compound-context-built-in", fn_map.compound_context_built_in);
    learn_locations(operator_locations, "sigmoid", fn_map.sigmoids);
    learn_locations(operator_locations, "compound-sigmoid", fn_map.compound_sigmoids);
    learn_locations(operator_locations, "ket-fn", fn_map.ket_fn);
    learn_locations(operator_locations, "context-ket-fn", fn_map.context_ket_fn);
    learn_locations(operator_locations, "compound-ket-fn", fn_map.compound_ket_fn);
    learn_locations(operator_locations, "sp-fn", fn_map.sp_fn);
    learn_locations(operator_locations, "compound-sp-fn", fn_map.compound_sp_fn);
    learn_locations(operator_locations, "seq-fn", fn_map.seq_fn);
    learn_locations(operator_locations, "context-seq-fn", fn_map.context_seq_fn);
    learn_locations(operator_locations, "compound-seq-fn", fn_map.compound_seq_fn);
    learn_locations(operator_locations, "compound-context-sp-fn", fn_map.compound_context_sp_fn);
    learn_locations(operator_locations, "compound-context-seq-fn", fn_map.compound_context_seq_fn);
    learn_locations(operator_locations, "function-1", fn_map.whitelist_1);
    learn_locations(operator_locations, "function-2", fn_map.whitelist_2);
    learn_locations(operator_locations, "function-3", fn_map.whitelist_3);
    learn_locations(operator_locations, "function-4", fn_map.whitelist_4);
    learn_locations(operator_locations, "context-function-1", fn_map.context_whitelist_1);
    learn_locations(operator_locations, "context-function-2", fn_map.context_whitelist_2);
    learn_locations(operator_locations, "context-function-3", fn_map.context_whitelist_3);
    learn_locations(operator_locations, "context-function-4", fn_map.context_whitelist_4);

    // Generate built-in statements section:
    body += generate_statement_usage_docs(operator_locations, "built in statements", dest_dir, "built-in-statement", built_in_statements);

    // Generate infix operators, v1 section:
    body += generate_statement_usage_docs(operator_locations, "infix operators, type 1", dest_dir, "infix_operator", infix_operators);

    // Generate infix operators, v2 section:
    body += generate_statement_usage_docs(operator_locations, "infix operators, type 2", dest_dir, "infix_operator", infix_operators2);

    // Generate learn rules section:
    body += generate_statement_usage_docs(operator_locations, "learn rules", dest_dir, "learn_rule", learn_rules);

    // Generate misc section:
    body += generate_statement_usage_docs(operator_locations, "misc", dest_dir, "misc", misc_components);

    // Generate object types section:
    body += generate_statement_usage_docs(operator_locations, "object types", dest_dir, "object_type", object_types);

    // Generate operator types section:
    body += generate_statement_usage_docs(operator_locations, "operator types", dest_dir, "operator_type", operator_types);

    // Generate operator sections:
    body += generate_operator_usage_docs(operator_locations, "built in operators", dest_dir, "built-in", fn_map.built_in);
    body += generate_operator_usage_docs(operator_locations, "built in compound operators", dest_dir, "compound-built-in", fn_map.compound_built_in);
    body += generate_operator_usage_docs(operator_locations, "built in compound context operators", dest_dir, "compound-context-built-in", fn_map.compound_context_built_in);
    body += generate_operator_usage_docs(operator_locations, "sigmoids", dest_dir, "sigmoid", fn_map.sigmoids);
    body += generate_operator_usage_docs(operator_locations, "compound sigmoids", dest_dir, "compound-sigmoid", fn_map.compound_sigmoids);
    body += generate_operator_usage_docs(operator_locations, "ket fn", dest_dir, "ket-fn", fn_map.ket_fn);
    body += generate_operator_usage_docs(operator_locations, "context ket fn", dest_dir, "context-ket-fn", fn_map.context_ket_fn);
    body += generate_operator_usage_docs(operator_locations, "compound ket fn", dest_dir, "compound-ket-fn", fn_map.compound_ket_fn);
    body += generate_operator_usage_docs(operator_locations, "sp fn", dest_dir, "sp-fn", fn_map.sp_fn);
    body += generate_operator_usage_docs(operator_locations, "compound sp fn", dest_dir, "compound-sp-fn", fn_map.compound_sp_fn);
    body += generate_operator_usage_docs(operator_locations, "seq fn", dest_dir, "seq-fn", fn_map.seq_fn);
    body += generate_operator_usage_docs(operator_locations, "context seq fn", dest_dir, "context-seq-fn", fn_map.context_seq_fn);
    body += generate_operator_usage_docs(operator_locations, "compound seq fn", dest_dir, "compound-seq-fn", fn_map.compound_seq_fn);
    body += generate_operator_usage_docs(operator_locations, "compound context sp fn", dest_dir, "compound-context-sp-fn", fn_map.compound_context_sp_fn);
    body += generate_operator_usage_docs(operator_locations, "compound context seq fn", dest_dir, "compound-context-seq-fn", fn_map.compound_context_seq_fn);
    body += generate_operator_usage_docs(operator_locations, "function 1", dest_dir, "function-1", fn_map.whitelist_1);
    body += generate_operator_usage_docs(operator_locations, "function 2", dest_dir, "function-2", fn_map.whitelist_2);
    body += generate_operator_usage_docs(operator_locations, "function 3", dest_dir, "function-3", fn_map.whitelist_3);
    body += generate_operator_usage_docs(operator_locations, "function 4", dest_dir, "function-4", fn_map.whitelist_4);
    body += generate_operator_usage_docs(operator_locations, "context function 1", dest_dir, "context-function-1", fn_map.context_whitelist_1);
    body += generate_operator_usage_docs(operator_locations, "context function 2", dest_dir, "context-function-2", fn_map.context_whitelist_2);
    body += generate_operator_usage_docs(operator_locations, "context function 3", dest_dir, "context-function-3", fn_map.context_whitelist_3);
    body += generate_operator_usage_docs(operator_locations, "context function 4", dest_dir, "context-function-4", fn_map.context_whitelist_4);


    // Generate sw-examples section:
    if (!sw3_files.empty()) {
        body += generate_sw_section(operator_locations, "sw-examples", dest_dir, "sw-examples", sw3_files);
    }

    // Load up the index page, and insert the body:
    std::string page = docs_index_page;
    string_replace_all(page, "$body$", body);

    // Generate current date:
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "%B %d, %G", timeinfo);

    // Now sub the date-time in:
    string_replace_all(page, "$date-time$", buffer);

    // Write index page to stdout:
    std::cout << "\nNew html index page:\n" << page << std::endl;


    // Write index page to file:
    std::ofstream myfile;
    myfile.open(dest_dir + "index.html");
    if (myfile.is_open()) {
        myfile << page;
        myfile.close();
    } else {
        std::cout << "Unable to open file: " << dest_dir + "index.html" << std::endl;
    }
}
