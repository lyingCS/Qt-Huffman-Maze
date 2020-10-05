#include "huffmancomp.h"

HuffmanComp::HuffmanComp(QString buffer,QTextStream& out)
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

void HuffmanComp::writeTrie(QTextStream &out,Node* root)
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

void HuffmanComp::writeCode(QTextStream& out,const QString& buffer)
{
    QString s;
    out<<buffer.size()<<'\n';
    for(auto x:buffer)
    {
        s+=mp[x];
    }
    char ch=0;
    int cnt=0;
    for(int i=0;i<s.size();i++)
    {
        char k=s[i]=='1'?1:0;
        ch=(ch<<1)+k;
        cnt++;
        if(cnt==7)
        {
            out<<ch;
            cnt=0;
            ch=0;
        }
    }
    if(cnt==0)
        return;
    while(cnt!=7)
    {
        cnt++;
        ch=(ch<<1);
    }
    out<<ch;
}
