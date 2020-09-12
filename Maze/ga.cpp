#include "ga.h"
#include<time.h>
#include<QDebug>

Player::Player(int n)
{
    genes.resize(n);
    for(int i=0;i<n;i++)
    {
        genes[i]=rand()%4;
    }
}

GA::GA(Maze& maze,int times):playerNum(1000),fatherNum(50),te({maze.height-1,maze.width-1}),evolutionTimes(times),isFound(false)
{
    int size=maze.height*maze.width;
    sons.resize(playerNum);
    geneLength=3*(maze.height+maze.width);
    variation=geneLength/10;
    for(int i=0;i<playerNum;i++)
    {
        parents.push_back(Player(3*size));
    }
    calAdapt(maze);
}

void GA::evolution()
{
    srand((unsigned)time(NULL));
    int i=0;
    for(i=0;i<fatherNum&&parents[i].adapt>0;i++)
        sons[i]=parents[i];
    for(;i<playerNum;i++)
    {
        int dad,mom;
        do{dad=rand()%fatherNum,mom=rand()%fatherNum;} while(dad==mom);
        int pos=rand()%geneLength;
        for(int j=0;j<pos;j++)
        {
            sons[i].genes.resize(geneLength);
            sons[i].genes[j]=parents[dad].genes[j];
        }
        for(int j=pos;j<geneLength;j++)
        {
            sons[i].genes.resize(geneLength);
            sons[i].genes[j]=parents[mom].genes[j];
        }
    }
    for(i=0;i<playerNum;i++)
    {
        parents[i]=sons[i];
        if(i<3)
            continue;
        for(int j=0;j<variation;j++)
        {
            parents[i].genes[rand()%geneLength]=rand()%4;
        }
    }
}

bool GA::findPath(Maze& maze)
{
    isFound=false;
    for(int i=0;i<evolutionTimes;i++)
    {
        evolution();
        calAdapt(maze);
    }
    return isFound;
}

void GA::calAdapt(Maze& maze)
{
    king.adapt=-100000;
    for(int i=0;i<playerNum;i++)
    {
        int x=0;
        int y=0;
        int adapt=0;
        vector<vector<bool>> isReached(maze.height,vector<bool>(maze.width,0));
        int j;
        for(j=0;j<geneLength;j++)
        {
            isReached[x][y]=true;
            int score=x*maze.width+y;
            if(parents[i].genes[j]==0)
            {
                if(0==x||!maze.s.count({score,score-maze.width}))
                    continue;
                if(isReached[--x][y])
                    adapt-=20;
            }
            else if(parents[i].genes[j]==1)
            {
                if(maze.height-1==x||!maze.s.count({score,score+maze.width}))
                    continue;
                if(isReached[++x][y])
                    adapt-=20;
            }
            else if(parents[i].genes[j]==2)
            {
                if(0==y||!maze.s.count({score,score-1}))
                    continue;
                if(isReached[x][--y])
                    adapt-=20;
            }
            else
            {
                if(maze.width==y||!maze.s.count({score,score+1}))
                    continue;
                if(isReached[x][++y])
                    adapt-=20;
            }
            if(maze.height-1==x&&maze.width-1==y)
            {
                adapt+=100000;
                isFound=true;
                break;
            }
        }
        adapt-=j;
        adapt-=(maze.height-1-x)*(maze.height-1-x)+(maze.width-1-y)*(maze.width-1-y);
        parents[i].adapt=adapt;
        if(adapt>king.adapt)
        {
            king.adapt=adapt;
            king.num=i;
        }
    }
    sort(parents.begin(),parents.end(),this->cmp);
}

bool GA::cmp(Player a,Player b)
{
    return a.adapt>b.adapt;
}
























