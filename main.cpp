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
					int min = intervalHeap.extractMin();
					smallBuffer.addData(number);
					intervalHeap.insert(number);
				}
			}
		}

		
	}

	smallBuffer.flushToDisk();
	largeBuffer.flushToDisk();

	

}


int main() {
	generate_file("data2.txt");
	cout << "File Genrated" << endl;
    string filename = "data2.txt";


	size_t bufferSize = 1024*1024*7*3; 
	InputFileHandler fileReader(filename, bufferSize);
	IntervalHeap intervalHeap(7);

	OutputBuffer smallBuffer("small.txt", 3);
	OutputBuffer largeBuffer("large.txt", 3);
    
	external_sort(filename, 0, fileReader, intervalHeap, smallBuffer, largeBuffer);

	cout << "End of main" << endl;
    return 0;
}



// int main() {
// 	IntervalHeap intervalHeap(7);

// 	intervalHeap.insert(3);
// 	intervalHeap.insert(2);
// 	intervalHeap.insert(15);
// 	intervalHeap.insert(5);
// 	intervalHeap.insert(4);
// 	intervalHeap.insert(45);
// 	intervalHeap.insert(10);

// 	intervalHeap.print();

// 	cout << "The Min val is " << intervalHeap.extractMin() << endl;
// 	intervalHeap.print();
// 	cout << "The Min val is " << intervalHeap.extractMin() << endl;
// 	intervalHeap.print();
// 	cout << "The Min val is " << intervalHeap.extractMin() << endl;
// 	intervalHeap.print();
// 	cout << "The Min val is " << intervalHeap.extractMin() << endl;
// 	intervalHeap.print();
// 	cout << "The Min val is " << intervalHeap.extractMin() << endl;
// 	intervalHeap.print();
// 	cout << "The Min val is " << intervalHeap.extractMin() << endl;
// 	intervalHeap.print();
// 	cout << "The Min val is " << intervalHeap.extractMin() << endl;
// 	intervalHeap.print();
// 	cout << "The Min val is " << intervalHeap.extractMin() << endl;
// 	intervalHeap.print();
// 	cout << "The Min val is " << intervalHeap.extractMin() << endl;
// 	intervalHeap.print();

// }