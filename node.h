#ifndef NODE_H
#define NODE_H

using namespace std;
class node
{
private:
    int id;
    string name;
    string type;
    node *next;

public:
    node (int = 0, string n = "Unknown", string t = "Unknown", node *next = nullptr) //default values
        : id(id), name(n), type(t), next(next) {} //constructor
    void print();
    void set_next(node* x) {next = x;}
    node* get_next() {return next;} 
    ~node();
};

void node::print()
{
    cout<< id << ", " << name << ", " << type << endl;
}

node::~node()
{
    cout << "Node deleted" << endl;
}

#endif