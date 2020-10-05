#include "huffmancomp.h"

HuffmanComp::HuffmanComp(QString buffer)
{
    for(auto x:buffer)
        countNum[x]++;
    for(auto i=countNum.begin();i!=countNum.end();i++)
    {
        que.push(new Node(i.value(),i.key()));
    }
    while((int)que.size()>1)
    {
        auto p1=que.top();
        que.pop();
        auto p2=que.top();
        que.pop();
        que.push(new Node(p1,p2));
    }
    buildCode(que.top(),"");
    return;
}

void HuffmanComp::buildCode(Node* node,QString s)
{
    if(node->isLeaf())
    {
        mp[node->ch]=s;
        return;
    }
    buildCode(node->left,s+'0');
    buildCode(node->right,s+'1');
}
