#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <conio.h>
#include <map>
#include <functional>
#include <utility>


using namespace std;

#include "trash.h"
#include "node.h"
#include "file.h"
#include "searchSuggestion.h"
#include "trashType.h"
#include "manager.h"


int main() {

    Manager m; // for trash linked lists
    
    //put name of trash and trash nodes into separate vectors for the searchsuggestion (.first is the string, .second is the trash node)
    pair<vector<string>, vector<trash>> dictionary=wordBank("Trash_list.txt");

    //put trashBin nodes into a vector
    std::vector<trashBin> binNery = binBank();
    

    while(1){
        //searchSuggestion
        std::string input = runAutocomplete(dictionary.first); //this junk uses vectors not string arrays

        if(input == ""){ // stops asking for more inputs when user press ESC
            break;
        }
        
        //gets information and adds trash to appropriate linked list
        int i=0;
        for(i; i<dictionary.second.size(); i++){
            if(dictionary.second[i].getName() == input){
                break;
            }
        }
        
        m.addTrash(dictionary.second[i].getID(), dictionary.second[i].getName(), dictionary.second[i].getType());
    }

    m.printAll();

    //file_close(myfile);
    return 0;
}
