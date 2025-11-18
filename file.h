#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void open_file(ifstream &f, const string &filename)
{
    f.open(filename);
    if (!f.is_open()) {
        cerr << "Error: Could not open file.\n";
    }
}

void skip_lines(ifstream &f, int n)// n for line skips in the files
{
    string line;
    for (int i = 0; i < n; i++) {
        if (!getline(f, line)) {
            cerr << "Error: File has fewer than " << n <<" lines.\n";
        }
    }
}

void file_read(ifstream &f)
{
    string line;
        // Read the rest of the file
    cout << "Reading remaining lines:\n";
    while (getline(f, line)) {
        cout << line << endl;
    }
}

void file_close(ifstream &f)
{
    if(f.is_open());
    f.close();
}




#endif