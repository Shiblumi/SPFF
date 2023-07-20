#pragma once

#include "file_data.h"

typedef std::vector<std::pair<fs::directory_entry, FileData>> fpd_pairs; // File Pointer Data Pairs

class FileManip {

    // private data
    std::string _dir_path_str;
    fs::path _dir_path_obj;
    std::string _user_file_format;
    std::string _user_suffix_format;
    fpd_pairs _files; // Don't modify this

    // private helper funcs
    void store_files_from_filename(const std::string& path);

    void store_files_from_system(fs::path path);

    const std::string get_file_data(const std::string& ff, const FileData& fd);

    std::string create_formatted_filename(const FileData& file_data);

    std::string create_formatted_suffix(const int& file_num);

    bool validate_new_filenames(fpd_pairs original_files, str_vect modified_file_names);

    void apply_rename(str_vect modified_filenames);

    void handle_duplicates(str_vect& modified_filenames);

    void append_file_extension(str_vect& modified_filenames);

public:

    // ctor dtor
    FileManip() : _dir_path_str{}, _files() {
        _user_file_format = "{gn} {y}.{m}.{d} - {hr}.{min}.{sec}.{ms}";
        _user_suffix_format = " - {n}";
    }

    FileManip(std::string dir_path) : _dir_path_str(dir_path), _dir_path_obj(), _files() {
        _user_file_format = "{gn} {y}.{m}.{d} - {hr}.{min}.{sec}.{ms}";
        _user_suffix_format = " - {n}";
    }

    FileManip(const char* dir_path) : _dir_path_str(dir_path), _dir_path_obj(), _files() {
        _user_file_format = "{gn} {y}.{m}.{d} - {hr}.{min}.{sec}.{ms}";
        _user_suffix_format = " - {n}";
    }

    FileManip(fs::path dir_path) : _dir_path_str{}, _dir_path_obj(dir_path), _files() {
        _user_file_format = "{gn} {y}.{m}.{d} - {hr}.{min}.{sec}.{ms}";
        _user_suffix_format = " - {n}";
    }

    ~FileManip() = default;

    // access funcs
    void set_user_filename_format(const std::string& user_format) { _user_file_format = user_format; }

    std::string get_user_filename_format() const { return _user_file_format; }

    void set_user_suffix_format(const std::string& user_format) { _user_suffix_format = user_format; }

    std::string get_user_suffix_format() const { return _user_suffix_format; }

    // methods
    std::string input_user_file_format();

    std::string input_user_suffix_format();

    void rename_files();


};
