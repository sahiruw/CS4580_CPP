#ifndef OUTPUTBUFFER_H
#define OUTPUTBUFFER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

class OutputBuffer {
public:
    OutputBuffer(const std::string& filename, std::size_t bufferSizeMB);
    ~OutputBuffer();

    void addData(int data);
    void flushToDisk();
    int getBufferSize() { return buffer.size(); }

private:
    std::string filename;
    std::size_t bufferSize;
    std::vector<int> buffer;
    std::ofstream file;

    void saveToDisk();
};

#endif // OUTPUTBUFFER_H
