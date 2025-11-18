#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "trash.h"
#include "node.h"
#include "file.h"

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
    file_close(myfile);
    return 0;
}
