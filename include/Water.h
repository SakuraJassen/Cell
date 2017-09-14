#ifndef WATER_H
#define WATER_H

#include "Object.h"
class Water : public Object
{
    public:
        Water(int x, int y);
        virtual ~Water();
        virtual std::string getClass() { return "water"; }
        virtual char getDisplay();
        virtual int getDisplayColor() { return 4; }
    protected:
        void update(Object* field[][SIZE]);
    private:
};

#endif // WATER_H
