//
// Semantic DB 4
// Created 2021/12/28
// Updated 2022/2/11
// Author Garry Morrison
// License GPL v3
//

#pragma once

#include <vector>
#include <string>
#include <string_view>

std::vector<std::string> split(const std::string& s, const std::string& delimiter);
std::vector<std::string> view_split(std::string_view s, std::string_view delimiter);
std::string join(const std::vector<std::string>& v, const std::string& delimiter);

std::vector<std::string> split_on_first(const std::string& s, const std::string& delimiter);
