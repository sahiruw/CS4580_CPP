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
    file.open(filename,  std::ios::out);
    if (!file) {
        throw std::runtime_error("Unable to open file");
    }
}

OutputBuffer::~OutputBuffer() {
    cout << "Destructor called. Saving to " << filename << endl;
    // flushToDisk();
    file.close();
}

void OutputBuffer::addData(int data) {
    buffer.push_back(data);
    if (buffer.size() >= bufferSize) {
        saveToDisk();
    }
}

void OutputBuffer::flushToDisk() {
    // cout << "Flush to disk called" << endl;

    saveToDisk();

    try {
        // close file
        file.close();
    } catch (const std::exception &e) {
        std::cerr << "Error closing file: " << e.what() << std::endl;
    }
}


void OutputBuffer::saveToDisk() {
    std::cout << "Saving buffer to disk" << std::endl;

    // Close the existing file stream if open
    file.close();

    // Reopen the file in append mode
    file.open(filename, std::ios::app);
    if (!file) {
        throw std::runtime_error("Unable to open file in append mode");
    }

    // Use a string stream to accumulate the output
    std::ostringstream oss;

    // Write each integer from the buffer to the string stream
    for (int value : buffer) {
        oss << value << '\n';
    }

    // Write the entire content of the string stream to the file in one go
    file << oss.str();

    // Clear the buffer after writing to the file
    buffer.clear();

    // Close the file
    file.close();
}