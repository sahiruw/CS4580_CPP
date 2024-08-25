#include "OutputBuffer.h"
#include <iostream>
using namespace std; 

OutputBuffer::OutputBuffer(const std::string& filename, std::size_t bufferSizeMB) {
    this->filename = filename;
    this->bufferSize = bufferSizeMB * 1024 * 1024 / sizeof(int);
    this->buffer = std::vector<int>();

    if (std::filesystem::exists(filename)) {
        std::filesystem::remove(filename);
    }
    // file.open(filename,  std::ios::out);
    // if (!file) {
    //     throw std::runtime_error("Unable to open file");
    // }
}

OutputBuffer::~OutputBuffer() {
    cout << "Destructor called. Saving to " << filename << endl;
    flushToDisk();
    file.close();
}

void OutputBuffer::addData(int data) {
    buffer.push_back(data);
    if (buffer.size() >= bufferSize) {
        saveToDisk();
    }
}

void OutputBuffer::flushToDisk() {
    if (!buffer.empty()) {
        saveToDisk();
    }

    try {
        // close file
        // file.close();
        // cout << "File closed " << filename << endl;
    } catch (const std::exception &e) {
        std::cerr << "Error closing file: " << e.what() << std::endl;
    }
}


void OutputBuffer::saveToDisk() {
    std::cout << "Saving buffer to disk" << std::endl;
    // Use the existing file stream in append mode
    file.close(); // Close the existing file stream
    file.open(filename, std::ios::app); // Reopen the file in append mode

    if (!file) {
        throw std::runtime_error("Unable to open file in append mode");
    }

    // Write each integer from the buffer to the file in a readable format
    for (int value : buffer) {
        file << value << '\n'; // Write each integer on a new line
    }

    buffer.clear(); // Clear the buffer after writing
    file.close();
    cout << "Buffer saved to disk" << endl;
}

