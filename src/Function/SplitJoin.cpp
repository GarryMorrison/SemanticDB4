//
// Semantic DB 4
// Created 2021/12/28
// Updated 2022/2/11
// Author Garry Morrison
// License GPL v3
//

#include "SplitJoin.h"


#include <vector>
#include <string>
#include <string_view>



// from here:
// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
    std::vector<std::string> result;
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        result.push_back(token);
    }
    result.push_back(s.substr(pos_start));
    return result;
}

std::vector<std::string> view_split(std::string_view s, std::string_view delimiter) {
    std::vector<std::string> result;
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string_view token;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string_view::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        result.push_back(static_cast<std::string>(token));
    }
    result.push_back(static_cast<std::string>(s.substr(pos_start)));
    return result;
}

std::string join(const std::vector<std::string>& v, const std::string& delimiter) {
    std::string s;
    bool first_pass = true;
    for (const auto& token : v) {
        if (first_pass) {
            s += token;
            first_pass = false;
        }
        else {
            s += delimiter + token;
        }
    }
    return s;
}

std::vector<std::string> split_on_first(const std::string& s, const std::string& delimiter)  // Need to test it!
{
    std::vector<std::string> result;
    size_t split_pos = s.find(delimiter, 0);
    if (split_pos != std::string::npos)
    {
        result.push_back(s.substr(0, split_pos));
        result.push_back(s.substr(split_pos + delimiter.length()));
    }
    else
    {
        result.push_back(s);
    }
    return result;
}

std::vector<std::string> split_on_chars(const std::string& s, const std::set<char> chars)
{
    std::vector<std::string> result;
    std::string token;
    token.clear();

    // loop through our string, one char at a time:
    for (char c : s)
    {
        if (chars.find(c) != chars.end())
        {
            if (!token.empty())
            {
                result.push_back(token);
                token.clear();
            }
            result.push_back(std::string(1,c));
        }
        else
        {
            token += c;
        }
    }

    // Make sure we catch the last token too:
    if (!token.empty())
    {
        result.push_back(token);
    }

    return result;
}