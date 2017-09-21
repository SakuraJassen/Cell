#include "Object.h"
#include "Vector2D.h"
#include "States.h"
#include <ctime>
#include <random>

namespace GameState
{
    extern unsigned int GrownThisCycle;
    extern unsigned int DiedThisCycle;
    extern unsigned int FireChance;
    extern unsigned int GrowChance;
	extern bool canGrow;
	extern bool canIgnite;
    extern bool won;
	extern bool pause;
    extern int maxY;
    extern int maxX;
    extern int cycle;
    extern int score;
    extern int cellCount;
    extern Vector2D furthest;
    extern Vector2D goal;
    extern std::vector<States> stats;
    extern double leftChance;
    extern double rightChance;
    extern double upChance;
    extern double downChance;

    int getNeighbors(Object* field[][SIZE], int x, int y, std::string type);
    int getNeighborsDic(Object* field[][SIZE], int x, int y, std::string type);
    bool is(Object* field[][SIZE], int x, int y, int offX, int offY, std::string type);
}
