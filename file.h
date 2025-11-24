#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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

void file_read(ifstream &f, vector<trash> &items) //put things in the file into classes
{
    items.reserve(100);//reserve the space
    string line;
        // Read the rest of the file
    //cout << "Reading remaining lines:\n";
    while (getline(f, line)) {
        //cout << line << endl;
        if (line.empty()) continue;

        string id_str, name, type;
        stringstream ss(line);

        // split by comma
        getline(ss, id_str, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');

        int id = stoi(id_str);

        items.emplace_back(id, name, type);

    }
}

void file_close(ifstream &f)
{
    if(f.is_open());
    f.close();
}




#endif