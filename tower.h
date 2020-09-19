#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QString>

#include "mainwindow.h"

class MainWindow;
class QPainter;

class Tower
{
public:
    Tower(QPoint pos, MainWindow * game, QString path = ":/images/background12.jpg");
    ~Tower();
    Tower();

    void draw(QPainter * painter)const;//画出防御塔
private:
    QPoint m_pos;//防御塔的中心点
    QString m_path;//防御塔图片的路径

    int m_attackRange;//攻击范围
    static const QSize m_fixedSize;//防御塔图片的固定大小
    MainWindow * m_game;//指向mainwindow的指针

};

#endif // TOWER_H
