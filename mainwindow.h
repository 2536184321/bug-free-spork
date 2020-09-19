#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include "towerposition.h"
#include "tower.h"
#include "waypoint.h"

class Tower;

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
    void loadTowerPosition1();


    void addWayPoint1();//用来添加航点的函数

private:

    Ui::MainWindow *ui;
    QList<wayPoint * > m_wayPointList;//用来储存航点的list
    QList<TowerPosition> m_towerPositionList;
    QList<Tower *> m_towerList;

protected:
    void mousePressEvent(QMouseEvent *); // 鼠标点击函数
    void paintEvent(QPaintEvent*);
};

#endif // MAINWINDOW_H
