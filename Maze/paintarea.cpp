#include "paintarea.h"
#include<QDebug>
#include<astar.h>

PaintArea::PaintArea(QWidget *parent) : QWidget(parent),status(0)
{
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    this->resize(800,800);
}

void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if(status==1||status==2)
        drawMaze();
    if(status==2)
        drawPath();
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
    brush.setColor(QColor(0,255,255,255));
    brush.setStyle(Qt::SolidPattern);
    p.setBrush(brush);
    for(int i=star->path.size();i>=0;i--)
    {
        int x=star->path[i].first;
        int y=star->path[i].second;
        QRectF rect{y*step,x*step,step,step};
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











