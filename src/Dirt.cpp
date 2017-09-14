#include "Dirt.h"
#include "Tree.h"
#include "GameState.h"

Dirt::Dirt(int x, int y) : Object(x, y)
{
    //ctor
}

void Dirt::update(Object* field[][SIZE])
{
}

bool Dirt::isDirt(Object* field[][SIZE], int x, int y)
{
	if((((m_Pos.m_Y+y) > 0) && ((m_Pos.m_Y+y) < GameState::maxY)) && (((m_Pos.m_X+x) > 0) && ((m_Pos.m_X+x) < GameState::maxX)))
	{
		if(field[m_Pos.m_X+x][m_Pos.m_Y+y]->getClass() == "tree")
		{
			return false;
		}
	}

	return true;
}

char Dirt::getDisplay()
{
	return ' ';
}

Dirt::~Dirt()
{
    //dtor
}
