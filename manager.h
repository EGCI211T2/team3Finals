/*0 Compost, 1 Plastic Bottle, 2 Recycle, 3 Landfill, 4 Paper/Box, 5 E-waste, 6 Infectious, 7 Hazardous*/

// make the linked lists for each type of trash, handles the allocation of trash to specific type list, and handles route stuff

#ifndef MANAGER_H
#define MANAGER_H

#include <unordered_map>
#include "trashType.h"

// ANSI escape codes for colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"

class Manager {
private:
    unordered_map<string, TrashType*> types;
    string keyCat[8] = {
        "Compost", "Plastic Bottle", "Recycle", 
        "Landfill", "Paper/Box", "E-waste", 
        "Infectious", "Hazardous"
    };

public:
    Manager() {}

    void addTrash(int id, string name, string type) {
        node* newNode = new node(id, name, type);

        // create new list if it doesn't exist
        if (types.find(type) == types.end()) {
            types[type] = new TrashType(type);
        }

        // add to correct linked list
        types[type]->add(newNode);
    }

    std::pair<std::vector<trashBin>, std::vector<std::vector<int>>> computeRoute(vector<trashBin>& bins, double userX, double userY) {
        std::vector<trashBin> route;
        std::vector<std::vector<int>> categoriesPerBin; // vector in a vector... 

        // determining what catagories are needed
        vector<int> needed(8,0);

        vector<int> neededCatLog; // keeps track of what catagory for which bin

        for(auto t : types) {
            string inputCat = t.first;

            for(int i = 0; i < 8; i++) { // find index that matches user input catagory
                if(inputCat == keyCat[i]) {
                    needed[i] = 1; // marks catagory as needed
                    break;
                }
            }
        }

        while (true) {
            // check if all needs satisfied
            bool done = true;
            for (int v : needed) {
                if (v == 1) { done = false; break; }
            }
            if (done) break;

            trashBin* bestBin = nullptr;
            double bestDist = 1e9; // 1*10^9

            // find nearest bin that helps with ANY needed type
            for (auto& b : bins) {

                bool helpful = false;
                for (int i = 0; i < 8; i++) {
                    if (needed[i] == 1 && b.getCat()[i] == 1) {
                        helpful = true;
                        break;
                    }
                }

                if (!helpful) continue; // No bins can satisfy a catagory

                double d = b.distanceTo(userX, userY);
                if (d < bestDist) {
                    bestDist = d;
                    bestBin = &b;
                }
            }

            if (!bestBin) {
                cout << "ERROR: No bin can satisfy all categories!" << endl;
                break;
            }

            // add chosen bin to route
            route.push_back(*bestBin);

            std::vector<int> binCats;

            // update needed categories (remove those satisfied) and record categories satisfied by this bin
            for (int i = 0; i < 8; i++) {
                if (bestBin->getCat()[i] == 1 && needed[i] == 1) {
                    needed[i] = 0;
                    binCats.push_back(i);
                }
            }

            categoriesPerBin.push_back(binCats);

            // move starting point to this bin
            userX = bestBin->getX();
            userY = bestBin->getY();
        }

        return {route, categoriesPerBin};
    }

    void printBinWithTrash(const std::pair<std::vector<trashBin>, std::vector<std::vector<int>>>& result) {
        std::vector<trashBin> route = result.first;
        const auto& categoriesPerBin = result.second;

        for (size_t i = 0; i < route.size(); ++i) {
            cout << GREEN << "Bin " << route[i].getName()
                 << " at (" << route[i].getX() << ", " << route[i].getY() << ")\n" << RESET;

            cout << "Dispose: " << endl;

            for (int catIndex : categoriesPerBin[i]) { // prevent crashing, Im out of my wits to fix this one
                const string& catName = keyCat[catIndex];
                auto it = types.find(catName);
                if (it != types.end() && it->second != nullptr) {
                    it->second->print();
               } else {
                    // cout << "  (No TrashType for " << catName << ")\n";
                }
            }

            cout << endl;
        }
    }

    void printAll() {
        for (auto& t : types) {
            t.second->print();
        }
    }

        ~Manager() {
        for (auto &entry : types) {
            delete entry.second;   // free each TrashType*
        }
    }

};

#endif