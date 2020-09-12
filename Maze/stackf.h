#ifndef STACKF_H
#define STACKF_H

#include<vector>
#include<maze.h>

using namespace std;

class StackF
{
private:
    vector<pair<int,int>> foot{{1,0},{0,1},{-1,0},{0,-1}};
    vector<pair<int,int>> path;
    vector<int> vec;
    friend class PaintArea;
    vector<int> closed;

public:
    StackF(Maze& maze);
    void search(pair<int,int> p,Maze& maze);
    void findPath(Maze& maze);

};

#endif // STACKF_H
