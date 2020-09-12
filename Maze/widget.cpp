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
    ui->lineEdit->setEnabled(true);
    ui->lineEdit_2->setEnabled(true);
    ui->lineEdit_3->setEnabled(true);
    ui->lineEdit_4->setEnabled(true);
    ui->lineEdit_5->setEnabled(true);
    ui->findButton->setEnabled(true);
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
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

void Widget::on_pushButton_2_clicked()
{
    QString times=ui->lineEdit->text();
    QString nums=ui->lineEdit_2->text();
    QString rate=ui->lineEdit_3->text();
    QString rate_2=ui->lineEdit_4->text();
    QString length=ui->lineEdit_5->text();
    if(times.isEmpty())
    {
        QMessageBox::critical(this,"Error","Please input the evolution times!");
        return;
    }
    else if(times.toInt()<=0)
    {
        QMessageBox::critical(this,"Error","evolution times should>0");
        return;
    }
    if(nums.isEmpty())
    {
        QMessageBox::critical(this,"Error","Please input the parent number!");
        return;
    }
    else if(nums.toInt()<=20)
    {
        QMessageBox::critical(this,"Error","parent number should>20!");
        return;
    }
    if(rate.isEmpty())
    {
        QMessageBox::critical(this,"Error","Please input the mutation rate!");
        return;
    }
    else if(rate.toInt()<=0||rate.toInt()>20)
    {
        QMessageBox::critical(this,"Error","0<mutation rate<=20!");
        return;
    }
    if(rate_2.isEmpty())
    {
        QMessageBox::critical(this,"Error","Please input the survival rate!");
        return;
    }
    else if(rate_2.toInt()<=0||rate_2.toInt()>40)
    {
        QMessageBox::critical(this,"Error","0<survival rate<=40!");
        return;
    }
    if(length.isEmpty())
    {
        QMessageBox::critical(this,"Error","Please input the length!");
        return;
    }
    else if(length.toInt()<=5)
    {
        QMessageBox::critical(this,"Error","length>5!");
        return;
    }
    paintArea->findPath_3(times.toInt(),nums.toInt(),rate.toInt(),rate_2.toInt(),length.toInt());
}
