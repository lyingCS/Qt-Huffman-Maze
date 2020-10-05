#include "huffmandecomp.h"

HuffmanDecomp::HuffmanDecomp(QTextStream& in,QTextStream& out)
{
    root=buildTrie(in);
    in>>size;
    QString s=in.read(1);
    getCode(in);
    decomp(out);
}

HuffmanDecomp::Node* HuffmanDecomp::buildTrie(QTextStream& in)
{
    if(in.read(1)=="1")
        return new Node(0,in.read(1)[0]);
    return new Node(buildTrie(in),buildTrie(in));
}

void HuffmanDecomp::getCode(QTextStream &in)
{
    while(!in.atEnd())
    {
        char ch=in.read(1)[0].toLatin1();
//        qDebug()<<ch;
        QString s;
        for(int i=0;i<7;i++)
        {
            if(ch&1)
                s="1"+s;
            else
                s="0"+s;
            ch=(ch>>1);
        }
        huffmanCode+=s;
    }
}

void HuffmanDecomp::decomp(QTextStream &out)
{
    int pos=0;
    while(size>0)
    {
        Node* x=root;
        while(!x->isLeaf())
        {
            if(huffmanCode[pos++]=='0')
                x=x->left;
            else
                x=x->right;
        }
        out<<x->ch;
        size--;
    }
}
