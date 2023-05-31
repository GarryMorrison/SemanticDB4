//
// Semantic DB 4
// Created 2021/12/28
// Updated 2021/12/28
// Author Garry Morrison
// License GPL v3
//

#pragma once


#include <map>
#include <string>
#include <vector>
#include <set>
#include "../Function/SplitJoin.h"
#include "../Function/misc.h"


typedef struct
{
    std::string Name;
    std::string Description;
    std::string Examples;
    std::string SeeAlso;
} OpUsageInfo;

class OperatorUsageMap {
private:
public:
    std::map<std::string, std::string> map;
    OperatorUsageMap();
    std::string get_usage(const std::string& s) const;
    bool usage_is_defined(const std::string& s) const;

    std::map<std::string, OpUsageInfo*> m_usage_info_map;  // Make private?
    void PopulateUsageMap();
    OpUsageInfo* get_usage_info(const std::string& op);

    std::string linkify_text(std::string text);

    std::map<std::string, std::string> statement_prototypes;
    bool has_statement_prototype(const std::string& s) const;

    std::set<std::string> search_usage_map(const std::string search_term, bool name, bool description, bool examples, bool seealso);
};

extern OperatorUsageMap operator_usage_map;