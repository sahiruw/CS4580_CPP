#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <filesystem> // Add this line

using namespace std;

#include "file_operations.h"

void generate_file(const string &file_name)
{
    const int file_size = 256/8;
    const int no_of_items = file_size * 1024 * 1024 / sizeof(int);

    if (filesystem::exists(file_name)) { // Use fs::exists instead of filesystem::exists
        cout << "File " << file_name << " already exists." << endl;
        return;
    }

    ofstream file(file_name, ios::out);

    cout << "Generating file " << file_name << " with " << no_of_items << " integers." << endl;

    std::random_device rd;                             
    std::mt19937 gen(rd());                            
    std::uniform_int_distribution<> distr(0, 1000000);

    for (int i = 0; i < no_of_items; i++)
    {
        file << distr(gen) << endl;
    }
}