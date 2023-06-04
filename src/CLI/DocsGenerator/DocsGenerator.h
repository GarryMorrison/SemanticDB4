//
// Semantic DB 4
// Created 2023/6/3
// Updated 2023/6/3
// Author Garry Morrison
// License GPL v3
//


#pragma once


#include <string>
#include "../SDB_CLI.h"

// FIXME: delete these when it is safe to do so:
// #include "../FunctionOperatorMap/FunctionOperatorMap.h"
// #include "../OperatorUsageMap/OperatorUsageMap.h"
// #include "../Function/misc.h"


class DocsGenerator {
public:
    void generate(const std::string& dir);
};



