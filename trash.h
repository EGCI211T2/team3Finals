/*Read the text file and turn it into array.

Test files 
Name of the trash and type of the trash

Then put them in class (separately)
Put those class into an array of classes.

function to add later if possible
Check all of the trash (use link list)
Add trash
Delete trash

When the program loads, everything has to be loaded in class.
Each trash will create its own class
Then put all of them class into an array of classes
Compare user input with the text file to determine the type of trash (search suggestion functions)
*/

#ifndef TRASH_H
#define TRASH_H

#include <cstring>
#include <iostream> 


class trash {
    
private:
    int id;
    string name;
    string type;
    trash* next;

public:
    trash();
    trash(int id, string name, string type);
    //void insert_trash (int x, string n, string t); //add the next node 
    string getName(){return name;}
    string getType(){return type;}
    int getID(){return id;}
    void print() const;
    ~trash();
};

    trash::trash() {
        id = 0;
        name = "";
        type = "";
        next = NULL;
    }

    trash::trash(int ID, string NAME, string TYPE) {
        id = ID;
        name = NAME;
        type = TYPE;
    }

    void trash::print() const {//const is to tell the compiler that the valuable cannot be change
            cout << endl << "ID: " << id << endl
                 << "Name: " << name << endl
                 << "Type: " << type << endl
                 << endl;
    }

    trash::~trash() 
    {}


#endif