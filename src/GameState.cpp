#include "GameState.h"
#include "Vector2D.h"

namespace GameState
{
	unsigned int GrownThisCycle = 0;
	unsigned int DiedThisCycle = 0;
	unsigned int FireChance = 10000;
	unsigned int GrowChance = 100;
	bool canGrow = true;
	bool canIgnite = true;
// OLD

	bool pause = true;
	bool won = false;
	int maxY = 0;
    int maxX = 0;
    int cycle = 1;
    int score = 0;
	int cellCount = 0;

	double leftChance = .25;
    double rightChance = .25;
    double upChance = .25;
    double downChance = .25;
	Vector2D furthest = Vector2D(-1000, -1000);
	Vector2D goal = Vector2D(0, 0);
	std::vector<States> stats{States()};

    int getNeighbors(Object* field[][SIZE], int x, int y, std::string type)
    {
        int cnt = 0;
        for (int tempY = -1; tempY <= 1; ++tempY)
		{
			for (int tempX = -1; tempX <= 1; ++tempX)
			{
				if((((tempY+y) > 0) && ((tempY+y) < GameState::maxY)) && (((tempX+x) > 0) && ((tempX+x) < GameState::maxX)))
				{
					if(field[tempX+x][tempY+y]->getClass() == type)
					{
						cnt++;
					}
				}
			}
		}
		return cnt;
    }

    int getNeighborsDic(Object* field[][SIZE], int x, int y, std::string type)
    {
        int cnt = 0;
        if(is(field, x, y, 1, 0, type))
            cnt++;
        if(is(field, x, y, -1, 0, type))
            cnt++;
        if(is(field, x, y, 0, 1, type))
            cnt++;
        if(is(field, x, y, 0, -1, type))
            cnt++;
		return cnt;
    }

    bool is(Object* field[][SIZE], int x, int y, int offX, int offY, std::string type)
    {
		if((((y+offY) > 0) && ((y+offY) < GameState::maxY)) && (((x+offX) > 0) && ((x+offX) < GameState::maxX)))
		{
			if(field[x+offX][y+offY]->getClass() == type)
			{
				return true;
			}
		}
		return false;
    }
}
