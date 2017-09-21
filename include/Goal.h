#ifndef GOAL_H
#define GOAL_H

#include "Object.h"
class Goal : public Object
{
    public:
        Goal(int x, int y);
        virtual ~Goal();
        virtual std::string getClass() { return "goal"; }
        virtual char getDisplay();
        virtual int getDisplayColor() { return 5; }
    protected:
        void update(Object* field[][SIZE]);
    private:
};

#endif // GOAL_H
