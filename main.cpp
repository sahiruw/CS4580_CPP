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
	int idx = 0;
	bool intervalTreeFull = false;

    try {
        InputFileHandler fileReader(filename, bufferSize);
		IntervalHeap intervalHeap(16);

		OutputBuffer smallBuffer("small-" + to_string(idx) + ".txt", 3);
		OutputBuffer largeBuffer("large-" + to_string(idx) + ".txt", 3);

        while (fileReader.hasMoreData()) {
            vector<int> part = fileReader.readNextPart();
            cout << "Read " << part.size() << " numbers " << sizeof(part)/1024/1024 << endl;

            for (int number : part) {
				if (intervalHeap.isFree() && !intervalTreeFull) {
					intervalHeap.insert(number);
				} else {
					intervalTreeFull = true;
					
					
					if (number > intervalHeap.seeMax()) {
						largeBuffer.addData(number);
					}
					else if (number < intervalHeap.seeMin()) {
						smallBuffer.addData(number);
					}
					else {
						int min = intervalHeap.extractMin();
						smallBuffer.addData(min);
						intervalHeap.insert(number);
					}
				}
            }
        }

    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}
