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
    //node (int = 0, string n = "Unknown", string t = "Unknown");
    void print();
    void set_next(node*);
    node* get_next();
    ~node();
};

typedef node *trashPtr;

node* node::get_next()
{
    return next;
}

void node::set_next (node *x) //add new node at the end
{
    next = x;
}

/*
node::node(int x, string n, string t)
{
    id = x;
    name = n;
    type = t;
    next = NULL;
}
*/

void node::print()
{
    cout<< id << " " << name << " " << type << endl;
}

node::~node()
{
    cout << "Node deleted" << endl;
}

#endif