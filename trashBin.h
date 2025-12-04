#ifndef TRASHBIN_H
#define TRASHBIN_H

#include <cstring>
#include <iostream> 
#include <cmath>


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

    //fancy ass constructor
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
                
    // git gud
    double getX() {return x;}
    double getY() {return y;}
    int getID() {return id;}
    int* getCat() {return catagory;}
    string getName() {return name;}
    void print() const;

    // LL stuff
    void set_next(trashBin* x) {next = x;}
    trashBin* get_next() {return next;} 

    // router stuff
    double distanceTo(double px, double py);
    ~trashBin();
};

    void trashBin::print() const { // const is to tell the compiler that the valuable cannot be change
            cout << endl << "ID: " << id << endl
                 << "Name: " << name << endl
                 << "Coords: " << x << ", " << y << endl;
            for(int cat : catagory){
                cout << cat << endl;
            }
            cout << endl;

    }

    double trashBin::distanceTo(double px, double py) { // returns the distance between inputted cords and site cords
        double dx = x - px;
        double dy = y - py;
        return sqrt(dx*dx + dy*dy);
    }

    trashBin::~trashBin() { // deezconstructor
        #if 0
        cout << "trashBin deleted" << endl;
        #endif
    }


#endif