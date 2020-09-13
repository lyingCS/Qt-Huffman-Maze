#include "aco.h"

ACO::ACO(Maze& maze,int ants,int de,double al,int iter,double iP,double ap):antNum(ants),size(maze.height*maze.width),delta(de),alpha(al),iteration(iter),minP(iP),maxP(ap)
{
    srand(time(0));
    peromone.resize(size,minP);
    routes.resize(antNum);
    closed.resize(antNum);
}

double ACO::power(double x,int y)
{
    double ans = 1;
    while (y){
        if (y & 1) ans *= x;
        x *= x;
        y >>= 1;
    }
    return ans;
}

void ACO::tour(int n,Maze& maze)
{
    if(!survival.count(n))
        return;
    int next=choNext(n,maze);
    if(next==INT_MIN)
        return;
    closed[n].insert(next);
    if(n<antNum/2)
    {
        routes[n].push_back(next);
        if(posStart[next].second==-1||posStart[next].first>(int)routes[n].size())
        {
            posStart[next].first=routes[n].size();
            posStart[next].second=n;
        }
        if(posEnd[next].second!=-1)
        {
            if(posEnd[next].first-1+(int)routes[n].size()<bestInfo.steps)
            {
                bestInfo.steps=posEnd[next].first-1+routes[n].size();
                bestInfo.begin=n;
                bestInfo.mid=routes[n].back();
                bestInfo.end=posEnd[next].second;
            }
        }
    }
    else
    {
        routes[n].push_back(next);
        if(posEnd[next].second==-1||posEnd[next].first>(int)routes[n].size())
        {
            posEnd[next].first=routes[n].size();
            posEnd[next].second=n;
        }
        if(posStart[next].second!=-1)
        {
            if(posStart[next].first-1+(int)routes[n].size()<bestInfo.steps)
            {
                bestInfo.steps=posStart[next].first-1+(int)routes[n].size();
                bestInfo.begin=posStart[next].second;
                bestInfo.end=n;
                bestInfo.mid=routes[n].back();
            }
        }
    }
}

void ACO::init()
{
    for(int i=0;i<antNum;i++)
        survival.insert(i);
    for(int i=0;i<antNum/2;i++)
    {
        routes[i]={0};
        closed[i].insert(0);
    }
    for(int j=antNum/2;j<antNum;j++)
    {
        routes[j]={size-1};
        closed[j].insert(size-1);
    }
    posStart.resize(size,{-1,-1});
    posStart[0]={0,0};
    posEnd.resize(size,{-1,-1});
    posEnd[size-1]={0,antNum-1};
    bestInfo={0,0,0,INT_MAX};
}

void ACO::updateP()
{
    for(int i=0;i<size;i++)
    {
        if(bestPath.count(i))
            peromone[i]=(1-alpha)*peromone[i]+1/bestPath.size();
        else
            peromone[i]=(1-alpha)*peromone[i];
        peromone[i]=max(peromone[i],minP);
        peromone[i]=min(peromone[i],maxP);
    }
}

bool ACO::findPath(Maze& maze)
{
    for(int i=0;i<iteration;i++)
    {
        init();
        while((int)survival.size()!=0)
        {
            for(int j=0;j<antNum;j++)
            {
                if(survival.count(j))
                    tour(j,maze);
            }
        }
        if(bestInfo.steps<(int)bestPath.size()||(bestPath.size()==0&&bestInfo.steps!=INT_MAX))
        {
            bestPath.clear();
            for(int i=0;i<(int)routes[bestInfo.begin].size();i++)
            {
                if(routes[bestInfo.begin][i]==bestInfo.mid)
                    break;
                bestPath.insert(routes[bestInfo.begin][i]);
            }
            bestPath.insert(bestInfo.mid);
            for(int i=0;i<(int)routes[bestInfo.end].size();i++)
            {
                if(routes[bestInfo.end][i]==bestInfo.mid)
                    break;
                bestPath.insert(routes[bestInfo.end][i]);
            }
        }
        updateP();
    }
    if(bestPath.size()==0)
        return false;
    return true;
}

int ACO::choNext(int n,Maze& maze)
{
    double p=rand()%100/(double)101;
    vector<pair<int,double>> chols;
    int score=routes[n].back();
    int x=score/maze.width;
    int y=score%maze.width;
    double sumP=0;
    if(x>0&&maze.s.count({score,score-maze.width})&&!closed[n].count(score-maze.width))
    {
        chols.push_back({score-maze.width,power(peromone[score-maze.width],delta)});
    }
    if(x<maze.height-1&&maze.s.count({score,score+maze.width})&&!closed[n].count(score+maze.width))
    {
        chols.push_back({score+maze.width,power(peromone[score+maze.width],delta)});
    }
    if(y>0&&maze.s.count({score,score-1})&&!closed[n].count(score-1))
    {
        chols.push_back({score-1,power(peromone[score-1],delta)});
    }
    if(y<maze.width-1&&maze.s.count({score,score+1})&&!closed[n].count(score+1))
    {
        chols.push_back({score+1,power(peromone[score+1],delta)});
    }
    if(chols.size()==0){
        survival.erase(n);
        return INT_MIN;
    }
    int i=0;
    for(auto x:chols)
    {
        sumP+=x.second;
    }
    while(p>chols[i].second/sumP)
    {
        p-=chols[i].second/sumP;
        i++;
    }
    return chols[i].first;
}




































