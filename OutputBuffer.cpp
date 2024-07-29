#include "OutputBuffer.h"

OutputBuffer::OutputBuffer(const std::string& filename, std::size_t bufferSizeMB) {
    this->filename = filename;
    this->bufferSize = bufferSizeMB * 1024 * 1024 / sizeof(int);
    this->buffer = std::vector<int>();
    
    if (std::filesystem::exists(filename)) {
        std::filesystem::remove(filename); // Ensure the file does not already exist
    }
    file.open(filename, std::ios::binary | std::ios::out);
    if (!file) {
        throw std::runtime_error("Unable to open file");
    }
}

OutputBuffer::~OutputBuffer() {
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
}

void OutputBuffer::saveToDisk() {
    file.write(reinterpret_cast<char*>(buffer.data()), buffer.size() * sizeof(int));
    buffer.clear();
}
