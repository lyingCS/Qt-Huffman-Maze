#ifndef ASTAR_H
#define ASTAR_H

#include<vector>
#include<queue>
#include<maze.h>
#include<unordered_set>

using namespace std;

class Astar
{
private:
    vector<pair<int,int>> father;       //record the father of each point
    pair<int,int> ts;
    pair<int,int> te;
    priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> que;   //priority_queue
    unordered_set<int> closed;          //judge if the point has been searched
    vector<vector<int>> vec;     //record the h,g,f value of each point
    vector<pair<int,int>> path;
    int height;
    int width;
    friend class PaintArea;
public:
    Astar(Maze& maze);
    int f(int,int);
    int h(int,int);
    int g(int,int);
    void findpath(Maze& maze);
    void search(int,Maze& maze);
};

#endif // ASTAR_H
