#ifndef MAZE_H
#define MAZE_H

#include<vector>
#include<random>
#include<set>
#include"disjsets.h"

using namespace std;

class Maze{
private:
    vector<vector<int>> mp;
    DisjSets st;
    set<pair<int,int>> s;
    int height;
    int width;
    friend class Astar;
    friend class PaintArea;
    friend class StackF;
public:
    Maze();
    Maze(int m,int n);
    void find_path();
};

#endif // MAZE_H
