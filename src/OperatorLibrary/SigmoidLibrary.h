#pragma once

//
// Created by Garry Morrison on 13/09/2020.
//


#include <vector>
#include <memory>
#include "../CompoundConstant/CompoundConstant.h"

double clean(const double x);
double threshold_filter(const double x, const double t);
double op_threshold_filter(const double x, const std::vector<std::shared_ptr<CompoundConstant> >& parameters);
double not_threshold_filter(const double x, const double t);
double op_not_threshold_filter(const double x, const std::vector<std::shared_ptr<CompoundConstant> >& parameters);
double binary_filter(const double x);
double sigmoid_in_range(const double x, const double a, const double b);
double op_sigmoid_in_range(const double x, const std::vector<std::shared_ptr<CompoundConstant> >& parameters);
double ReLU(const double x);
double op_invert(const double x);
double op_sigmoid_random(const double x, const std::vector<std::shared_ptr<CompoundConstant> >& parameters);  // Deprecated.
double op_min(const double x, const std::vector<std::shared_ptr<CompoundConstant> >& parameters);
double op_max(const double x, const std::vector<std::shared_ptr<CompoundConstant> >& parameters);

double sigmoid_inc(const double x);
double sigmoid_dec(const double x);

