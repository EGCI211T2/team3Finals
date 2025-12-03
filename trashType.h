#ifndef TRASHTYPE_H
#define TRASHTYPE_H

#include "node.h"
#include <string>
#include <iostream>

class TrashType { // stores one type of trash
private:
    std::string typeName;
    node* head; // first node

public:
    TrashType(string name) : typeName(name), head(nullptr) {}

    void add(node* newTrash) {
        
        if (head == nullptr) { // if there are no nodes in the linked list
            head = newTrash;
            return;
        }

        node* curr = head;
        while (curr->get_next() != nullptr && newTrash->get_id() > curr->get_next()->get_id()) { // traversal
            curr = curr->get_next();
        }

        if (newTrash->get_id() < head->get_id()) { // if head is smaller than newTrash
            curr->set_before(newTrash);
            newTrash->set_next(curr);
            head = newTrash;
            return;
        }

        if (curr->get_next() == nullptr) { // if id is larger than all the nodes in the linked list
            newTrash->set_before(curr);
            curr->set_next(newTrash);
        } else { // insert in middle
            node* temp = curr->get_before();
            curr->set_before(newTrash);
            temp->set_next(newTrash);

            newTrash->set_before(temp);
            newTrash->set_next(curr);
        }
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
