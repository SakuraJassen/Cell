#include "Object.h"

namespace GameState
{
    extern unsigned int GrownThisCycle;
    extern unsigned int DiedThisCycle;
    extern unsigned int FireChance;
    extern unsigned int GrowChance;
	extern bool canGrow;
	extern bool canIgnite;
	extern bool pause;
    extern int maxY;
    extern int maxX;

    int getNeighbors(Object* field[][SIZE], int x, int y, std::string type);
    int getNeighborsDic(Object* field[][SIZE], int x, int y, std::string type);
    bool is(Object* field[][SIZE], int x, int y, int offX, int offY, std::string type);
}
