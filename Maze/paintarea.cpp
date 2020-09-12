#include "paintarea.h"
#include<QDebug>
#include<astar.h>
#include<windows.h>
#include<QMessageBox>

PaintArea::PaintArea(QWidget *parent) : QWidget(parent),status(0)
{
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    this->resize(800,800);
}

void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if(status==1||status==2||status==3||4==status)
        drawMaze();
    if(status==2)
        drawPath();
    if(status==3)
        drawPath_2();
    if(status==4)
        drawPath_3();
}

void PaintArea::initMaze(int m, int n)
{
    maze=new Maze(m,n);
    status=1;
    update();
}

void PaintArea::drawMaze()
{
    double m=maze->height,n=maze->width,height,width;
    if(m>n)
        width=800*n/m,height=800;
    else
        height=800*m/n,width=800;
    this->resize(width,height);
    step=height/maze->height;
    QPainter p(this);
    p.drawLine(0,step,0,height);
    p.drawLine(step,0,width,0);
    p.drawLine(0,height,width-step,height-1);
    p.drawLine(width,0,width-1,height-step);

    for(int i=0;i<m;i++)
    {
        for(int j=1;j<n;j++)
        {
            int num=i*n+j;
            if(!maze->s.count({num,num-1}))
                p.drawLine(step*j,i*step,step*j,i*step+step);
        }
    }
    for(int i=1;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            int num=i*n+j;
            if(!maze->s.count({num,num-n}))
                p.drawLine(j*step,i*step,j*step+step,i*step);
        }
    }
}

void PaintArea::drawPath()
{
    QPainter p(this);
    brush.setColor(QColor(255,0,0));
    brush.setStyle(Qt::SolidPattern);
    p.setBrush(brush);
    for(int i=star->path.size()-1;i>=0;i--)
    {
        int x=star->path[i].first;
        int y=star->path[i].second;
        QRectF rect{y*step+step/4,x*step+step/4,step/2,step/2};
        p.drawEllipse(rect);
    }
}

void PaintArea::findPath()
{
    star=new Astar(*maze);
    star->findpath(*maze);
    status=2;
    update();
}

void PaintArea::findPath_2()
{
    stac=new StackF(*maze);
    stac->findPath(*maze);
    status=3;
    update();
}

void PaintArea::drawPath_2()
{
    QPainter p(this);
    brush.setColor(QColor(255,0,0));
    brush.setStyle(Qt::SolidPattern);
    p.setBrush(brush);
    for(int i=0;i<(int)stac->path.size();i++)
    {
        int x=stac->path[i].first;
        int y=stac->path[i].second;
        QRectF rect{y*step+step/4,x*step+step/4,step/2,step/2};
        p.drawEllipse(rect);
    }
}

void PaintArea::findPath_3(int times,int nums,int rate,int rate_2)
{
    ga=new GA(*maze,times,nums,rate,rate_2);
    if(!ga->findPath(*maze))
        QMessageBox::critical(this,"Error","Path not found, try change the evolution times, parents number or the mutation rate...");
    status=4;
    update();
}

void PaintArea::drawPath_3()
{
    QPainter p(this);
    brush.setColor(QColor(255,0,0));
    brush.setStyle(Qt::SolidPattern);
    p.setBrush(brush);
    auto path=ga->parents[ga->king.num].genes;
    int x=0,y=0;
    QRectF rect{y*step+step/4,x*step+step/4,step/2,step/2};
    p.drawEllipse(rect);
    for(int i=0;i<(int)path.size();i++)
    {
        int score=x*maze->width+y;
        if(path[i]==0)
        {
            if(0==x||!maze->s.count({score,score-maze->width}))
                continue;
            x--;
        }
        else if(path[i]==1)
        {
            if(maze->height-1==x||!maze->s.count({score,score+maze->width}))
                continue;
            x++;
        }
        else if(path[i]==2)
        {
            if(0==y||!maze->s.count({score,score-1}))
                continue;
            y--;
        }
        else
        {
            if(maze->width==y||!maze->s.count({score,score+1}))
                continue;
            y++;
        }
        QRectF rect{y*step+step/4,x*step+step/4,step/2,step/2};
        p.drawEllipse(rect);
        if(x==maze->height-1&&y==maze->width-1)
            break;
    }
}



