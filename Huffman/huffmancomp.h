#ifndef HUFFMANCOMP_H
#define HUFFMANCOMP_H
#include<QWidget>
#include<QTextStream>
#include<unordered_map>
#include<queue>
#include<QHash>
#include<QtDebug>
#include<QDataStream>

using namespace std;

class HuffmanComp
{
public:
    class Node{
    public:
        Node* left;
        Node* right;
        QChar ch;
        int freq;
        Node (int f,QChar c='\0'):left(nullptr),right(nullptr),ch(c),freq(f){}
        Node (Node* l,Node* r):left(l),right(r),ch('\0'),freq(l->freq+r->freq){}
        bool isLeaf(){return this->left==nullptr&&this->right==nullptr;}
    };
    class cmp{
    public:
        bool operator ()(Node* n1,Node* n2){
            return n1->freq>n2->freq;
        }
    };
    HuffmanComp(QString buffer,QTextStream& out);
private:
    QHash<QChar,int> countNum;
    priority_queue<Node*,vector<Node*>,cmp> que;
    QHash<QChar,QString> mp;
    void buildCode(Node* n,QString s);
    void writeTrie(QTextStream& out,Node* root);
    void writeCode(QTextStream& out,const QString& buffer);
};

#endif // HUFFMANCOMP_H
