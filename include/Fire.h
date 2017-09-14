#ifndef FIRE_H
#define FIRE_H

#include "Object.h"
class Fire : public Object
{
    public:
        Fire(int x, int y);
        virtual ~Fire();
        virtual std::string getClass() { return "fire"; }
        virtual char getDisplay();
        virtual int getDisplayColor() {
            if(m_LifeTime == 0)
                return 5;
            return 1;
        }
    protected:
        void update(Object* field[][SIZE]);
        void ignite(Object* field[][SIZE], int x, int y);
    private:
};

#endif // FIRE_H
