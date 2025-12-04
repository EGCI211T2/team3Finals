#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>

#include "trash.h"
#include "trashBin.h"

void open_file(ifstream &f, const string &filename)
{
    f.open(filename);
    if (!f.is_open()) {
        cerr << "Error: Could not open file.\n";
    }
}

#ifndef _WIN32
void normalize(std::string &s) { 
    // Remove UTF-8 BOM
    if (s.size() >= 3 &&
        (unsigned char)s[0] == 0xEF &&
        (unsigned char)s[1] == 0xBB &&
        (unsigned char)s[2] == 0xBF) {
        s.erase(0, 3);
    }

    // Remove trailing '\r' from Windows CRLF files
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
}
#endif

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
    cout << "Reading remaining lines:\n";
    while (getline(f, line)) {
        //cout << line << endl;
        if (line.empty()) continue;

        string id_str, name, type;
        stringstream ss(line);

        // split by comma
        getline(ss, id_str, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');

        #ifndef _WIN32
        normalize(id_str);
        normalize(name);
        normalize(type);
        #endif

        int id = stoi(id_str);

        items.emplace_back(id, name, type);

    }
}

void file_close(ifstream &f)
{
    if(f.is_open());
    f.close();
}

std::pair<std::vector<string>, std::vector<trash>> wordBank(string name) {
    ifstream myfile; // for file stuff

    open_file(myfile, name);

    skip_lines(myfile, 3);

    /*put the value from the file into class*/
    vector<trash>items;
    file_read(myfile, items);

    file_close(myfile);

    std::vector<string>dictionary;
    for (int i = 0; i < items.size(); i++) {
        dictionary.push_back(items[i].getName());
    }    

    return {dictionary, items};
}

std::vector<trashBin> binBank() {
    ifstream myfile;
    std::vector<trashBin>binlog;
    string name = "Trash_Site.txt";

    open_file(myfile, name);

    skip_lines(myfile, 3);

    binlog.reserve(100);//reserve the space
    string line;
        // Read the rest of the file
    cout << "Reading remaining lines:\n";
    while (getline(myfile, line)) {
        //cout << line << endl;
        if (line.empty()) continue;

        string id_str, name, cat, x, y;
        stringstream ss(line);

        // split by comma
        getline(ss, id_str, ',');
        getline(ss, name, ',');
        getline(ss, x, ',');
        getline(ss, y, ',');
        getline(ss, cat, ',');

        #ifndef _WIN32
        normalize(id_str);
        normalize(name);
        normalize(x);
        normalize(y);
        normalize(cat);
        #endif

        int id = stoi(id_str);

        int catArr[8];
        int i = 0;
        
        for(char c : cat) {
            catArr[i] = c - '0';  // convert '0' or '1' → int 0 or 1
            i++;
        }

        binlog.emplace_back(stoi(id_str), name, stod(x), stod(y), catArr);

    }
    return binlog;
}


#endif