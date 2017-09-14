#include "Cell.h"
#include "Dirt.h"
#include "Vector2D.h"
#include "GameState.h"
#include <sstream>


Cell::Cell(int x, int y) : Object(x, y)
{
    m_MatureTime = 10;
}

Cell::Cell(int x, int y, int lifeTime) : Object(x,y,lifeTime)
{
	m_MatureTime = 10;
}

void Cell::update(Object* field[][SIZE])
{
	if(GameState::pause) return;

	Object::update(field);
	if(m_LifeTime == m_MatureTime-3)
	{
		int dir = rand() % 4;
		bool split = (rand() % 10 == 0 || true);
		Vector2D pos;
		if(dir == 0) {
			pos = Vector2D(1,0);
		} else if (dir == 1) {
			pos = Vector2D(-1,0);
		} else if (dir == 2) {
			pos = Vector2D(0,1);
		} else if (dir == 3) {
			pos = Vector2D(0,-1);
		}

		/*if(move(field, pos.m_X, pos.m_Y, m_MatureTime) || m_LifeTime > m_MatureTime*50)
			field[m_Pos.m_X][m_Pos.m_Y] = new Dirt(m_Pos.m_X,m_Pos.m_Y);*/

		if(split)
		{
			Vector2D revpos = pos*-1;
			grow(field, revpos.m_X, revpos.m_Y, -3);
		}
	} else if(m_LifeTime >= m_MatureTime)
	{
		m_LifeTime = 0;
	}
}

inline void Cell::grow(Object* field[][SIZE], int x, int y)
{
	if((((m_Pos.m_Y+y) > 1) && ((m_Pos.m_Y+y) < GameState::maxY)) && (((m_Pos.m_X+x) > 0) && ((m_Pos.m_X+x) < GameState::maxX)))
	{
		if(field[m_Pos.m_X+x][m_Pos.m_Y+y]->getClass() == "dirt")
		{
			field[m_Pos.m_X+x][m_Pos.m_Y+y] = new Cell(m_Pos.m_X+x, m_Pos.m_Y+y);
		}
	}
}

inline void Cell::grow(Object* field[][SIZE], int x, int y, int lifeTime)
{
	if((((m_Pos.m_Y+y) > 1) && ((m_Pos.m_Y+y) < GameState::maxY)) && (((m_Pos.m_X+x) > 0) && ((m_Pos.m_X+x) < GameState::maxX)))
	{
		if(field[m_Pos.m_X+x][m_Pos.m_Y+y]->getClass() == "dirt")
		{
			field[m_Pos.m_X+x][m_Pos.m_Y+y] = new Cell(m_Pos.m_X+x, m_Pos.m_Y+y, lifeTime);
		}
	}
}

//inline bool Cell::move(Object* field[][SIZE], int x, int y, int matureTime)
//{
//	if((((m_Pos.m_Y+y) > 1) && ((m_Pos.m_Y+y) < GameState::maxY)) && (((m_Pos.m_X+x) > 0) && ((m_Pos.m_X+x) < GameState::maxX)))
//	{
//		if(field[m_Pos.m_X+x][m_Pos.m_Y+y]->getClass() == "dirt")
//		{
//			field[m_Pos.m_X+x][m_Pos.m_Y+y] = new Cell(m_Pos.m_X+x, m_Pos.m_Y+y, matureTime);
//			return true;
//		}
//	}
//	return false;
//}

char Cell::getDisplay()
{
	return 'o';
}

std::string Cell::toString()
{
    std::stringstream ss;
    ss << Object::toString()
        << " m_MatureTime:" << this->m_MatureTime;
    return ss.str();
}

Cell::~Cell()
{
    //dtor
}
