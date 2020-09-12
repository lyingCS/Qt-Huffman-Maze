#ifndef GA_H
#define GA_H

#include<maze.h>
#include<vector>
#include<algorithm>

class Player{
private:
    vector<int> genes;
    int adapt;
    friend class GA;
    friend class PaintArea;
public:
    Player(int n=0);
};

class GA
{
private:
    int playerNum;
    int geneLength;
    int fatherNum;
    int evolutionTimes;
    int variation;
    pair<int,int> te;
    vector<Player> parents;
    vector<Player> sons;
    bool isFound;
    int murate;
    int surate;
    struct
    {
        int num;
        int adapt;
    }king;
    friend class PaintArea;

public:
    GA(Maze& maze,int times,int nums,int rate,int rate_2);
    void calAdapt(Maze& maze);
    void evolution();
    bool findPath(Maze& maze);
    static bool cmp(Player a,Player b);
};

#endif // GA_H
