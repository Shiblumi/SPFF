#pragma once

#include "file_data.h"

#include <filesystem>

namespace fs = std::filesystem;
typedef std::vector<std::pair<fs::directory_entry, FileData>> fpd_pairs; // File Pointer Data Pairs

class FileManip {

    // private data
    std::string _dir_path;
    std::string _user_file_format;
    std::string _user_suffix_format;
    fpd_pairs _files; // Don't modify this

    // private helper funcs
    void store_dir_files(const std::string& path);

    const std::string get_file_data(const std::string& ff, const FileData& fd);

    std::string create_formatted_file_name(const FileData& file_data);

    std::string create_formatted_suffix(const int file_num);

public:

    // ctor dtor
    FileManip() : _dir_path{}, _user_file_format{}, _files() { }
    FileManip(std::string dir_path) : _dir_path(dir_path), _user_file_format{}, _files() { }
    ~FileManip() = default;

    // access funcs
    void set_user_string_format(const std::string& user_format) { _user_file_format = user_format; }

    std::string get_user_string_format() const { return _user_file_format; }

    // methods
    std::string input_user_file_format();

    std::string FileManip::input_user_suffix_format();

    void rename_files();


};