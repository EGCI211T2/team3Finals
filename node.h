#ifndef NODE_H
#define NODE_H

class node {
private:
    int id;
    string name;
    string type;
    node *next;
    node *before;

public:
    node (int idParam = 0, string n = "Unknown", string t = "Unknown", node *n2 = nullptr, node *b = nullptr) //default values
        : id(idParam), name(n), type(t), next(n2), before(b) {} //constructor
    void print();
    void set_next(node* x) {next = x;}
    void set_before(node* x) {before = x;}
    node* get_next() {return next;} 
    node* get_before() {return before;}
    int get_id() {return id;}
    ~node();
};

void node::print() {
    cout<< id << ", " << name << ", " << type << endl;
}

node::~node() {
    cout << "Node deleted" << endl;
}

#endif