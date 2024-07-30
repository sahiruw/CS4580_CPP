#ifndef INTERVAL_HEAP_H
#define INTERVAL_HEAP_H

struct Node {
    int low;
    int high;

    Node() {
        this->low = -1;
        this->high = -1;
    }
};

class IntervalHeap {
    public:
        IntervalHeap(int capacity);
        ~IntervalHeap();
        void insert(int value);
        int extractMin();
        int extractMax();
        int seeMin();
        int seeMax();
        void print();
        bool isFree();
        int getSize();

    private:
        int capacity;
        int size;
        Node* heap;
        void heapifyUp(int index);
        void heapifyDownMin(int index);
        void heapifyDownMax(int index);
        int getParent(int index);
        int getLeftChild(int index);
        int getRightChild(int index);
        void swapifNeeded(int rightChildIndex, int index);
};



#endif
