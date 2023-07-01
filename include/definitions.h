#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include <unordered_map>

struct file_data_struct {
    // general
    std::string game_name;
    std::string file_type;

    // date
    std::string day;
    std::string day_name;
    std::string day_name_s;
    std::string month;
    std::string month_name;
    std::string month_name_s;
    std::string year;

    // time
    std::string time_ms;
    std::string time_sec;
    std::string time_min;
    std::string time_hr;
};


const std::array<std::string, 7> day_names = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};


const std::array<std::string, 7> day_names_s = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};


const std::array<std::string, 12> month_names = {
    "January", "February", "March", "April", "May", "June", "July", "August", "September",
    "October", "November", "December"
};


const std::array<std::string, 12> month_names_s = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep",
    "Oct", "Nov", "Dec"
};
