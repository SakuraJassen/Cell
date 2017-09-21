#include "Cell.h"
#include "Dirt.h"
#include "Vector2D.h"
#include "GameState.h"
#include <sstream>

States::States(std::vector<int> v)
{
	m_Dirs = v;
}

States::States()
{
 //ctor
}

States::~States()
{
 //dtor
}

void States::addStat(std::vector<int> v)
{
	m_Dirs.insert( m_Dirs.end(), v.begin(), v.end() );
}

void States::addDir(int dir)
{
	m_Dirs.push_back(dir);
}

std::string States::toString()
{
	return "";
}

