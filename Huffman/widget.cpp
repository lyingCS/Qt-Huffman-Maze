#include "widget.h"
#include "ui_widget.h"
#include<QtDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    fileName=QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("txt(*.txt)"));
    if(fileName.endsWith("_comp.txt"))
        ui->pushButton_3->setEnabled(true),ui->pushButton_2->setEnabled(true);
    else
        ui->pushButton_2->setEnabled(true),ui->pushButton_3->setEnabled(false);
}

void Widget::loadFile(QString fileName)
{
    QFile data(fileName);
    if(data.open(QFile::ReadOnly|QFile::Truncate))
    {
        QTextStream in(&data);
        buffer=in.readAll();
        if(buffer.isEmpty())
        {
            QMessageBox::critical(this,"Error","Empty file!");
            return;
        }
        outFileName=fileName;
        outFileName.replace(outFileName.size()-4,4,"_comp.txt"),ui->label_2->setText(outFileName);
    }
    else
        QMessageBox::critical(this,"Error","Can't open the input file!");
}

void Widget::on_pushButton_2_clicked()
{
    if(!fileName.isEmpty())
    {
        loadFile(fileName);
        ui->label->setText(fileName);
    }
    QFile outPut(outFileName);
    if(outPut.open(QFile::WriteOnly|QFile::Truncate))
    {
        QTextStream out(&outPut);
        comp=new HuffmanComp(buffer,out);
    }
    else
    {
        QMessageBox::critical(this,"Error","Can't open the output file!");
        return;
    }
}

void Widget::on_pushButton_3_clicked()
{
    if(!fileName.isEmpty())
    {
        loadFile(fileName);
        ui->label->setText(fileName);
    }
    QFile data(fileName);
    if(data.open(QFile::ReadOnly|QFile::Truncate))
    {
        QTextStream in(&data);
        outFileName=fileName;
        outFileName.replace(outFileName.size()-4,4,"_demp.txt"),ui->label_2->setText(outFileName);
        QFile outPut(outFileName);
        if(outPut.open(QFile::WriteOnly|QFile::Truncate))
        {
            QTextStream out(&outPut);
            deComp=new HuffmanDecomp(in,out);
        }
        else
        {
            QMessageBox::critical(this,"Error","Can't open the output file!");
            return;
        }
    }
    else
        QMessageBox::critical(this,"Error","Can't open the input file!");
}
