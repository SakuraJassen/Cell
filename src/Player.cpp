#include "Player.h"
#include "Tree.h"
#include "GameState.h"

Player::Player(int x, int y) : Object(x, y)
{
    m_WoodCounter = 0;
}

void Player::addWood(int amount)
{
	m_WoodCounter += amount;
}

int Player::getWood()
{
	return m_WoodCounter;
}


void Player::update(Object* field[][SIZE])
{
	return;
}


char Player::getDisplay()
{
	return ' ';
}

Player::~Player()
{
    //dtor
}
