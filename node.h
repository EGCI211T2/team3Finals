#ifndef NODE_H
#define NODE_H

using namespace std;
class trash
{
private:
    int id;
    string name;
    string type;
    trash *next;

public:
    trash 
    (int = 0, string n = "Unknown", string t = "Unknown");
    void print();
    void set_next(trash*);
    trash* get_next();
    ~trash();
};

typedef trash *trashPtr;

trash *trash::get_next()
{
    return next;
}

void trash::set_next (trash *x) //add new node at the end
{
    next = x;
}

trash::trash(int x, string n, string t)
{
    id = x;
    name = n;
    type = t;
    next = NULL;
}

void trash::print()
{
    cout<< id << " " << name << " " << type << endl;
}

trash::~trash()
{
    cout << "Node deleted" << endl;
}

#endif