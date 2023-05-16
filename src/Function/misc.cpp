//
// Semantic DB 4
// Created 2021/12/28
// Updated 2023/5/12
// Author Garry Morrison
// License GPL v3
//

#include <math.h>
#include <iostream>
#include <sstream>
#include "misc.h"
#include <regex>


bool double_eq(const double v1, const double v2) {
    if (fabs(v1 - v2) < EPSILON) {
        return true;
    }
    return false;
}

bool long_double_eq(const long double v1, const long double v2) {
    if (fabs(v1 - v2) < EPSILON) {
        return true;
    }
    return false;
}

int ipower(int a, int n)  // From here: https://stackoverflow.com/questions/1505675/power-of-an-integer-in-c
{
    int res = 1;  // Please test it is correct!
    while (n) {
        if (n & 1)
            res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

std::string float_to_int(const long double v, unsigned int places) {
    if (long_double_eq(v, round(v))) {
        return std::to_string(static_cast<long long int>(round(v)));
    }
    // return std::to_string(v); // use decimal places here later!
    // std::cout << "float_to_int, decimal places: " << places << "\n";
    std::ostringstream buffer;
    // unsigned int tens = pow(10, places);  // Compiler warning: conversion from double to unsigned int, possible loss of data. Fix.
    int tens = ipower(10, places);           // Need to test it works, but it should be correct.
    buffer << round(v * tens) / tens;
    return buffer.str();
}

void string_replace_all(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty()) { return; }
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

bool string_starts_with_token(const std::string& str, const std::vector<std::string>& tokens) {
    for (const std::string& token : tokens) {
        if (str.size() < token.size()) {
            continue;
        }
        if (str.substr(0, token.size()) == token) {
            return true;
        }
    }
    return false;
}

bool string_ends_with_token(const std::string& str, const std::vector<std::string>& tokens) {
    for (const std::string& token : tokens) {
        if (str.size() < token.size()) {
            continue;
        }
        if (std::equal(token.rbegin(), token.rend(), str.rbegin())) {
            return true;
        }
    }
    return false;
}

bool string_starts_with(const std::string& str, const std::string& token)
{
    if (str.size() < token.size()) {
        return false;
    }
    if (str.substr(0, token.size()) == token) {  // Should we convert to std::equal() instead?
        return true;
    }
    return false;
}

bool string_ends_with(const std::string& str, const std::string& token)
{
    if (str.size() < token.size()) {
        return false;
    }
    if (std::equal(token.rbegin(), token.rend(), str.rbegin())) {
        return true;
    }
    return false;
}


std::string string_repeat(const std::string& input, unsigned num) {
    std::string ret;
    ret.reserve(input.size() * num);
    while (num--)
        ret += input;
    return ret;
}

bool is_number(const std::string& str) {  // a quick check if a string is a number or not. NB: not perfect, since invalid numbers will return true.
    return !str.empty() && str.find_first_not_of("-.0123456789") == std::string::npos;
}

std::string strip_ket(const std::string& str)  // Test it, but should be correct. This function removes the first and last chars from a string. eg |Fred> converts to Fred.
{
    if (str.size() < 2) { return str; }
    return str.substr(1, str.size() - 2);
}

std::string strip_leading_spaces(const std::string& s, const unsigned int spaces_count)
{
    // return std::regex_replace(s, std::regex("^    "), "");
    return std::regex_replace(s, std::regex("^ {" + std::to_string(spaces_count) + "}"), "");
}

// Copied from here:
// https://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector
std::size_t int_vector_to_hash(const std::vector<uint32_t>& vec)
{
    std::size_t seed = vec.size();
    for (auto x : vec)
    {
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = (x >> 16) ^ x;
        seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}


