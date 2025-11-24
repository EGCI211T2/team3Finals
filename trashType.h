#ifndef TRASHTYPE_H
#define TRASHTYPE_H

#include "node.h"
#include <string>
#include <iostream>

class TrashType { // stores one type of trash
private:
    std::string typeName;
    node* head;

public:
    TrashType(string name) : typeName(name), head(nullptr) {}

    void add(node* newTrash) {
        newTrash->set_next(head);
        head = newTrash;
    }

    void print() {
        std::cout << "=== " << typeName << " ===\n";
        node* cur = head;
        while (cur) {
            cur->print();
            cur = cur->get_next();
        }
        std::cout << std::endl;
    }
};

#endif
