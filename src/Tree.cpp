#include "Tree.h"
#include "Dirt.h"
#include "Fire.h"
#include "GameState.h"

Tree::Tree(int x, int y) : Object(x, y)
{
    //ctor
}

void Tree::update(Object* field[][SIZE])
{
	if(GameState::pause) return;
	Object::update(field);
	if(GameState::canIgnite && rand() % GameState::FireChance == 0 && !GameState::pause)
	{
		field[m_Pos.m_X][m_Pos.m_Y] = new Fire(m_Pos.m_X,m_Pos.m_Y);
	}
}

char Tree::getDisplay()
{
	if(m_LifeTime < 50)
	{
		return 't';
	}
	else if(m_LifeTime >= 50 && m_LifeTime < 100)
	{
		return '|';
	}
    return 'T';

}

Tree::~Tree()
{
    //dtor
}
