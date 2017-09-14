#include "Object.h"
#include "GameState.h"
#include "Vector2D.h"
#include <sstream>

Object::Object(int x, int y)
{
    m_Pos = Vector2D(x, y);
    m_LifeTime = 0;
}

Object::Object(int x, int y, int lifeTime)
{
    m_Pos = Vector2D(x, y);
    m_LifeTime = lifeTime;
}

void Object::update(Object* field[][SIZE])
{
	if(GameState::pause) return;
	m_LifeTime++;
}

std::string Object::toString()
{
    std::stringstream ss;
    ss << "Life:"<< m_LifeTime
        << " DispChar:" << this->getDisplay()
        << " DispInt: " << this->getDisplayColor()
        << " Class: " << this->getClass()
        << " Pos: " << this->m_Pos.toString();
    return ss.str();
}

Object::~Object()
{
    //dtor
}
