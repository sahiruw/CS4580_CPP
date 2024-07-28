#include "interval_heap.h"
#include <iostream>
using namespace std;


IntervalHeap::IntervalHeap(int memory_capacity) {
    this->capacity = memory_capacity* 1024 * 1024 / sizeof(Node);
    this->size = 0;
    this->heap = new Node[capacity];
}

IntervalHeap::~IntervalHeap() {
    delete[] heap;
}

void IntervalHeap::insert(int value) {
    if (size == capacity) {
        return;
    }

    if (heap[size].low == -1 && heap[size].high == -1) {
        if (heap[0].high < value) {
            heap[size].high = value;
        } else {
            heap[size].low = value;
        }

        heapifyUp(size);
    }
    else {
        if (heap[size].low == -1) {
            heap[size].low = value;}

         else {
            heap[size].high = value;
        }

        if (heap[size].low > heap[size].high) {
            swap(heap[size].low, heap[size].high);
        }

        heapifyUp(size);
        size++;
    }
    

}

int IntervalHeap::seeMin() {
    return heap[0].low;
}

int IntervalHeap::seeMax() {
    return heap[0].high;
}

int IntervalHeap::extractMin() {
    int min = heap[0].low;

    // bring the last element to the root
    if (heap[size].low != -1) {
        heap[0].low = heap[size].low;
        heap[size].low = heap[size].high;
        heap[size].high = -1;
    } else {
        heap[0].low = heap[size].high;
        heap[size].high = -1;
    }

    // delete the last element if null
    if (heap[size].low == -1 && heap[size].high == -1) {
        size--;
    }
    

    heapifyDown(0);

    return min;
}

void IntervalHeap::heapifyUp(int index) {
    if (index == 0) {
        return;
    }

    int parentIndex = getParent(index);
    if (heap[index].low != -1 && heap[parentIndex].low > heap[index].low) {
        swap(heap[parentIndex].low, heap[index].low);
    }

    if (heap[index].high != -1 && heap[parentIndex].high < heap[index].high) {
        swap(heap[parentIndex].high, heap[index].high);
    }

    if (heap[parentIndex].low > heap[parentIndex].high) {
        swap(heap[parentIndex].low, heap[parentIndex].high);
    }

    if (heap[index].low > heap[index].high) {
        swap(heap[index].low, heap[index].high);
    }

    heapifyUp(parentIndex);
}

void IntervalHeap::heapifyDown(int index) {
    if (index >= size) {
        return;
    }

    int leftChildIndex = getLeftChild(index);
    int rightChildIndex = getRightChild(index);

    swapifNeeded(leftChildIndex, index);
    swapifNeeded(rightChildIndex, index);

    
}


void IntervalHeap::swapifNeeded(int childIndex, int parentIndex) {
    if (childIndex <= size) {
        if (heap[childIndex].low < heap[parentIndex].low) {
            swap(heap[childIndex].low, heap[parentIndex].low);
        }

        if (heap[childIndex].high > heap[parentIndex].high) {
            swap(heap[childIndex].high, heap[parentIndex].high);
        }

        if (heap[childIndex].low > heap[childIndex].high) {
            swap(heap[childIndex].low, heap[childIndex].high);
        }

        if (heap[parentIndex].low > heap[parentIndex].high) {
            swap(heap[parentIndex].low, heap[parentIndex].high);
        }

        heapifyDown(childIndex);
    }
}

void IntervalHeap::print() {
    for (int i = 0; i < size+1; i++) {
        cout << "[" << heap[i].low << ", " << heap[i].high << "] ";
    }
    cout << endl;
}

int IntervalHeap::getParent(int index) {
    return (index - 1) / 2;
}

int IntervalHeap::getLeftChild(int index) {
    return 2 * index + 1;
}

int IntervalHeap::getRightChild(int index) {
    return 2 * index + 2;
}