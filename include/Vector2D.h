#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <string>
class Vector2D
{
    public:
        Vector2D(int x, int y);
        Vector2D();
        virtual ~Vector2D();
        void backInBounds(float x, float y, float x2, float y2);
        void setIfNull(int x, int y);

        Vector2D operator+(Vector2D& vec);
        Vector2D operator-(Vector2D& vec);
        Vector2D operator*(int i);
        std::string toString();
        int m_X;
        int m_Y;
    protected:
    private:
};

#endif // VECTOR2D_H
