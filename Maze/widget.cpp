#include "widget.h"
#include "maze.h"
#include "ui_widget.h"
#include<QMessageBox>
#include<QPen>
#include<QPainter>
#include<QRect>

extern Maze maze;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::green));
    setAutoFillBackground(true);
    paintArea=new PaintArea(this);
    paintArea->move(70,70);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_makeButton_clicked()
{
    QString heightStr=ui->heightLineEdit->text();
    QString widthStr=ui->widthLineEdit->text();
    if(heightStr.isEmpty())
    {
        QMessageBox::critical(this,"Error","Please input the height!");
        return;
    }
    if(heightStr.toInt()<2||heightStr.toInt()>181)
    {
        QMessageBox::critical(this,"Error","1<height<182!");
        return;
    }
    if(widthStr.isEmpty())
    {
        QMessageBox::critical(this,"Error","Please input the width!");
        return;
    }
    if(widthStr.toInt()<2||widthStr.toInt()>181)
    {
        QMessageBox::critical(this,"Error","1<width<182!");
        return;
    }
    ui->label->setText("click \"find\" to find a path");
    ui->findButton->setEnabled(true);
    ui->pushButton->setEnabled(true);
    paintArea->initMaze(heightStr.toInt(),widthStr.toInt());
}

void Widget::on_findButton_clicked()
{
    paintArea->findPath();
}

void Widget::on_pushButton_clicked()
{
    paintArea->findPath_2();
}
