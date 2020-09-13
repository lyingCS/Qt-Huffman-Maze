#include "widget.h"
#include "maze.h"
#include "ui_widget.h"
#include<QMessageBox>
#include<QPen>
#include<QPainter>
#include<QRect>
#include<string>
#include<QDebug>

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
    ui->findAcoButton->setEnabled(true);
    ui->antsLineEdit->setEnabled(true);
    ui->deltaLineEdit->setEnabled(true);
    ui->alphaLineEdit->setEnabled(true);
    ui->iterLineEdit->setEnabled(true);
    ui->minLineEdit->setEnabled(true);
    ui->maxLineEdit->setEnabled(true);
    paintArea->initMaze(heightStr.toInt(),widthStr.toInt());
    ui->antsLineEdit->setText(QString::number(paintArea->maze->height*paintArea->maze->width*(paintArea->maze->height+paintArea->maze->width)/2));
    ui->minLineEdit->setText(QString::number(0.5/(paintArea->maze->height+paintArea->maze->width)));
    ui->maxLineEdit->setText(QString::number(3*ui->minLineEdit->text().toDouble()));
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

void Widget::on_findAcoButton_clicked()
{
    QString ants=ui->antsLineEdit->text();
    QString delta=ui->deltaLineEdit->text();
    QString alpha=ui->alphaLineEdit->text();
    QString iter=ui->iterLineEdit->text();
    QString minP=ui->minLineEdit->text();
    QString maxP=ui->maxLineEdit->text();
    if(ants.isEmpty())
    {
        QMessageBox::critical(this,"Error","Please input the ants number!");
        return;
    }
    else if(ants.toInt()<=10)
    {
        QMessageBox::critical(this,"Error","ants number>10!");
        return;
    }
    if(delta.isEmpty())
    {
        QMessageBox::critical(this,"Error","Please input the delta!");
        return;
    }
    else if(delta.toInt()<=0)
    {
        QMessageBox::critical(this,"Error","delta>0!");
        return;
    }
    if(alpha.isEmpty())
    {
        QMessageBox::critical(this,"Error","Please input the alpha!");
        return;
    }
    else if(alpha.toDouble()<=0||alpha.toDouble()>=1)
    {
        QMessageBox::critical(this,"Error","0<alpha<1!");
        return;
    }
    if(iter.isEmpty())
    {
        QMessageBox::critical(this,"Error","Please input the iteration times!");
        return;
    }
    else if(iter.toInt()<=0)
    {
        QMessageBox::critical(this,"Error","iteration times>=0!");
        return;
    }
    if(minP.isEmpty())
    {
        QMessageBox::critical(this,"Error","Please input the min of peromone!");
        return;
    }
    else if(minP.toDouble()<=0||minP.toDouble()>=0.5)
    {
        QMessageBox::critical(this,"Error","0<min of peromone<0.5!");
        return;
    }
    if(maxP.isEmpty())
    {
        QMessageBox::critical(this,"Error","Please input the max if peromone!");
        return;
    }
    else if(maxP.toDouble()<=minP.toDouble())
    {
        QMessageBox::critical(this,"Error","maxP>minP!");
        return;
    }
    paintArea->findPath_4(ants.toInt(),delta.toInt(),alpha.toDouble(),iter.toInt(),minP.toDouble(),maxP.toDouble());
}































