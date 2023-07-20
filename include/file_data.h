#pragma once

#include "definitions.h"

#include <chrono>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <sstream>
#include <regex>
#include <cmath>

class FileData {
    // private data
    file_data_struct _fd;
    std::string _original_path;
    std::string _modified_path;

    // private helper funcs
    str_vect split_filename(std::string str);

    str_vect split_last_write_time(std::string str);

    void data_from_filename_to_obj(str_vect tokens);

    void data_from_system_to_obj(str_vect tokens);

    void store_day_name(std::string day, std::string month, std::string year);

    void store_month_name(int month);

    void store_month_number(std::string month);

    void store_file_extension(std::string path);
    
    void store_game_name(str_vect tokens);

public:
    // ctor dtor
    FileData() : _original_path(""), _modified_path("") { }
    FileData(std::string path) : _original_path(path), _modified_path("") {
        // store_file_data_from_filename(str);
        store_file_data_from_system(path);
    }
    ~FileData() = default;

    // access funcs for private data
    std::string get_original_str() const { return _original_path; }

    std::string get_modified_str() const { return _modified_path; }

    void set_original_str(std::string str) { _original_path = str; }

    void set_modified_str(std::string str) { _modified_path = str; }

    // access funcs for file_data_struct
    std::string get_game_name() const { return _fd.game_name; }

    std::string get_file_type() const { return _fd.file_type; }

    std::string get_day() const { return _fd.day; }

    std::string get_day_name() const { return _fd.day_name; }

    std::string get_day_name_short() const { return _fd.day_name_s; }

    std::string get_month() const { return _fd.month; }

    std::string get_month_name() const { return _fd.month_name; }

    std::string get_month_name_short() const { return _fd.month_name_s; }

    std::string get_year() const { return _fd.year; }

    std::string get_ms() const { return _fd.time_ms; }

    std::string get_sec() const { return _fd.time_sec; }

    std::string get_min() const { return _fd.time_min; }

    std::string get_hr() const { return _fd.time_hr; }

    // methods
    void store_file_data_from_filename(std::string str);

    void store_file_data_from_system(std::string a_path);

    void print_data();
};


