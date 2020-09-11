#include "maze.h"
#include "disjsets.h"
#include<QDebug>
Maze::Maze(){}
Maze::Maze(int _m,int _n):height(_m),width(_n){
    srand((unsigned)time(NULL));
    int size=_m*_n;
    st=DisjSets(size);
    while(st.find(0)!=st.find(size-1))
    {
        int rand_point_1=rand()%size;
        int flag=rand()%4;
        int rand_point_2;
        if(flag==0)
        {
            if(rand_point_1%_n==0)
                rand_point_2=rand_point_1+1;
            else
                rand_point_2=rand_point_1-1;
        }
        else if(flag==1)
        {
            if(rand_point_1%_n==_n-1)
                rand_point_2=rand_point_1-1;
            else
                rand_point_2=rand_point_1+1;
        }
        else if(flag==2)
        {
            if(rand_point_1/_n==0)
                rand_point_2=rand_point_1+_n;
            else
                rand_point_2=rand_point_1-_n;
        }
        else
        {
            if(rand_point_1/_n==_m-1)
                rand_point_2=rand_point_1-_n;
            else
                rand_point_2=rand_point_1+_n;
        }
        s.insert({rand_point_1,rand_point_2});
        s.insert({rand_point_2,rand_point_1});
        st.unionSets(rand_point_1,rand_point_2);
    }
    mp.resize(_m,vector<int>(_n,1));
}
