#ifndef ACO_H
#define ACO_H

#include<vector>
#include<time.h>
#include<queue>
#include<maze.h>
#include<unordered_set>
#include<map>
#include<maze.h>

using namespace std;

class ACO
{
private:
    vector<double> peromone;   //信息素
    vector<vector<int>> routes;             //每只蚂蚁走过的路径
    unordered_set<int> bestPath;
    struct
    {
        int begin;
        int end;
        int mid;
        int steps;
    }bestInfo;                               //每一轮迭代得到的最佳路径信息
    int antNum;
    int size;                               //maze的size
    int delta;
    double alpha;
    int iteration;                              //迭代次数
    vector<unordered_set<int>> closed;          //每只蚂蚁走过的位置
    vector<pair<int,int>> posStart;                 //记录从起点出发的蚂蚁走过的最短位置和相应的蚂蚁序号
    vector<pair<int,int>> posEnd;               //记录从终点出发的蚂蚁走过的最短位置和相应的蚂蚁序号
    double minP;                                //信息素的最小值
    double maxP;
    unordered_set<int> survival;               //记录存活的蚂蚁序号
    friend class PaintArea;

public:
    ACO(Maze& maze,int,int,double,int,double,double);
    double power(double a,int b);
    void tour(int n,Maze& maze);
    void init();
    void updateP();
    bool findPath(Maze& maze);
    int choNext(int n,Maze& maze);
};

#endif // ACO_H
