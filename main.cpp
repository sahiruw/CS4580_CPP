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


void external_sort(string filename, int startindex, InputFileHandler &fileReader, IntervalHeap &intervalHeap, OutputBuffer &smallBuffer, OutputBuffer &largeBuffer) {
	int idx = 0;
	bool intervalTreeFull = false;
	int minOrMaxFlag = false;

	while (fileReader.hasMoreData()) {
		vector<int> part = fileReader.readNextPart();
		// cout << "Read 	" << part.size() << " numbers " << intervalHeap.getSize() << "hehe" << endl;

		for (int number : part) {
			// cout << "The  number is " << number << endl;
			if (!intervalTreeFull && intervalHeap.isFree() ) {
				// cout << "Inserting to initializing heap " << number << endl;
				intervalHeap.insert(number);
			} 
			else {
				intervalTreeFull = true;
				
				if (number > intervalHeap.seeMax()) {
					// cout << "Adding to large buffer " << number << endl;
					largeBuffer.addData(number);
				}
				else if (number < intervalHeap.seeMin()) {
					// cout << "Adding to small buffer " << number << endl;
					smallBuffer.addData(number);
				}
				else {
					// if (minOrMaxFlag == true){
					// 	// cout << "Extracting min " << intervalHeap.seeMin() << endl;
					// 	int min = intervalHeap.extractMin();
					// 	smallBuffer.addData(min);
					// 	intervalHeap.print();
					// 	intervalHeap.insert(number);
					// }
					// else {
					// 	// cout << "Extracting max " << intervalHeap.seeMax() << endl;
					// 	int max = intervalHeap.extractMax();
					// 	largeBuffer.addData(max);
					// 	intervalHeap.print();
					// 	intervalHeap.insert(number);
					// }
					// // cout << "Inserting " << number << endl;
					
					// minOrMaxFlag = !minOrMaxFlag;
				}
			}

			
			intervalHeap.print();
		}

		
	}

	cout << intervalHeap.seeMin() << " " << intervalHeap.seeMax() << endl;

	smallBuffer.flushToDisk();
	largeBuffer.flushToDisk();

}



void run() {
	// generate_file("data1.txt");
	cout << "File Genrated" << endl;
    string filename = "data2.txt";


	size_t bufferSize = 1024*1024*7*3; 
	InputFileHandler fileReader(filename, bufferSize);
	IntervalHeap intervalHeap(8);

	OutputBuffer smallBuffer("small.txt", 3);
	OutputBuffer largeBuffer("large.txt", 3);
    
	external_sort(filename, 0, fileReader, intervalHeap, smallBuffer, largeBuffer);

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