#include "Fire.h"
#include "Dirt.h"
#include "GameState.h"

Fire::Fire(int x, int y) : Object(x, y)
{
    //ctor
}

void Fire::update(Object* field[][SIZE])
{
	if(GameState::pause) return;
	int fireReach = 1;

	Object::update(field);
	for (int y = -fireReach; y <= fireReach; ++y)
	{
		for (int x = -fireReach; x <= fireReach; ++x)
		{
			ignite(field, x, y);
		}
	}
	/*ignite(field, 1, 0);
	ignite(field, -1, 0);
	ignite(field, 0, 1);
	ignite(field, 0, -1);*/

	if(m_LifeTime == 3)
		field[m_Pos.m_X][m_Pos.m_Y] = new Dirt(m_Pos.m_X,m_Pos.m_Y);
}

inline void Fire::ignite(Object* field[][SIZE], int x, int y)
{
	if((((m_Pos.m_Y+y) > 0) && ((m_Pos.m_Y+y) < GameState::maxY)) && (((m_Pos.m_X+x) > 0) && ((m_Pos.m_X+x) < GameState::maxX)))
	{
		if(field[m_Pos.m_X+x][m_Pos.m_Y+y]->getClass() == "tree")
		{
			field[m_Pos.m_X+x][m_Pos.m_Y+y] = new Fire(m_Pos.m_X+x, m_Pos.m_Y+y);
		}
	}
}

char Fire::getDisplay()
{
	return 'F';
}

Fire::~Fire()
{
    //dtor
}
