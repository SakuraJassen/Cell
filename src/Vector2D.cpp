#include "Vector2D.h"
#include <sstream>

Vector2D::Vector2D(int x, int y)
{
    m_X = x;
    m_Y = y;
}

Vector2D::Vector2D()
{
    m_X = 0;
    m_Y = 0;
}

Vector2D::~Vector2D()
{
    //dtor
}

Vector2D Vector2D::operator+(Vector2D& vec)
{
	return Vector2D(this->m_X+vec.m_X, this->m_Y+vec.m_Y);
}

Vector2D Vector2D::operator-(Vector2D& vec)
{
	return Vector2D(this->m_X-vec.m_X, this->m_Y-vec.m_Y);
}

Vector2D Vector2D::operator*(int i)
{
    return Vector2D(this->m_X*i, this->m_Y*i);
}

void Vector2D::backInBounds(float x, float y, float x2, float y2)
{
    if(m_X < x)        m_X = x;
    else if(m_X > x2)  m_X = x2;

    if(m_Y < y)        m_Y = y;
    else if(m_Y > y2)  m_Y = y2;
}

void Vector2D::setIfNull(int x, int y)
{
    if(m_Y == 0 && m_X == 0)
    {
        m_X = x;
        m_Y = y;
    }
}

std::string Vector2D::toString()
{
    std::stringstream ss;
    ss << "X:"<< m_X << ", Y:" << m_Y;
    return ss.str();
}
