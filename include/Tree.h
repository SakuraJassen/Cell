#ifndef TREE_H
#define TREE_H

#include "Object.h"
class Tree : public Object
{
    public:
        Tree(int x, int y);
        virtual ~Tree();
        virtual std::string getClass() { return "tree"; }
        virtual char getDisplay();
        virtual int getDisplayColor() { return 2; }
    protected:
        void update(Object* field[][SIZE]);
    private:
};

#endif // TREE_H
