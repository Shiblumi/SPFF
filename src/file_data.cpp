#include "../include/file_data.h"


str_vect FileData::split_filename(std::string str) {

    // from: https://stackoverflow.com/a/58164098
    std::regex re("[. -]");
    std::sregex_token_iterator first{str.begin(), str.end(), re, -1}, last;
    str_vect tokens{first, last};

    tokens.erase(
        std::remove_if(
            tokens.begin(), 
            tokens.end(), 
            [](std::string s) { 
                return s.empty(); 
            }
        ), 
        tokens.end());
    
    return tokens;
}

str_vect FileData::split_last_write_time(std::string str) {

    // from: https://stackoverflow.com/a/58164098
    std::regex re(" ");
    std::sregex_token_iterator first{str.begin(), str.end(), re, -1}, last;
    str_vect tokens{first, last};

    tokens.erase(
        std::remove_if(
            tokens.begin(), 
            tokens.end(), 
            [](std::string s) { 
                return s.empty(); 
            }
        ), 
        tokens.end());
    
    return tokens;
}


void FileData::data_from_filename_to_obj(str_vect tokens) {
    size_t size = tokens.size();
    _fd.file_type = tokens[size - 1];
    _fd.time_ms   = tokens[size - 2];
    _fd.time_sec  = tokens[size - 3];
    _fd.time_min  = tokens[size - 4];
    _fd.time_hr   = tokens[size - 5];
    _fd.day       = tokens[size - 6];
    _fd.month     = tokens[size - 7];
    _fd.year      = tokens[size - 8];

    // If file uses older Shadowplay filename format, change to YYYY-MM-DD.
    if (_fd.year.size() != 4) {
        std::swap(_fd.year, _fd.day);
        std::swap(tokens[size - 8], tokens[size - 6]);
        std::swap(_fd.month, _fd.day);
        std::swap(tokens[size - 7], tokens[size - 6]);
    }

    store_day_data(_fd.day, _fd.month, _fd.year);
    store_month_data_from_filename(std::stoi(_fd.month));
    store_game_name(tokens);
}


void FileData::data_from_system_to_obj(str_vect tokens) {
    _fd.day_name_s   = tokens[0];
    _fd.month_name_s = tokens[1];
    _fd.day          = tokens[2];
    _fd.time_hr      = tokens[3];
    _fd.time_min     = tokens[4];
    _fd.time_sec     = tokens[5];
    _fd.year         = tokens[6];

    store_month_data_from_system(_fd.month_name_s);
    store_day_data(_fd.day, _fd.month, _fd.year);
    store_file_extension(_original_path);
}


void FileData::store_day_data(std::string a_day, std::string a_month, std::string a_year) {
    int day   = std::stoi(a_day);
    int month = std::stoi(a_month);
    int year  = std::stoi(a_year);

    // formula from: https://www.tondering.dk/claus/cal/chrweek.php#calcdow
    int a = (14 - month) / 12;
    int y = year - a;
    int m = month + 12 * a - 2;

    size_t d = static_cast<size_t>((day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7);

    _fd.day_name = day_names[d];
    _fd.day_name_s = day_names_s[d];
}


void FileData::store_month_data_from_filename(int month) {
    _fd.month_name = month_names[static_cast<size_t>(month - 1)];
    _fd.month_name_s = month_names_s[static_cast<size_t>(month - 1)];
}


void FileData::store_month_data_from_system(std::string a_month_name_s) {
    std::string index = std::to_string(std::distance(month_names_s.begin(), std::find(month_names_s.begin(), month_names_s.end(), a_month_name_s)));
    _fd.month = std::stoi(index) + 1;
    _fd.month_name = month_names[static_cast<size_t>(std::stoi(index))];
}


void FileData::store_file_extension(std::string path) {
    fs::path p(path);
    std::string ext = p.extension().string();
    _fd.file_type = ext;
}



void FileData::store_game_name(str_vect tokens) {
    str_vect game_name;
    for (auto &s: tokens) {
        if (s == _fd.year) break;
        game_name.push_back(s);
    }
    for(auto &s: game_name) {
        _fd.game_name += s;
        _fd.game_name += (s == game_name.back()) ? "" : " ";
    }
}


void FileData::store_file_data_from_filename(std::string str) {

    str_vect tokens = split_filename(str);
    tokens.erase(remove_if(tokens.begin(), tokens.end(), [](std::string s) { return s == "DVR"; }), tokens.end());
    data_from_filename_to_obj(tokens);
}


void FileData::store_file_data_from_system(fs::path path) {

    // From cppreference.com - https://en.cppreference.com/w/cpp/filesystem/directory_entry/last_write_time
    // NOTE: Requires std=c++20
    fs::file_time_type ftime = fs::last_write_time(path);
    std::time_t cftime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(ftime));
    std::string ftime_str = std::asctime(std::localtime(&cftime));
    ftime_str.pop_back();  // rm the trailing '\n' put by `asctime`

    std::cout << ftime_str << std::endl;

    str_vect tokens = split_last_write_time(ftime_str);

    data_from_system_to_obj(tokens);
}



void FileData::print_data() {
    using namespace std;

    int w = 20;

    cout << setw(w) << left << "original_string: " << right << _original_path << endl;
    cout << setw(w) << left << "game_name: "       << right << _fd.game_name << endl;
    cout << setw(w) << left << "file_type: "       << right << _fd.file_type << endl;
    cout << setw(w) << left << "day: "             << right << _fd.day << endl;
    cout << setw(w) << left << "day_name: "        << right << _fd.day_name << endl;
    cout << setw(w) << left << "month: "           << right << _fd.month << endl;
    cout << setw(w) << left << "month_name: "      << right << _fd.month_name << endl;
    cout << setw(w) << left << "year: "            << right << _fd.year << endl;
    cout << setw(w) << left << "time_ms: "         << right << _fd.time_ms << endl;
    cout << setw(w) << left << "time_sec: "        << right << _fd.time_sec << endl;
    cout << setw(w) << left << "time_min: "        << right << _fd.time_min << endl;
    cout << setw(w) << left << "time_hr: "         << right << _fd.time_hr << endl;
}
