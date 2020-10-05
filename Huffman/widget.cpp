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
    if(!fileName.isEmpty())
    {
        loadFile(fileName);
        ui->label->setText(fileName);
    }
}

void Widget::loadFile(QString fileName)
{
    QFile data(fileName);
    if(data.open(QFile::ReadOnly|QFile::Truncate))
    {
        QTextStream in(&data);
        in >> buffer;
        outFileName=fileName;
        if(outFileName.endsWith(tr("_comp.txt")))
            outFileName.replace(outFileName.size()-9,9,".txt"),ui->label_2->setText(outFileName);
        else
            outFileName.replace(outFileName.size()-4,4,"_comp.txt"),ui->label_2->setText(outFileName);
    }
    else
        QMessageBox::critical(this,"Error","Can't open this file!");
}

void Widget::on_pushButton_2_clicked()
{
    comp=new HuffmanComp(buffer);
    int i=0;
}

void Widget::on_pushButton_3_clicked()
{

}
