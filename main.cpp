#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std; 	

#include "interval_heap.h"
#include "InputFileHandler.h"
#include "file_operations.h"
#include "OutputBuffer.h"


void external_sort(string filename, int startindex, InputFileHandler &fileReader, IntervalHeap &intervalHeap, OutputBuffer &smallBuffer, OutputBuffer &largeBuffer) {
	cout << "External Sort called for " << filename << endl; 
	
	fileReader.openFile(filename);
	if (!fileReader.hasMoreData()) {
		cout << "No more data to read" << endl;
        return;
    }
	
	bool intervalTreeFull = false;
	int minOrMaxFlag = false;

	while (fileReader.hasMoreData()) {
		vector<int> part = fileReader.readNextPart();
		cout << "Read 	" << part.size() << " numbers " << intervalHeap.getSize() << "hehe" << endl;

		for (int number : part) {
			if (!intervalTreeFull && intervalHeap.isFree() ) {
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

	intervalHeap.saveToFile("sorted" + to_string(startindex) + ".txt");

	external_sort("small_temp.txt", startindex + 1, fileReader, intervalHeap, smallBuffer, largeBuffer);
	external_sort("large_temp.txt", startindex + 2, fileReader, intervalHeap, smallBuffer, largeBuffer);

}



void run() {
	generate_file("data3.txt");
	cout << "File Genrated" << endl;
    string filename = "data3.txt";


	size_t bufferSize = 1024*1024*3; 
	InputFileHandler fileReader(bufferSize);
	IntervalHeap intervalHeap(2);

	OutputBuffer smallBuffer("small.txt", 1);
	OutputBuffer largeBuffer("large.txt", 1);
    
	external_sort(filename, 0, fileReader, intervalHeap, smallBuffer, largeBuffer);
	// external_sort("small.txt", 0, fileReader, intervalHeap, smallBuffer, largeBuffer);

	// cout << "End of main" << endl;
}



void test() {
	IntervalHeap intervalHeap(7);

	intervalHeap.insert(3);
	intervalHeap.insert(2);
	intervalHeap.insert(15);
	intervalHeap.insert(5);
	intervalHeap.insert(4);
	intervalHeap.insert(45);
	intervalHeap.insert(10);

	intervalHeap.print();

	// cout << "The Min val is " << intervalHeap.extractMin() << endl;
	intervalHeap.print();
	// cout << "The Min val is " << intervalHeap.extractMin() << endl;
	intervalHeap.print();
	// cout << "The Min val is " << intervalHeap.extractMin() << endl;
	intervalHeap.print();



	// cout << "The Max val is " << intervalHeap.extractMax() << endl;
	intervalHeap.print();
	// cout << "The Max val is " << intervalHeap.extractMax() << endl;
	intervalHeap.print();
	// cout << "The Max val is " << intervalHeap.extractMax() << endl;
	intervalHeap.print();
	// cout << "The Max val is " << intervalHeap.extractMax() << endl;
	intervalHeap.print();
	// // cout << "The Max val is " << intervalHeap.extractMax() << endl;
	// intervalHeap.print();
	// // cout << "The Max val is " << intervalHeap.extractMax() << endl;
	// intervalHeap.print();
	// // cout << "The Max val is " << intervalHeap.extractMax() << endl;
	// intervalHeap.print();
	// // cout << "The Max val is " << intervalHeap.extractMax() << endl;
	// intervalHeap.print();
	// cout << "The Max val is " << intervalHeap.extractMax() << endl;
	intervalHeap.print();

}


int main () {
	// test();
	run();
	return 0;
}