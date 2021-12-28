//
// Semantic DB 4
// Created 2021/12/28
// Updated 2021/12/28
// Author Garry Morrison
// License GPL v3
//

#pragma once

#include <iostream>
#include <chrono>
#include <map>
#include <string>


const std::map<long long, std::string> time_interval_map = {  // time_interval_map assumes times are in milliseconds.
        { 1000 * 60 * 60 * 24 * 7, "week"},
        { 1000 * 60 * 60 * 24, "day"},
        { 1000 * 60 * 60, "hour"},
        { 1000 * 60, "minute"},
        { 1000, "second"},
        { 1, "millisecond"}
};


std::string display_time(const long long time);


class Timer_ms
{
private:
    std::chrono::high_resolution_clock::time_point m_StartTimepoint;
    std::chrono::high_resolution_clock::time_point m_StopTimepoint;
    bool m_stopped;
public:
    Timer_ms() {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
        m_stopped = false;
    }

    void Stop() {
        m_StopTimepoint = std::chrono::high_resolution_clock::now();
        m_stopped = true;
    }
    long long GetTime() {
        if (!m_stopped) {
            return 0;  // Maybe do something else here? Eg, just call Stop()?
        }
        long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimepoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StopTimepoint).time_since_epoch().count();
        return end - start;
    }

    ~Timer_ms() {
        if (!m_stopped) { Stop(); }
    }
};

