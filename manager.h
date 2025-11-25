#ifndef MANAGER_H
#define MANAGER_H

#include <unordered_map>
#include "trashType.h"

class Manager {
private:
    unordered_map<string, TrashType*> types;

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

    void printAll() {
        for (auto& t : types) {
            t.second->print();
        }
    }
};

#endif