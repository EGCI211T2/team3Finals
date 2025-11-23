#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <conio.h>
#include <map>
#include <functional>


using namespace std;

#include "trash.h"
#include "node.h"
#include "file.h"
#include "searchSuggestion.h"

int main() {

    ifstream myfile;

    open_file(myfile, "Trash_list.txt");

    skip_lines(myfile, 3);

    /*put the value from the file into class*/
    vector<trash>items;
    file_read(myfile, items);

    //check if everything is in there
    cout << "Total items loaded: " << items.size() << endl;

    for (int i = 0; i < items.size(); i++)
    {
        cout << "Item " << i + 1 << ": ";
        items[i].print();
    }

    cout << endl;

        //converting string arr to vector
    std::string stringArr[] = {"plastic", "paper", "plastic bag", "banana"}; //for compatability (this an example)
    int arraySize = sizeof(stringArr)/sizeof(stringArr[0]); 
    std::vector<std::string> dictionary(stringArr, stringArr + arraySize); //range constructor

    //searchSuggestion
    std::string input = runAutocomplete(dictionary); //this junk uses vectors not string arrays

    std::cout << "\n" << input << std::endl;

    file_close(myfile);
    return 0;
}
