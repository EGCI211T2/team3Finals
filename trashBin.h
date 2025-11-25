#ifndef TRASHBIN_H
#define TRASHBIN_H

#include <cstring>
#include <iostream> 

using namespace std;

class trashBin {
    
private:
    int id;
    string name;
    double x;
    double y;
    int catagory[8]; 
    /*shows which type of trash can be disposed(0 for no, 1 for yes), order is as follow:
    Compost, Plastic Bottle, Recycle, Landfill, Paper/Box, E-waste, Infectious, Hazardous*/
    trashBin* next;

public:
    trashBin();
    trashBin(int idParam = 0, 
            string n = "", 
            double xa = 0, 
            double ya = 0, 
            const int cat[8] = nullptr, 
            trashBin* next = nullptr) // default value
                : id(idParam), name(n), x(xa), y(ya) { // init with values
                    for(int i = 0; i < 8; i++){ // constructor for the string array
                        catagory[i] = cat[i];
                    }
                }
    
    double getX() {return x;}
    double getY() {return y;}
    int getID() {return id;}
    int* getCat() {return catagory;}
    string getName() {return name;}
    void set_next(trashBin* x) {next = x;}
    trashBin* get_next() {return next;} 
    void print() const;
    ~trashBin();
};

    void trashBin::print() const {//const is to tell the compiler that the valuable cannot be change
            cout << endl << "ID: " << id << endl
                 << "Name: " << name << endl
                 << "Coords: " << x << ", " << y << endl;
            for(int cat : catagory){
                cout << cat << endl;
            }
            cout << endl;

    }

    trashBin::~trashBin() {
        #if 0
        cout << "trashBin deleted" << endl;
        #endif
    }


#endif