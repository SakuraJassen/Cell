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
#include <bitset>
#include <limits>

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
#include "States.h"
#include "Goal.h"

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

inline void place(Object* field[][SIZE], string type, string xStr, string yStr)
{
    int x = 0;
    int y = 0;
    if(xStr != "maxx")
    {
        x = stoi(xStr, nullptr, 10);
    } else
    {
        x = GameState::maxX-2;
    }
    if(yStr != "maxy")
    {
        y = stoi(yStr, nullptr, 10);
    } else
    {
        y = GameState::maxY-1;
    }
    if(type == "cell") {
        field[x][y] = new Cell(x,y);
    } else if(type == "dirt"){
        field[x][y] = new Dirt(x,y);
    } else if(type == "goal"){
        field[x][y] = new Goal(x,y);
        GameState::goal = {x,y};
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

        string type = v.at(1);
        place(field, type, v.at(2), v.at(3));
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
                place(field, type, std::to_string(x), std::to_string(y));
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
    std::ifstream infile("/home/jcl/prog/code/aitest/"+fileName);
    for( std::string line; getline( infile, line ); )
    {
        if(line == "") // Ignore empty lines
            continue;
        runCmd(field, line);
    }
}

void clearField(Object* field[][SIZE])
{
    stringstream out;
    out << "rect dirt 0 0 " << GameState::maxX << " " << GameState::maxY;
    runCmd(field, out.str());
}

double getScore(int timePenalty)
{
    double wonBonus = 0;
    if(GameState::won)
        wonBonus = -100;
    return std::hypot(GameState::goal.m_X-GameState::furthest.m_X, GameState::goal.m_Y-GameState::furthest.m_Y)+(GameState::cycle/30)+wonBonus;
}

int main()
{
    int maxY,maxX;

    initscr();
    start_color();
    srand (time(NULL));
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    curs_set(0);
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

    vector<double> score;
    vector<Vector2D> scoreVec;
    int frames = 0;
    char lastKey = 'q';
    bool exit = false;
    bool onlyOneFrame = false;
    bool faster = true;
    int sameCellCount = 0;
    int oldCellCount = 0;
    int gen = 1;
    int tries = 0;
    double smallest = std::numeric_limits<double>::infinity();
    int index = 0;
    int timePenalty = 20;
    double dirsStat [] = {0,0,0,0,0};
    loadFile(field, "setup");
    field[GameState::goal.m_X][GameState::goal.m_Y] = new Goal(GameState::goal.m_X, GameState::goal.m_Y);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();
    while(!exit)
    {
        if(oldCellCount == GameState::cellCount && !GameState::pause)
        {
          sameCellCount++;
          if(sameCellCount >= 20*80 || GameState::won)
          {
            score.push_back(getScore(timePenalty));
            scoreVec.push_back(GameState::furthest);
            GameState::stats.push_back(States());
            loadFile(field, "setup");
            field[GameState::goal.m_X][GameState::goal.m_Y] = new Goal(GameState::goal.m_X, GameState::goal.m_Y);
            sameCellCount = 0;
            oldCellCount = 0;
            GameState::cycle = 1;
            GameState::score = 0;
            GameState::cellCount = 0;
            GameState::furthest = Vector2D(-1000, -1000);
            tries++;
            GameState::won = false;

            if(tries >= 10)
            {
                bool foundBetter = false;
                for(std::vector<double>::size_type i = 0; i != score.size(); i++)
                {
                    if(score[i] <= smallest)
                    {
                        smallest = score[i];
                        index = i;
                        foundBetter = true;
                    }
                }
                for (int i = 0; i < sizeof dirsStat / sizeof dirsStat[0]; ++i)
                {
                    dirsStat[i] = 0;
                }

                if(foundBetter)
                {
                    for (auto& dirs : GameState::stats[index].m_Dirs )
                    {
                        if(getBit(dirs, 0))
                        {
                            dirsStat[0]+=1; // >
                        } else if(getBit(dirs, 1))
                        {
                            dirsStat[1]+=1; // <
                        } else if(getBit(dirs, 2))
                        {
                            dirsStat[2]+=1; // V
                        } else if(getBit(dirs, 3))
                        {
                            dirsStat[3]+=1; // ^
                        }
                        dirsStat[4]+=1;
                    }
                    GameState::rightChance = (dirsStat[0]/dirsStat[4])+0.000001;
                    GameState::leftChance = (dirsStat[1]/dirsStat[4])+0.000001;
                    GameState::downChance =(dirsStat[2]/dirsStat[4])+0.000001;
                    GameState::upChance = (dirsStat[3]/dirsStat[4])+0.000001;
                }
                score.clear();
                GameState::stats = {States()};
                gen++;
                tries = 0;
            }
          }
        }
        else
        {
            sameCellCount = 0;
        }
        oldCellCount = GameState::cellCount;
        if (kbhit() != 0) { // When there is a key waiting in the InputStream get it.
            Vector2D vec(0,0); // The direction Vector
            lastKey = getch();
            switch(lastKey) {
                case 'a' :
                    vec = Vector2D (-1,0);
                    break;
                case 'd' :
                    vec = Vector2D (1,0);
                    break;
                case 'w' :
                    timePenalty++;
                    break;
                case 's' :
                    timePenalty--;
                    break;
                case 'p' :
                    GameState::pause = !GameState::pause;
                    break;
                case 'o':
                    loadFile(field, "thefile");
                    break;
                case 'q':
                    onlyOneFrame = true;
                    break;
                case 'l':
                    faster = !faster;
                    break;
                case 27: //<-- Escape Key
                    exit = true;
                    break;
            }

            frames += 100; // Force an Update
        }
        // move(1,1);
        if(frames >= 40){
            t1 = std::chrono::high_resolution_clock::now();
            // Logic
            if (!GameState::pause || onlyOneFrame)
            {
                GameState::cycle++;
                if(onlyOneFrame)
                    GameState::pause = false; // Temporary unpause the Game

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

            // Display
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

            // Debug Display
            attron(COLOR_PAIR(6));
            move(maxY, 0);
            printw("gen:%d, tries:%02d, score: %f, %s", gen, tries+1, getScore(timePenalty), GameState::furthest.toString().c_str());
            if(faster)
            {
                printw("\t>%f <%f V%f ^%f\t\t\t\t", GameState::rightChance, GameState::leftChance, GameState::downChance, GameState::upChance);
            } else
            {
                printw("\t\t\t\t\t\t\t");
            }

            /*stringstream out;
            t2 = std::chrono::high_resolution_clock::now();
            out << "Last Frame:" << std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count() << "µs   ";
            printw("\n %s", out.str().c_str());*/
            refresh();
            frames = 0;
        }
        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
        frames++;
        // if(GameState::won)
            // exit = true;
    }
    endwin();
    /*for (const auto& scoreTuple : score)
    {
        cout << setfill('0') << setw(10) << scoreTuple << "  ";
    }
    cout << "big:" << smallest << " " << index;
    cout << endl;

    for (auto& dirs : GameState::stats[index].m_Dirs )
    {
        std::string binary = std::bitset<4>(dirs).to_string();
        cout << binary << " ";
        if(getBit(dirs, 0))
        {
            cout << "0, >";
        } else if(getBit(dirs, 1))
        {
            cout << "1, <";
        } else if(getBit(dirs, 2))
        {
            cout << "2, V";
        } else if(getBit(dirs, 3))
        {
            cout << "3, ^";
        }
        cout << endl;
    }
    for (int i = 0; i < sizeof dirsStat / sizeof dirsStat[0]; ++i)
    {
        cout << i << ": " << dirsStat[i]<<endl;
    }*/
    if(GameState::won)
        cout << "It took " << gen << " generations" << endl;

    cout << endl;
    return 0;
}
