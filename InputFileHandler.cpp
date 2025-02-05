#include "InputFileHandler.h"
#include <iostream>

using namespace std; 	

InputFileHandler::InputFileHandler(std::size_t bufferSize) {
    this->bufferSize = bufferSize;
    this->currentPosition = 0;

}

void InputFileHandler::openFile(const std::string& filename) {
    // Close the current file if it is open
    if (this->file.is_open()) {
        this->file.close();
    }

    this->currentPosition = 0;
    this->filename = filename;

    std::cout << "Opening file " << filename << std::endl;
    this->file.open(filename, std::ios::binary);

    if (!this->file) {
        throw std::runtime_error("Unable to open file");
    }

}


std::vector<int> InputFileHandler::readNextPart() {
    file.seekg(currentPosition);

    std::vector<char> buffer(bufferSize);
    file.read(buffer.data(), bufferSize);
    std::streamsize bytesRead = file.gcount();

    currentPosition += bytesRead;

    std::string bufferStr(buffer.data(), bytesRead);
    std::istringstream stream(bufferStr);

    std::vector<int> numbers;
    std::string temp;
    while (std::getline(stream, temp, '\n')) {
        if (!temp.empty()) {
            numbers.push_back(std::stoi(temp));
        }
    }

    return numbers;
}

bool InputFileHandler::hasMoreData() {
    // cout << "Peek is " << file.peek() << endl;
    return file.peek() != EOF;
}