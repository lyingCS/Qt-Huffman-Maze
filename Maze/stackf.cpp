#include "stackf.h"
#include<QtDebug>

StackF::StackF(Maze& maze)
{
    vec.resize(maze.height*maze.width);
    path.push_back({0,0});
    closed.resize(vec.size());
    closed[0]=1;
}

void StackF::findPath(Maze& maze)
{
    while(path.back().first!=maze.height-1||path.back().second!=maze.width-1)
    {
        search(path.back(),maze);
    }
}

void StackF::search(pair<int, int> p, Maze &maze)
{
    int x=p.first;
    int y=p.second;
    int score=x*maze.width+y;
    if(vec[score]==0)
    {
        if(x==maze.height-1||!maze.s.count({score,score+maze.width})||closed[score+maze.width]==1)
            vec[score]++;
        else
        {
            path.push_back({x+1,y});
            vec[score]++;
            closed[score+maze.width]=1;
        }
    }
    else if(vec[score]==1)
    {
        if(y==maze.width-1||!maze.s.count({score,score+1})||closed[score+1]==1)
            vec[score]++;
        else
        {
            path.push_back({x,y+1});
            vec[score]++;
            closed[score+1]=1;
        }
    }
    else if(vec[score]==2)
    {
        if(x==0||!maze.s.count({score,score-maze.width})||closed[score-maze.width]==1)
            vec[score]++;
        else
        {
            path.push_back({x-1,y});
            vec[score]++;
            closed[score-maze.width]=1;
        }
    }
    else if(vec[score]==3)
    {
        if(y==0||!maze.s.count({score,score-1})||closed[score-1]==1)
            vec[score]++;
        else
        {
            path.push_back({x,y-1});
            vec[score]++;
            closed[score-1]=1;
        }
    }
    else
    {
        path.pop_back();
    }
}
