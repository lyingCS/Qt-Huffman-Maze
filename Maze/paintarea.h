#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include<QPen>
#include<QBrush>
#include<QPainter>
#include<astar.h>
#include"maze.h"

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

public:
    explicit PaintArea(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void initMaze(int,int);
    void drawMaze();
    void findPath();
    void drawPath();

signals:

};

#endif // PAINTAREA_H
