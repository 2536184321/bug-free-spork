#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waypoint.h"
#include <QPainter>
#include "towerposition.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addWayPoint1();//增加航点函数的调用
    loadTowerPosition1();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QString path(":/images/background12.jpg");//path是你图片的路径

    painter.drawPixmap(0,0,750,375,path);

    foreach(const wayPoint * waypoint,m_wayPointList)
           waypoint->draw(&painter);
    foreach(const TowerPosition towerposition,m_towerPositionList)
           towerposition.draw(&painter);

}

void MainWindow::addWayPoint1()
{
     wayPoint * waypoint1=new wayPoint(QPoint(79,6));
    m_wayPointList.push_back(waypoint1);

    wayPoint * waypoint2=new wayPoint(QPoint(79,55));
    waypoint1->setNextWayPoint(waypoint2);
    m_wayPointList.push_back(waypoint2);

    wayPoint * waypoint3=new wayPoint(QPoint(407,55));
    waypoint2->setNextWayPoint(waypoint3);
    m_wayPointList.push_back(waypoint3);

    wayPoint * waypoint4=new wayPoint(QPoint(407,175));
    waypoint3->setNextWayPoint(waypoint4);
    m_wayPointList.push_back(waypoint4);

    wayPoint * waypoint5=new wayPoint(QPoint(83,175));
    waypoint4->setNextWayPoint(waypoint5);
    m_wayPointList.push_back(waypoint5);

    wayPoint * waypoint6=new wayPoint(QPoint(83,292));
    waypoint5->setNextWayPoint(waypoint6);
    m_wayPointList.push_back(waypoint6);

    wayPoint * waypoint7=new wayPoint(QPoint(473,292));
    waypoint6->setNextWayPoint(waypoint7);
    m_wayPointList.push_back(waypoint7);
}

void MainWindow::loadTowerPosition1()
{
    //这里和找航点是一样的，制作者需要自己不断尝试
    //找到比较合适的防御塔坑点
    QPoint pos[]=
    {
        QPoint(86,98),
        QPoint(226,98),
        QPoint(439,98),
        QPoint(105,215),
        QPoint(186,215),
        QPoint(314,215),
        QPoint(105,321),
        QPoint(223,323),
        QPoint(365,319)
    };
    int len=sizeof(pos)/sizeof(pos[0]);
    for(int i=0;i<len;i++)
    {
//        m_towerPositionList.push_back(pos[i]);
    }
}
