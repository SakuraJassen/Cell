#include "Cell.h"
#include "Dirt.h"
#include "Vector2D.h"
#include "GameState.h"
#include <sstream>
#include <vector>
#include <random>
#include <map>
#include <iterator>
#include <type_traits>
#include <ctime>

Cell::Cell(int x, int y) : Object(x, y)
{
    m_MatureTime = 5;
    m_hasSpread = false;
}

Cell::Cell(int x, int y, int lifeTime) : Object(x,y,lifeTime)
{
	m_MatureTime = 5;
	m_hasSpread = false;
}

void Cell::update(Object* field[][SIZE])
{
	if(GameState::pause) return;

	Object::update(field);

	int divisionTime = 2;
	if(m_LifeTime == m_MatureTime-divisionTime && !m_hasSpread)
	{
		std::map<double, int> cumulative;

		cumulative[(GameState::rightChance)] = 0;
		cumulative[(GameState::rightChance+GameState::leftChance)] = 1;
		cumulative[(GameState::downChance+GameState::rightChance+GameState::leftChance)] = 2;
		cumulative[(GameState::upChance+GameState::downChance+GameState::rightChance+GameState::leftChance)] = 3;

		double linear = rand()*1.0/RAND_MAX;
		int dir = cumulative.upper_bound(linear)->second;

		Vector2D pos;

		if(dir == 0) { //
			pos = Vector2D(1,0);
		} else if (dir == 1) { //
			pos = Vector2D(-1,0);
		} else if (dir == 2) { //
			pos = Vector2D(0,1);
		} else if (dir == 3) { //
			pos = Vector2D(0,-1);
		}
		unsigned int dirBit = 0;

		if(grow(field, pos.m_X, pos.m_Y, -divisionTime))
		{
			m_hasSpread = true;
			dirBit ^= (-1 ^ dirBit) & (1 << dir);
			GameState::stats[GameState::stats.size()-1].addDir(dirBit);
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
		// if(field[m_Pos.m_X+x][m_Pos.m_Y+y]->getClass() == "dirt" || field[m_Pos.m_X+x][m_Pos.m_Y+y]->getClass() == "goal")
		// {
			field[m_Pos.m_X+x][m_Pos.m_Y+y] = new Cell(m_Pos.m_X+x, m_Pos.m_Y+y);
		// }
	}
}

inline bool Cell::grow(Object* field[][SIZE], int x, int y, int lifeTime)
{
	if((((m_Pos.m_Y+y) > 1) && ((m_Pos.m_Y+y) < GameState::maxY)) && (((m_Pos.m_X+x) > 0) && ((m_Pos.m_X+x) < GameState::maxX)))
	{
		if(field[m_Pos.m_X+x][m_Pos.m_Y+y]->getClass() == "dirt" || field[m_Pos.m_X+x][m_Pos.m_Y+y]->getClass() == "goal")
		{
			if(field[m_Pos.m_X+x][m_Pos.m_Y+y]->getClass() == "goal")
				GameState::won = true;
			field[m_Pos.m_X+x][m_Pos.m_Y+y] = new Cell(m_Pos.m_X+x, m_Pos.m_Y+y, lifeTime);
			GameState::furthest = Vector2D(m_Pos.m_X+x,m_Pos.m_Y+y);
			GameState::cellCount++;
			return true;
		}
	}
	return false;
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
        << " m_MatureTime:" << this->m_hasSpread;
    return ss.str();
}

Cell::~Cell()
{
    //dtor
}
