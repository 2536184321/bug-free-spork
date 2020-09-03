#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    GameModel *game;//游戏指针
    GameType game_type;//存储游戏类型

    int clickPosRow, clickPosCol;// 存储将点击的位置
    bool selectPos = false;//是否移动到合适位置

    //绘制
    void paintEvent(QPaintEvent * event);

    void initGame();
    void initAIGame();

    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void chessOneByPerson();
};

#endif // MAINWINDOW_H
