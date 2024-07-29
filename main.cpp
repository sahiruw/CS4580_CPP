#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std; 	

#include "interval_heap.h"
#include "InputFileHandler.h"
#include "file_operations.h"
#include "OutputBuffer.h"


int main() {
    string filename = "data1.txt";
    size_t bufferSize = 1024*1024*3; 

    try {
        InputFileHandler fileReader(filename, bufferSize);
		IntervalHeap intervalHeap(16);
		
		OutputBuffer smallBuffer("small.txt", 3);
		OutputBuffer largeBuffer("large.txt", 3);

        while (fileReader.hasMoreData()) {
            vector<int> part = fileReader.readNextPart();
            cout << "Read " << part.size() << " numbers " << sizeof(part)/1024/1024 << endl;

            for (int number : part) {
				if (intervalHeap.isFree()) {
					intervalHeap.insert(number);
				} else {
					cout << "Heap is full" << endl;
				}
            }
        }

    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}
