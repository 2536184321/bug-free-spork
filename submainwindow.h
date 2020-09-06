#ifndef SUBMAINWINDOW_H
#define SUBMAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "GameModel.h"

class subMainWindow : public QMainWindow
{
    Q_OBJECT
public:



    explicit subMainWindow(QWidget *parent = nullptr);

    // 绘制
    void paintEvent(QPaintEvent *event);

    void initAIGame();//AI模式

    void initPERSONGame();//玩家模式

    void sendSlot();

    void regret();

signals:
    //信号在此声明，使用：emit mySignal();
    void mySignal();


private:


    GameModel *game; // 游戏指针
    GameType game_type; // 存储游戏类型

    QPushButton b1, b2;


    int clickPosRow, clickPosCol; // 存储将点击的位置
    int clickPosRow1, clickPosCol1;//存储上一步点击的位置
    int clickPosRow2, clickPosCol2;//存储上上步点击的位置
    bool selectPos = false; // 是否移动到合适的位置

protected:



    void mouseMoveEvent(QMouseEvent *event);
    // 实际落子
    void mouseReleaseEvent(QMouseEvent *event);
    void chessOneByPerson();

private slots:
    void chessOneByAI();

};

#endif // SUBMAINWINDOW_H
