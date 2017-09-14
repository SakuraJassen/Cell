#ifndef DIRT_H
#define DIRT_H

#include "Object.h"
class Dirt : public Object
{
    public:
        Dirt(int x, int y);
        virtual ~Dirt();
        bool isDirt(Object* field[][SIZE], int x, int y);
        virtual std::string getClass() { return "dirt"; }
        virtual char getDisplay();
        virtual int getDisplayColor() { return 3; }
    protected:
        void update(Object* field[][SIZE]);
    private:
};

#endif // DIRT_H
