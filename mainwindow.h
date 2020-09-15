#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>

#include "waypoint.h"

namespace Ui {
class MainWindow;
}

class wayPoint;//新增对wayPoint类的说明

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addWayPoint1();//用来添加航点的函数

private:
    Ui::MainWindow *ui;
    QList<wayPoint * > m_wayPointList;//用来储存航点的list

protected:
    void paintEvent(QPaintEvent*);
};

#endif // MAINWINDOW_H
