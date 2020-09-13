#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include<QPen>
#include<QBrush>
#include<QPainter>
#include<astar.h>
#include"maze.h"
#include<stackf.h>
#include<ga.h>
#include<aco.h>

class PaintArea : public QWidget
{
    Q_OBJECT
private:
    QPen pen;
    QBrush brush;
    Qt::FillRule fillRule;
    Maze *maze;
    int status;
    Astar *star;
    double step;
    StackF *stac;
    GA *ga;
    ACO *aco;

public:
    explicit PaintArea(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void initMaze(int,int);
    void drawMaze();
    void findPath();
    void drawPath();
    void findPath_2();
    void drawPath_2();
    void findPath_3(int times,int nums,int rate,int rate_2,int length);
    void drawPath_3();
    void findPath_4(int ants,int delta,double alpha,int iter,double minP,double maxP);
    void drawPath_4();

signals:

};

#endif // PAINTAREA_H
