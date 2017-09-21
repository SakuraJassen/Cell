#ifndef CELL_H
#define CELL_H

#include "Object.h"
class Cell : public Object
{
    public:
        Cell(int x, int y);
        Cell(int x, int y, int lifeTime);
        virtual ~Cell();
        virtual std::string getClass() { return "cell"; }
        virtual char getDisplay();
        virtual int getDisplayColor() {
            if(m_LifeTime < 0) return 5;
            return 2;
        }
        virtual std::string toString();
    protected:
        virtual void update(Object* field[][SIZE]);
        void grow(Object* field[][SIZE], int x, int y);
        bool grow(Object* field[][SIZE], int x, int y, int lifeTime);
        //bool move(Object* field[][SIZE], int x, int y, int matureTime);
    private:
        int m_MatureTime;
        bool m_hasSpread;
};

#endif // CELL_H
