#pragma once
#include <iostream>
#include <fstream>
#include <string>

class ReadFile
{
    public:
        int read_file(std::string fileLoc);
};

int ReadFile::read_file(std::string fileLoc) {
    std::ifstream file_in;
    file_in.open(fileLoc);
    if (!file_in.is_open()) {
        return -1;
    }
    std::string line;
    int nr_frames = 0;
    while (std::getline(file_in, line)) { // search first 2 numbers from file
        for (auto i : line) {
            if (isdigit(i)) {
                nr_frames = nr_frames * 10 + i - '0';
            }
        }
    }
    file_in.close();
    return nr_frames;
}