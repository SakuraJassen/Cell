#include <string>
#include <iostream>
#include <bitset>
#include <iomanip>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <vector>

#include "conio.h"
#include <unistd.h>
#include <termios.h>
#include "Vector2D.h"
#include "Object.h"
#include "Tree.h"
#include "Dirt.h"
#include "Fire.h"
#include "Water.h"
#include "GameState.h"
#include "Player.h"
#include "Cell.h"

#define SIZE 250

using namespace std;

template <typename T>
inline void toggleBit(T* test, int n)
{
    *test ^= 1U << n;
}

template <typename T>
inline void setBit(T* test, int n, int x)
{
    *test ^= (-x ^ *test) & (1 << n);
}

template <typename T>
inline bool getBit(T const test, int n)
{
    return (test >> n) & 1;
}

template <typename T>
inline void copyArr(T arr1[][SIZE], T arr2[][SIZE])
{
    for (int y = 0; y < SIZE; ++y)
    {
        for (int x = 0; x < SIZE; ++x)
        {
           arr2[x][y] = arr1[x][y];
        }
    }
}

inline vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

inline void place(Object* field[][SIZE], string type, int x, int y)
{
    if(type == "cell") {
        field[x][y] = new Cell(x,y);
    } else if(type == "dirt"){
        field[x][y] = new Dirt(x,y);
    }
}

inline void runCmd(Object* field[][SIZE], string cmd)
{
    for(unsigned short loop=0;loop < cmd.size();loop++)
    {
        cmd[loop]=tolower(cmd[loop]);
    }
    std::vector<string> v = split(cmd, " ");
    if(v.at(0) == "set")
    {
        int x = stoi(v.at(2), nullptr, 10);
        int y = stoi(v.at(3), nullptr, 10);
        string type = v.at(1);
        place(field, type, x, y);
    } else if(v.at(0) == "rect") {
        int x1 = stoi(v.at(2), nullptr, 10);
        int y1 = stoi(v.at(3), nullptr, 10);
        int x2 = stoi(v.at(4), nullptr, 10);
        int y2 = stoi(v.at(5), nullptr, 10);
        string type = v.at(1);
        for (int y = y1; y <= y2; ++y)
        {
            for (int x = x1; x <= x2; ++x)
            {
                place(field, type, x, y);
            }
        }
    } else if(v.at(0) == "option") {
        int option = stoi(v.at(2), nullptr, 10);
        string type = v.at(1);
        if(type == "firechance") {
            GameState::FireChance = option;
        } else if(type == "growchance"){
            GameState::GrowChance = option;
        } else if(type == "cangrow"){
            GameState::canGrow = option;
        } else if(type == "canignite"){
            GameState::canIgnite = option;
        } else if(type == "pause"){
            GameState::pause = option;
        }
    }
}

void loadFile(Object* field[][SIZE], string fileName)
{
    std::string line;
    std::ifstream infile("/home/jcl/prog/code/ConsoleTest/"+fileName);
    for( std::string line; getline( infile, line ); )
    {
        if(line == "") // Ignore empty lines
            continue;
        runCmd(field, line);
    }
}

int main()
{
    int maxY,maxX;

    initscr();
    start_color();

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    getmaxyx(stdscr, maxY, maxX);

    Object* field[SIZE][SIZE];
    Object* bufffield[SIZE][SIZE];

    maxY -= 1;
    maxX -= 1;
    if(maxY > SIZE) maxY = SIZE;
    if(maxX > SIZE) maxX = SIZE;
    GameState::maxY = maxY;
    GameState::maxX = maxX;

    GameState::pause = true;
    for (int y = 0; y < maxY; ++y)
    {
        for (int x = 0; x < maxX; ++x)
        {
            field[x][y] = new Dirt(x, y);
        }
    }

    Player player(1,3);
    int frames = 0;

    char lastKey = 'q';
    bool exit = false;
    bool onlyOneFrame = false;
    bool faster = false;
    loadFile(field, "setup");
    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();
    while(!exit)
    {
        if (kbhit() != 0) { // When there is a key wating in the InputStream get it.
            Vector2D vec(0,0); //The direction Vector
            lastKey = getch();
            switch(lastKey) {
                case 'a' :
                    vec = Vector2D (-1,0);
                    break;
                case 'd' :
                    vec = Vector2D (1,0);
                    break;
                case 'w' :
                    vec = Vector2D (0,-1);
                    break;
                case 's' :
                    vec = Vector2D (0,1);
                    break;
                case 'p' :
                    GameState::pause = !GameState::pause;
                    break;
                case ' ':
                    {
                        int x = player.m_Pos.m_X;
                        int y = player.m_Pos.m_Y;
                        field[x][y] = new Cell(x,y);
                        break;
                    }
                case 'o':
                    loadFile(field, "thefile");
                    break;
                case 'q':
                    onlyOneFrame = true;
                    break;
                case 'n':
                    {
                        stringstream out;
                        out << "rect dirt 0 0 " << GameState::maxX << " " << GameState::maxY;
                        runCmd(field, out.str());
                        break;
                    }
                case 'l':
                    faster = !faster;
                    break;
                case 27: //<-- Escape Key
                    exit = true;
                    break;
            }

            player.m_Pos = player.m_Pos + vec;
            player.m_Pos.backInBounds(1,2,maxX-1,maxY-1);
            frames += 100; //Force an Update
        }
        //move(1,1);
        if(frames >= 40 || faster){
            t1 = std::chrono::high_resolution_clock::now();
            //Logic
            if (!GameState::pause || onlyOneFrame)
            {
                if(onlyOneFrame)
                    GameState::pause = false; //Temporary unpause the Game

                copyArr(field, bufffield);

                for (int y = 2; y < maxY; ++y)
                {
                    for (int x = 1; x < maxX; ++x)
                    {
                       field[x][y]->update(bufffield);
                    }
                }
                copyArr(bufffield, field);

                if(onlyOneFrame)
                {
                    GameState::pause = true;
                    onlyOneFrame = false;
                }
            }

            //Display
            for (int y = 1; y < maxY; ++y)
            {
                for (int x = 1; x < maxX; ++x)
                {
                    move(y,x);
                    attron(COLOR_PAIR(field[x][y]->getDisplayColor()));
                    addch(field[x][y]->getDisplay());
                }
                move(y,1);
            }
            //Debug Display
            attron(COLOR_PAIR(6));
            move(maxY+1, 0);
            printw("%s, P:%d, Tile:", player.m_Pos.toString().c_str(), GameState::pause);
            printw("\n %s", field[player.m_Pos.m_X][player.m_Pos.m_Y]->toString().c_str());

            stringstream out;
            t2 = std::chrono::high_resolution_clock::now();
            out << "Last Frame:" << std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count() << "µs   ";
            printw("\n %s", out.str().c_str());
            refresh();
            frames = 0;
        }
        move(player.m_Pos.m_Y-1, player.m_Pos.m_X);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        frames++;
    }
    endwin();
    return 0;
}
