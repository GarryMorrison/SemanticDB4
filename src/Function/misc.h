//
// Semantic DB 4
// Created 2021/12/28
// Updated 2023/5/12
// Author Garry Morrison
// License GPL v3
//

#pragma once



#include <string>
#include <vector>

extern unsigned int default_decimal_places;

const double EPSILON = 0.0001;
bool double_eq(const double v1, const double v2);
bool long_double_eq(const long double v1, const long double v2);
int ipower(int a, int n);
std::string float_to_int(const long double v, unsigned int places);
void string_replace_all(std::string& str, const std::string& from, const std::string& to);
bool string_starts_with_token(const std::string& str, const std::vector<std::string>& tokens);
bool string_ends_with_token(const std::string& str, const std::vector<std::string>& tokens);
bool string_starts_with(const std::string& str, const std::string& token);
bool string_ends_with(const std::string& str, const std::string& token);
std::string string_repeat(const std::string& input, unsigned num);
bool is_number(const std::string& str);
std::string strip_ket(const std::string& str);
std::string strip_leading_spaces(const std::string& s, const unsigned int spaces_count);
std::size_t int_vector_to_hash(const std::vector<uint32_t>& vec);
// std::size_t int_vector_to_hash(const std::vector<ulong>& vec);
