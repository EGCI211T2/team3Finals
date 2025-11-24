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
#include "trashType.h"
#include "manager.h"


int main() {

    ifstream myfile; // for file stuff
    Manager m; // for trash linked lists

    open_file(myfile, "Trash_list.txt");

    skip_lines(myfile, 3);

    /*put the value from the file into class*/
    vector<trash>items;
    file_read(myfile, items);

    //check if everything is in there
    #if 0
    cout << "Total items loaded: " << items.size() << endl;

    for (int i = 0; i < items.size(); i++)
    {
        cout << "Item " << i + 1 << ": ";
        items[i].print();
    }

    cout << endl;
    #endif
    
    //put name of trash into another vector for the searchsuggestion
    vector<string>dictionary;
    for (int i = 0; i < items.size(); i++) {
        dictionary.push_back(items[i].getName());
    }    

    while(1){
        //searchSuggestion
        std::string input = runAutocomplete(dictionary); //this junk uses vectors not string arrays

        if(input == ""){ // stops asking for more inputs when user press ESC
            break;
        }
        
        //gets information and adds trash to appropriate linked list
        int i=0;
        for(i; i<items.size(); i++){
            if(items[i].getName() == input){
                break;
            }
        }
        
        m.addTrash(items[i].getID(), items[i].getName(), items[i].getType());
    }

    m.printAll();

    file_close(myfile);
    return 0;
}
