#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPen>
#include<QBrush>
#include "paintarea.h"
#include"maze.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_makeButton_clicked();

    void on_findButton_clicked();

private:
    Ui::Widget *ui;
    PaintArea *paintArea;
};
#endif // WIDGET_H
