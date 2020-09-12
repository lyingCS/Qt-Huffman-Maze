#include "astar.h"
#include<QDebug>

Astar::Astar(Maze& maze):ts({0,0}),te({maze.height-1,maze.width-1}),height(maze.height),width(maze.width)
{
    vec.resize(height*width,vector<int>(3,-1));
    father.resize(height*width,{-1,-1});
    vec[0]={h(0,0),g(0,0),f(0,0)};
    que.push({f(0,0),{h(0,0),0}});
}

int Astar::g(int a,int b)
{
    return a+b;
}

int Astar::h(int a,int b)
{
    return abs(te.first-a)+abs(te.second-b);
}

int Astar::f(int a,int b)
{
    return h(a,b)+g(a,b);
}

void Astar::findpath(Maze& maze)
{
    int target=height*width-1;
    while(!closed.count(target))
    {
        auto k=que.top();
        que.pop();
        if(closed.count(k.second.second))
            continue;
        closed.insert(k.second.second);
        search(k.second.second,maze);
    }
    pair<int,int> p=te;
    while(p.first!=-1)
    {
        path.push_back(p);
        //qDebug()<<p.first<<p.second<<endl;
        p=father[p.first*width+p.second];
    }
}

void Astar::search(int score,Maze& maze)
{
    int x=score/width;
    int y=score%width;
    int _g=vec[score][1];
    if(y>0)
    {
        if(maze.s.count({score,score-1})&&!closed.count(score-1)&&((father[score-1].first==-1&&score!=1)||_g+1<vec[score-1][1]))
        {
            father[score-1]={x,y};
            vec[score-1][0]=h(x,y-1);
            vec[score-1][1]=1+_g;
            vec[score-1][2]=vec[score-1][0]+vec[score-1][1];
            que.push({vec[score-1][2],{vec[score-1][0],score-1}});
        }
    }
    if(y<width-1)
    {
        if(maze.s.count({score,score+1})&&!closed.count(score+1)&&(father[score+1].first==-1||_g+1<vec[score+1][1]))
        {
            father[score+1]={x,y};
            vec[score+1][0]=h(x,y+1);
            vec[score+1][1]=1+_g;
            vec[score+1][2]=vec[score+1][0]+vec[score+1][1];
            que.push({vec[score+1][2],{vec[score+1][0],score+1}});
        }
    }
    if(x>0)
    {
        if(maze.s.count({score,score-width})&&!closed.count(score-width)&&((father[score-width].first==-1&&score!=width)||_g+1<vec[score-width][1]))
        {
            father[score-width]={x,y};
            vec[score-width][0]=h(x-1,y);
            vec[score-width][1]=1+_g;
            vec[score-width][2]=vec[score-width][1]+vec[score-width][0];
            que.push({vec[score-width][2],{vec[score-width][0],score-width}});
        }
    }
    if(x<height-1)
    {
        if(maze.s.count({score,score+width})&&!closed.count(score+width)&&(father[score+width].first==-1||_g+1<vec[score+width][1]))
        {
            father[score+width]={x,y};
            vec[score+width][0]=h(x+1,y);
            vec[score+width][1]=_g+1;
            vec[score+width][2]=vec[score+width][0]+vec[score+width][1];
            que.push({vec[score+width][2],{vec[score+width][0],score+width}});
        }
    }
}
