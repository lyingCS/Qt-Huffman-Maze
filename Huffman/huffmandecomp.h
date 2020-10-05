#ifndef HUFFMANDECOMP_H
#define HUFFMANDECOMP_H

#include<QWidget>
#include<QTextStream>
#include<QDebug>

class HuffmanDecomp
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
    HuffmanDecomp(QTextStream& in,QTextStream& out);
private:
    Node* root;
    Node* buildTrie(QTextStream& in);
    void getCode(QTextStream& in);
    int size;
    QString huffmanCode;
    void decomp(QTextStream& out);
};

#endif // HUFFMANDECOMP_H
