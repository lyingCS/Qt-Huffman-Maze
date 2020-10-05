#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include<QMessageBox>
#include<huffmancomp.h>
#include<huffmandecomp.h>
#include<QDataStream>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    HuffmanComp* comp;
    HuffmanDecomp* deComp;
    QString buffer;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;
    QString fileName;
    void loadFile(QString fileName);
    QString outFileName;
};
#endif // WIDGET_H
