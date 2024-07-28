#include <iostream> 
using namespace std; 	

#include "file_operations.h"
#include "interval_heap.h"

void external_sort(string input_file) {
		
}

int main() 
{ 
	generate_file("data1.txt");

	IntervalHeap interval_heap(7); // 7 MB

	interval_heap.insert(3);
	interval_heap.print();
	interval_heap.insert(2);
	interval_heap.print();
	interval_heap.insert(15);
	interval_heap.print();
	interval_heap.insert(5);
	interval_heap.print();
	interval_heap.insert(4);
	interval_heap.print();
	interval_heap.insert(45);
	interval_heap.print();
	interval_heap.insert(7);
	interval_heap.print();
	interval_heap.insert(6);
	interval_heap.print();
	interval_heap.insert(116);
	interval_heap.print();

	cout << "Removing min: " << interval_heap.extractMin() << endl;
	interval_heap.print();
	cout << "Removing min: " << interval_heap.extractMin() << endl;
	interval_heap.print();
	cout << "Removing min: " << interval_heap.extractMin() << endl;
	interval_heap.print();
	cout << "Removing min: " << interval_heap.extractMin() << endl;
	interval_heap.print();
	cout << "Removing min: " << interval_heap.extractMin() << endl;
	interval_heap.print();
	cout << "Removing min: " << interval_heap.extractMin() << endl;
	interval_heap.print();
	cout << "Removing min: " << interval_heap.extractMin() << endl;
	interval_heap.print();
	cout << "Removing min: " << interval_heap.extractMin() << endl;
	interval_heap.print();
	cout << "Removing min: " << interval_heap.extractMin() << endl;
	interval_heap.print();


	

	// cout << sizeof(Node) << endl;
	return 0; 
}
