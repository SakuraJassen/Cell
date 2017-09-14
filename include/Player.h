#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
class Player : public Object
{
    public:
        Player(int x, int y);
        virtual ~Player();
        void addWood(int amount);
        int getWood();
        virtual std::string getClass() { return "player"; }
        virtual char getDisplay();
        virtual int getDisplayColor() { return 3; }
    protected:
        void update(Object* field[][SIZE]);
    private:
        int m_WoodCounter;
};

#endif // PLAYER_H
