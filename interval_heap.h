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
        int seeMin();
        int seeMax();
        void print();

    private:
        int capacity;
        int size;
        Node* heap;
        void heapifyUp(int index);
        void heapifyDown(int index);
        int getParent(int index);
        int getLeftChild(int index);
        int getRightChild(int index);
        void swapifNeeded(int rightChildIndex, int index);
};



#endif
