#include "../include/file_manip.h"

int main() {
    /* TODO: 
     * SPFF
     * ACCOUNT FOR LEAP YEAR
     * Main menu: Options, list of dirs to edit, etc. (Have option to go to previous menu)
     * Get confirmation from user and show preview of change.
     * Change the need for tokenizing and use std::filesystem to get file info.
     * CHECK IF FILE NAME HAS ALREADY BEEN MODIFIED
     * Create a backup that keeps original file names, and use it if the user wants to revert the changes.
     * Loading bar!
     * Use a mapping
     * eh: Add option to not override files with custom names (i.e. does not match the expected format based on its file data)
     * Put .exe in a dir, dir in the shadowplay dir, use ../${path} to access previous dir.
     * Comments.
     * Make a vector that stores the modified file names,
     * which you can use to check for duplicates, check if size
     * of it is the same as _files for correctness, etc. 
     * 
     * BUGS:
     * Everything
     * 
     */

    // Merely small test cases
    std::string str1("Apex Legends 2023.06.28 - 16.48.27.13.DVR.mp4");
    std::string str2("Dark Souls III 05.23.2017 - 15.21.40.01.mp4");
    std::string str3("Death Stranding Screenshot 2020.08.21 - 19.44.38.15.png");
    
    FileData ed1(str1);
    ed1.print_data();
    std::cout << std::endl;

    FileData ed2(str2);
    ed2.print_data();
    std::cout << std::endl;

    FileData ed3(str3);
    ed3.print_data();
    std::cout << std::endl;

    FileManip fm("G:\\Battlebit Remastered\\test");
    fm.set_user_filename_format("{gn} - {mns} {d}, {y} ({dns}) - {hr}h.{min}m.{sec}s"); 
    // fm.set_user_filename_format("{gn} - {mns} {d}, {y} ({dns})"); 
    fm.rename_files();

    return 0;
}

