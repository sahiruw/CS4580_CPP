#include "FileMerger.h"
#include <fstream>

namespace fs = std::filesystem;

// Constructor
FileMerger::FileMerger(const std::map<int, int>& parentChildRels) : parent_child_rels(parentChildRels) {
    buildTree();
}

// Function to build the tree structure from the parent-child map
void FileMerger::buildTree() {
    for (const auto& [child, parent] : parent_child_rels) {
        tree[parent].push_back(child);
    }
}

// Function to perform in-order traversal and collect file order
void FileMerger::inorderTraversal(int node, std::vector<std::string>& fileOrder) {
    if (tree.find(node) == tree.end()) {
        // If this node has no children, add its corresponding file to the order
        fileOrder.push_back("sorted" + std::to_string(node) + ".txt");
        return;
    }

    const auto& children = tree.at(node);
    if (!children.empty()) {
        // Traverse the left child (if it exists)
        if (children.size() > 0) {
            inorderTraversal(children[0], fileOrder);
        }

        // Add the current node's file to the order
        fileOrder.push_back("sorted" + std::to_string(node) + ".txt");

        // Traverse the right child (if it exists)
        if (children.size() > 1) {
            inorderTraversal(children[1], fileOrder);
        }
    } else {
        // Add the current node's file to the order
        fileOrder.push_back("sorted" + std::to_string(node) + ".txt");
    }
}

// Function to merge files in the order determined by the in-order traversal
void FileMerger::mergeFilesInOrder(const std::vector<std::string>& fileOrder, const std::string& outputFile) {
    std::ofstream output(outputFile);

    for (const auto& filename : fileOrder) {
        std::ifstream input(fs::path("Files") / filename);
        output << input.rdbuf(); // Write the content of the file to the output
        input.close();
    }

    output.close();
}

// Function to perform the merging process
void FileMerger::mergeFiles(const std::string& outputFile) {
    // Step 1: Identify the root nodes
    std::set<int> all_nodes;
    std::set<int> child_nodes;

    for (const auto& [child, parent] : parent_child_rels) {
        all_nodes.insert(child);
        all_nodes.insert(parent);
        child_nodes.insert(child);
    }

    std::vector<int> root_nodes;
    for (int node : all_nodes) {
        if (child_nodes.find(node) == child_nodes.end()) {
            root_nodes.push_back(node);
        }
    }

    // Step 2: Perform in-order traversal and collect the file order
    std::vector<std::string> file_order;
    for (int root : root_nodes) {
        inorderTraversal(root, file_order);
    }

    // Step 3: Merge files in the order determined by the in-order traversal
    mergeFilesInOrder(file_order, outputFile);

    std::cout << "Files merged successfully into '" << outputFile << "'." << std::endl;
}

