#include "huffmancomp.h"

HuffmanComp::HuffmanComp(QString buffer,QDataStream& out)
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
    writeTrie(out,que.top());
    writeCode(out,buffer);
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

void HuffmanComp::writeTrie(QDataStream &out,Node* root)
{
    if(root->isLeaf())
    {
        out<<(bool)1;
        out<<(QChar)root->ch;
        return;
    }
    out<<(bool)0;
    writeTrie(out,root->left);
    writeTrie(out,root->right);
}

void HuffmanComp::writeCode(QDataStream& out,const QString& buffer)
{
    for(auto x:buffer)
    {
        for(auto y:mp[x])
        {
            if(y=="1")
                out<<(bool)1;
            else
                out<<(bool)0;
        }
    }
}
