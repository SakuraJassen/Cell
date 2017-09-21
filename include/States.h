#ifndef STATES_H
#define STATES_H
#include <vector>

class States
{
    public:
        States(std::vector<int> v);
        States();
        virtual ~States();
        void addStat(std::vector<int> v);
        void addDir(int dir);
        std::string toString();
        std::vector<int> m_Dirs;
    protected:

    private:

};

#endif // STATES_H
