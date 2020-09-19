#include "tower.h"
#include "mainwindow.h"

#include <QPoint>
#include <QPainter>
#include <QString>

const QSize Tower::m_fixedSize(35,35);

Tower::Tower()
{

}

Tower::~Tower()
{
}

Tower::Tower(QPoint pos,MainWindow * game,QString path):
    m_pos(pos),
    m_path(path),
    m_attackRange(70),//根据地图的大小，确定攻击范围
    m_game(game)
{
}

void Tower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::green);
    painter->drawEllipse(m_pos,m_attackRange,m_attackRange);//画出防御塔的攻击范围
    painter->drawPixmap(m_pos.x()-m_fixedSize.width()/2,m_pos.y()-m_fixedSize.height()/2-10，path);//画出防御塔的图片
}
