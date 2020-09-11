#ifndef DISJSETS_H
#define DISJSETS_H

#include<vector>

using namespace std;

class DisjSets{
public:
    explicit DisjSets();
    explicit DisjSets(int numElements);

    int find(int x);
    void unionSets(int root1,int root2);
    void show();
    int num() const;

private:
    int size;
    vector<int> s;
};

#endif
