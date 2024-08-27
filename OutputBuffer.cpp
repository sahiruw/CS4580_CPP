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
    // cout << "Flush to disk called" << endl;

    saveToDisk();
    saveFileCopy();
    clearOriginalFile();

    try {
        // close file
        file.close();
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

    buffer.clear(); // Clear the buffer after writing to the file
}


void OutputBuffer::saveFileCopy() {
    // Find the last dot in the filename to separate the extension
    std::size_t dotPosition = filename.find_last_of('.');

    std::string backupFilename = filename.substr(0, dotPosition) + "_temp" + filename.substr(dotPosition);

    std::ifstream src(filename, std::ios::binary);
    std::ofstream dst(backupFilename, std::ios::binary | std::ios::trunc);

    if (!src || !dst) {
        throw std::runtime_error("Unable to create backup file");
    }

    dst << src.rdbuf(); // Copy content from the original file to the backup

    std::cout << "Backup saved as " << backupFilename << std::endl;
}

void OutputBuffer::clearOriginalFile() {
    // Reopen the original file in truncation mode to clear its contents
    file.close(); // Close the current file stream
    file.open(filename, std::ios::trunc); // Open the file with truncation mode

    if (!file) {
        throw std::runtime_error("Unable to open file in truncation mode");
    }

    std::cout << "Original file " << filename << " cleared." << std::endl;

    // Close the file after truncation to ensure it is cleared
    file.close();
}