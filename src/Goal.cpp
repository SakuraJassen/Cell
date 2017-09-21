#include "Goal.h"

Goal::Goal(int x, int y) : Object(x, y)
{
    // ctor
}

void Goal::update(Object* field[][SIZE])
{
}

char Goal::getDisplay()
{
	return 'X';
}

Goal::~Goal()
{
    // dtor
}
