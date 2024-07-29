#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>

class InputFileHandler {
public:
    InputFileHandler(const std::string& filename, std::size_t bufferSize);

    std::vector<int> readNextPart();

    bool hasMoreData();
private:
    std::string filename;
    std::size_t bufferSize;
    std::ifstream file;
    std::streampos currentPosition;
};

#endif // FILEHANDLER_H
