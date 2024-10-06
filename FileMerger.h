#ifndef FILEMERGER_H
#define FILEMERGER_H

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <filesystem>

class FileMerger {
public:
    // Constructor
    FileMerger(const std::map<int, int>& parentChildRels);

    // Function to perform the merging process
    void mergeFiles(const std::string& outputFile);

private:
    std::map<int, int> parent_child_rels;
    std::map<int, std::vector<int>> tree;

    // Helper function to build the tree structure
    void buildTree();

    // Helper function to perform in-order traversal and collect file order
    void inorderTraversal(int node, std::vector<std::string>& fileOrder);

    // Helper function to merge files in the order determined by the in-order traversal
    void mergeFilesInOrder(const std::vector<std::string>& fileOrder, const std::string& outputFile);
};

#endif // FILEMERGER_H
