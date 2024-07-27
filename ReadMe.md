CS4580 Advanced Data Structures
Lab 1
You are required to implement external sort using quick sort and merge sort as internal sorting methods.
You should use the below requirements.
Internal Memory that can be used for the program is 16 MB. You can partition the 16 MB for relevant
buffers as needed.
Size of the file with unsorted numbers is 256 MB. You can generate random numbers between 1 to one
Million for this purpose and should not be sorted.
For the quick sort adaptation, you need to implement and use an interval heap to find min and max. For
the rest of the algorithm, you can use the general quick sort and can allocate buffers as required within
16MB permitted memory.
For the Merge sort adaptation, you need to use tournament trees for optimum run generation and run
merging. Use K way merge algorithm for this purpose.
Note: You can use Huffman tree methods to improve the merging.
You should submit a report of comparing the run times of both external sorting methods for same
unsorted file. Also provide run times for 3 separate unsorted files.