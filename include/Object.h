#ifndef OBJECT_H
#define OBJECT_H
#define SIZE 250
#include <string>
#include "Vector2D.h"

class Object
{
    public:
        Object(int x, int y);
        Object(int x, int y, int lifeTime);
        virtual ~Object();
        virtual void update(Object* field[][SIZE]);
        int GetLifeTime() { return m_LifeTime; }
        void SetLifeTime(int val) { m_LifeTime = val; }
        virtual std::string getClass() { return "object"; }
        virtual char getDisplay() { return ' '; }
        virtual int getDisplayColor() { return 1; }

        virtual std::string toString();
        Vector2D m_Pos;
    protected:
        int m_LifeTime;
    private:

};

#endif // OBJECT_H
