#include "Water.h"
#include "Dirt.h"
#include "Fire.h"
#include "GameState.h"

Water::Water(int x, int y) : Object(x, y)
{
    //ctor
}

void Water::update(Object* field[][SIZE])
{

}

char Water::getDisplay()
{
	return ' ';
}

Water::~Water()
{
    //dtor
}
