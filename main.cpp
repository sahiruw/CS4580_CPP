#include <iostream>
#include <array>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <stdexcept>
#include <set>
#include <chrono> // Include chrono for timing

using namespace std; 	

#include "interval_heap.h"
#include "InputFileHandler.h"
#include "file_operations.h"
#include "OutputBuffer.h"
#include "FileMerger.h"

int external_sort(string filename, int startindex, InputFileHandler &fileReader, IntervalHeap &intervalHeap, map<int, int> &parent_child_rels) {
	cout << "External Sort called for " << filename << endl; 

	fileReader.openFile(filename);
	if (!fileReader.hasMoreData()) {
		cout << "No more data to read" << endl;
        return startindex - 1;
    }

	OutputBuffer smallBuffer("Files/small" + to_string(startindex) + ".txt", 1);
	OutputBuffer largeBuffer("Files/large" + to_string(startindex) + ".txt", 1);
	
	bool intervalTreeFull = false;
	int minOrMaxFlag = false;

	

	while (fileReader.hasMoreData()) {
		vector<int> part = fileReader.readNextPart();
		cout << "Read " << part.size() << " numbers " << intervalHeap.getSize() << endl;

		for (int number : part) {
			if (!intervalTreeFull && intervalHeap.isFree()) {
				intervalHeap.insert(number);
			} 
			else {
				intervalTreeFull = true;
				
				if (number > intervalHeap.seeMax()) {
					largeBuffer.addData(number);
				}
				else if (number < intervalHeap.seeMin()) {
					smallBuffer.addData(number);
				}
				else {
					if (minOrMaxFlag == true){
						int min = intervalHeap.extractMin();
						smallBuffer.addData(min);
						intervalHeap.insert(number);
					}
					else {
						int max = intervalHeap.extractMax();
						largeBuffer.addData(max);
						intervalHeap.insert(number);
					}
					
					minOrMaxFlag = !minOrMaxFlag;
				}
			}
		}
	}

	cout << intervalHeap.seeMin() << " " << intervalHeap.seeMax() << endl;

	smallBuffer.flushToDisk();
	largeBuffer.flushToDisk();

	intervalHeap.saveToFile("Files/sorted" + to_string(startindex) + ".txt");

	int lastindex = external_sort("Files/small" + to_string(startindex) + ".txt", startindex + 1, fileReader, intervalHeap, parent_child_rels);
	int lastIndexTemp = lastindex;
	lastindex = external_sort("Files/large" + to_string(startindex) + ".txt", lastindex + 1, fileReader, intervalHeap, parent_child_rels);

	if (lastindex != startindex) {
		parent_child_rels[lastIndexTemp + 1] = startindex;
		parent_child_rels[startindex + 1] = startindex;
	}



	return lastindex;
}


void actual_external_sort(string filename) {

	size_t bufferSize = 1024 * 1024 * 3; 
	InputFileHandler fileReader(bufferSize);
	IntervalHeap intervalHeap(2);
	
	map<int, int> parent_child_rels;

	external_sort(filename, 0, fileReader, intervalHeap, parent_child_rels);

	FileMerger fileMerger(parent_child_rels);
    fileMerger.mergeFiles("merged_output.txt");
}


void run() {
	generate_file("data3.txt");
	cout << "File Generated" << endl;
    string filename = "data3.txt";

	auto start = chrono::high_resolution_clock::now(); // Start timing
	actual_external_sort(filename);

	auto end = chrono::high_resolution_clock::now(); // End timing
	chrono::duration<double> duration = end - start; // Calculate duration
	cout << "Sorting completed in " << duration.count() << " seconds." << endl; // Log duration
}


int main() {
	run();
	return 0;
}
