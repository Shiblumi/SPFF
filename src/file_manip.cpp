#include "../include/file_manip.h"

#include <cassert>


const std::string FileManip::get_file_data(const std::string& ff, const FileData& fd) {
    if      (ff == "gn")  return fd.get_game_name();
    else if (ff == "d")   return fd.get_day();
    else if (ff == "dn")  return fd.get_day_name();
    else if (ff == "dns") return fd.get_day_name_short();
    else if (ff == "m")   return fd.get_month();
    else if (ff == "mn")  return fd.get_month_name();
    else if (ff == "mns") return fd.get_month_name_short();
    else if (ff == "y")   return fd.get_year();
    else if (ff == "ms")  return fd.get_ms();
    else if (ff == "sec") return fd.get_sec();
    else if (ff == "min") return fd.get_min();
    else if (ff == "hr")  return fd.get_hr();
    else {
        std::cerr << "Error: Invalid format specifier: " << ff << std::endl;
        exit(1);
    }
    return "";
}


std::string FileManip::input_user_file_format() {
    std::string user_format;
    std::cout << "{gn}=game_name  {d}=day  {dn}=day_name  {dns}=day_name_short  {m}=month  {mn}=month_name\n"
              << "{mns}=month_name_short  {y}=year  {ms}=milliseconds  {sec}=seconds  {min}=minutes  {hr}=hours\n";
    std::cin >> user_format;
    return user_format;
}


std::string FileManip::input_user_suffix_format() {
    std::string user_suffix_format;
    std::cout << "Resulting identical file names must have a suffix.\n"
              << "Example: \"File - 2.txt\", suffix is \" - 2\", format is \" - {d}\"\n";
    std::cout << "Enter suffix format: ";
    std::cin >> user_suffix_format;
    return user_suffix_format;
}


void FileManip::store_files(const std::string& path) {
    
    for (auto & file : fs::directory_iterator(path)) {
        if (fs::is_regular_file(file)) {
            
            std::pair<fs::directory_entry, FileData> file_pair(file, FileData(file.path().filename().string()));
            _files.push_back(file_pair);
        }
    }
}


std::string FileManip::create_formatted_filename(const FileData& file_data) {
    std::string formatted_file_name{};
    std::string format_flag{};
    bool format_bit{false};

    for (const auto& c : _user_file_format) {
        
        if (c == '{') {
            format_bit = true;
            continue;
        }
        else if (c == '}') {
            // std::cout << "format_flag: " << format_flag << std::endl;
            formatted_file_name.append(get_file_data(format_flag, file_data));
            format_flag.clear();
            format_bit = false;
            continue;
        }

        if (format_bit) {
            format_flag += c;
        }
        else {
            formatted_file_name += c;
        }
    }
    // formatted_file_name.append("." + file_data.get_file_type());

    return formatted_file_name;
}


std::string FileManip::create_formatted_suffix(const int& file_num) {
    std::string formatted_suffix{};
    std::string format_flag{};
    bool format_bit{false};

    for (const auto& c : _user_suffix_format) {
        
        if (c == '{') {
            format_bit = true;
            continue;
        }
        else if (c == '}') {
            if (format_flag == "n") {
                formatted_suffix.append(std::to_string(file_num));
            }
            else {
                std::cerr << "Invalid format specifier: " << format_flag << std::endl;
                exit(1);
            }
            format_flag.clear();
            format_bit = false;
            continue;
        }

        if (format_bit) {
            format_flag += c;
        }
        else {
            formatted_suffix += c;
        }
    }
    return formatted_suffix;
}


bool FileManip::validate_new_filenames(fpd_pairs original_files, str_vect modified_filenames) {

    if (original_files.size() != modified_filenames.size()) {
        std::cerr << "Program Error: Original file count does not match modified_filenames size\n" << std::endl;
        return false;
    }

    for (auto filename : modified_filenames) {
        if (std::count(modified_filenames.begin(), modified_filenames.end(), filename) > 1) {
            std::cerr << "Program Error: Duplicate filename found in modified_filenames\n" << std::endl;
            return false;
        }
    }
    return true;
}


void FileManip::apply_rename(str_vect modified_filenames) {
    size_t size = modified_filenames.size();

    for (size_t i = 0; i < size; ++i) {
        fs::path modified_path(modified_filenames[i]);
        fs::rename(_files[i].first.path(), _files[i].first.path().parent_path() / modified_path);
    }
}


void FileManip::handle_duplicates(str_vect& modified_filenames) {
    for (auto& filename : modified_filenames) {
        std::string original_filename = filename;
        if (std::count(modified_filenames.begin(), modified_filenames.end(), filename) > 1) {
            int count{1};
            auto it = std::find(modified_filenames.begin(), modified_filenames.end(), filename);

            while (it != modified_filenames.end()) {
                if (*it == original_filename) {
                    std::string formatted_suffix = create_formatted_suffix(count);
                    (*it).append(formatted_suffix);
                    ++count;
                }
                ++it;
            }
        }
    }
    // std::cout << "Display:\n";
    // for (auto i : modified_filenames) {
    //     std::cout << i << std::endl;
    // }
}


void FileManip::append_file_extension(str_vect& modified_filenames) {
    size_t size = modified_filenames.size();
    assert(size == _files.size());
    
    for (size_t i = 0; i < size; ++i) {
        std::string file_extension = "." + _files[i].second.get_file_type();
        modified_filenames[i].append(file_extension);
    }
}



void FileManip::rename_files() {
    str_vect modified_filenames{};

    _files.clear();

    if (_dir_path.empty()) {
        std::cerr << "Path is empty" << std::endl;
        return;
    }
    store_files(_dir_path);

    if (_files.empty()) {
        std::cerr << "No files found" << std::endl;
        return;
    }
    else
        std::cout << _files.size() << " files found\n"  << std::endl;

    for (auto& file : _files) {
        std::string formatted_file_name = create_formatted_filename(file.second);
        std::string file_extension = "." + file.second.get_file_type();

        modified_filenames.push_back(formatted_file_name);
    }

    handle_duplicates(modified_filenames);
    append_file_extension(modified_filenames);

    for (auto& i : modified_filenames) {
        std::cout << i << std::endl;
    }

    if (!validate_new_filenames(_files, modified_filenames)) {
        std::cerr << "Program Error: Modified filenames failed validation\n" << std::endl;
        exit(1);
    }

    try {
        apply_rename(modified_filenames);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error renaming file: " << e.what() << std::endl;
    }





    
    // try {
    //     std::cout << "OG:  " << file.first.path().filename() << "\n";
    //     std::cout << "New: \"" << formatted_file_name << file_extension << "\"\n" << std::endl;
    //     // fs::rename(file.first.path(), file.first.path().parent_path() / formatted_file_name);
    // } catch (const fs::filesystem_error& e) {
    //     std::cerr << "Error renaming file: " << e.what() << std::endl;
    // }
}

        // std::cout << "OG:  " << file.first.path().filename() << std::endl;
        // std::cout << "New: " << formatted_file_name << std::endl;
        // std::cout << std::endl;
        // std::cout << "New: " << file.first.path().parent_path() / formatted_file_name << std::endl;

        // std::cout << "Final: ";
        // std::cout << file.first.path().filename() << std::endl;