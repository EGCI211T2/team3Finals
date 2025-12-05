#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <utility>
#include <typeinfo>

// For non-blocking input (platform-specific)
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

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

    #if 0
    for(int i = 0; i < binNery.size(); i++) {
        binNery[i].print();
    }
    #endif

    // fancy scanf for user input coordinates of origin
    string buffer;
    char leComma;
    double userX = 0, userY = 0;
    double myDouble = 29.32;
    
    cout << "Welcome to trash+, where you can find where to throw your trash away." << endl;
    cout << "Enter your coordinates, and trash(s)' name that you would like to throw away." << endl;
    cout << "The program will tell you the type of trash and the closest bin to you." << endl << endl;

    do { // input protection for user cords
        cout << "Enter coordinates of origin (x,y): ";
        getline(cin, buffer);

        stringstream ss(buffer);
        if (!(ss >> userX >> leComma >> userY)) { // check input
            leComma = '\0'; // force failure
            cout << "invalid, try again" << endl;
        }

    } while (leComma != ',');
    
    

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
        
        m.addTrash(
            dictionary.second[i].getID(), 
            dictionary.second[i].getName(), 
            dictionary.second[i].getType()
        );
    }

    pair<vector<trashBin>, vector<vector<int>>> result = m.computeRoute(binNery, userX, userY);

    m.printBinWithTrash(result);
    //m.printAll(); // lists user input trash

    return 0;
}