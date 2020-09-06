#include "submainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <math.h>
#include "mainwindow.h"
#include <QPushButton>
#include <QMessageBox>


#include <QTimer>

subMainWindow::subMainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("游戏界面");
    setMouseTracking(true);

    // 设置棋盘大小
    setFixedSize(MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE + 200,
                 MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE);

    b1.setParent(this);
    b1.move(MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE,
            MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE-800);
    b1.resize(150, 100);
    b1.setText("返回主菜单");
    connect(&b1, &QPushButton::clicked, this, &subMainWindow::sendSlot);

    b2.setParent(this);
    b2.move(MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE,
            MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE-500);
    b2.resize(150, 100);
    b2.setText("悔棋");
    connect(&b2, &QPushButton::clicked, this, &subMainWindow::regret);
}

void subMainWindow::sendSlot()
{
    emit mySignal();
}

void subMainWindow::regret()
{
    if (game_type == AI)
    {
        game->gameMapVec[clickPosRow1][clickPosCol1] = 0;
        game->gameMapVec[clickPosRow2][clickPosCol2] = 0;
    }
    else if (game_type == PERSON)
    {
        game->gameMapVec[clickPosRow1][clickPosCol1] = 0;
        game->playerFlag = !game->playerFlag;
    }

    update();
}

void subMainWindow::paintEvent(QPaintEvent *event)
{

    b1.setParent(this);
    b1.move(MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE,
            MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE-800);
    b1.resize(150, 100);
    b1.setText("返回主菜单");

    b2.setParent(this);
    b2.move(MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE,
            MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE-500);
    b2.resize(150, 100);
    b2.setText("悔棋");

    QPainter painter(this);
    // 绘制棋盘
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

    for (int i = 0; i < BOARD_GRAD_SIZE + 1; i++)
    {
        // 从左到右，第(i+1)条竖线
        painter.drawLine(MARGIN + BLOCK_SIZE * i, MARGIN, MARGIN + BLOCK_SIZE * i, size().height() - MARGIN);
        // 从上到下，第（i+1)条横线
        painter.drawLine(MARGIN, MARGIN + BLOCK_SIZE * i, size().width() - MARGIN - 200, MARGIN + BLOCK_SIZE * i);
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    // 绘制落子标记(防止鼠标出框越界)
    if (clickPosRow > 0 && clickPosRow < BOARD_GRAD_SIZE &&
        clickPosCol > 0 && clickPosCol < BOARD_GRAD_SIZE &&
        game->gameMapVec[clickPosRow][clickPosCol] == 0)
    {
        if (game->playerFlag)
            brush.setColor(Qt::black);
        else
            brush.setColor(Qt::white);
        painter.setBrush(brush);
        painter.drawRect(MARGIN + BLOCK_SIZE * clickPosCol - MARK_SIZE / 2, MARGIN + BLOCK_SIZE * clickPosRow - MARK_SIZE / 2, MARK_SIZE, MARK_SIZE);
    }

    // 绘制棋子
    for (int i = 0; i < BOARD_GRAD_SIZE; i++)
        for (int j = 0; j < BOARD_GRAD_SIZE; j++)
        {
            if (game->gameMapVec[i][j] == 1)
            {

                brush.setColor(Qt::black);

                painter.setBrush(brush);
                painter.drawEllipse(MARGIN + BLOCK_SIZE * j - CHESS_RADIUS, MARGIN + BLOCK_SIZE * i - CHESS_RADIUS, CHESS_RADIUS * 2, CHESS_RADIUS * 2);
            }
            else if (game->gameMapVec[i][j] == -1)
            {

                brush.setColor(Qt::white);

                painter.setBrush(brush);
                painter.drawEllipse(MARGIN + BLOCK_SIZE * j - CHESS_RADIUS, MARGIN + BLOCK_SIZE * i - CHESS_RADIUS, CHESS_RADIUS * 2, CHESS_RADIUS * 2);
            }
        }

    // 判断输赢
    if (clickPosRow > 0 && clickPosRow < BOARD_GRAD_SIZE &&
        clickPosCol > 0 && clickPosCol < BOARD_GRAD_SIZE &&
        (game->gameMapVec[clickPosRow][clickPosCol] == 1 ||
            game->gameMapVec[clickPosRow][clickPosCol] == -1))
    {
        if (game->isWin(clickPosRow, clickPosCol) && game->gameStatus == PLAYING)
        {
            game->gameStatus = WIN;
            QString str;
            if (game->gameMapVec[clickPosRow][clickPosCol] == 1)
                str = "黑棋";
            else if (game->gameMapVec[clickPosRow][clickPosCol] == -1)
                str = "白棋";
            QMessageBox::StandardButton btnValue = QMessageBox::information(this, "五子棋决战", str + " 胜利!");

            // 重置游戏状态，否则容易死循环
            if (btnValue == QMessageBox::Ok)
            {
                game->startGame(game_type);
                game->gameStatus = PLAYING;
            }
        }
    }

}

void subMainWindow::initAIGame()
{
    game = new GameModel;
    game_type = AI;
    game->gameStatus = PLAYING;
    game->startGame(game_type);
    update();
}

void subMainWindow::initPERSONGame()
{
    game = new GameModel;
    game_type = PERSON;
    game->gameStatus = PLAYING;
    game->startGame(game_type);
    update();
}

void subMainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // 通过鼠标的hover确定落子的标记
    int x = event->x();
    int y = event->y();

    // 棋盘边缘不能落子
    if (x >= MARGIN + BLOCK_SIZE / 2 &&
            x < size().width() - MARGIN - BLOCK_SIZE / 2  &&
            y >= MARGIN + BLOCK_SIZE / 2 &&
            y < size().height()- MARGIN - BLOCK_SIZE / 2)
    {
        // 获取最近的左上角的点
        // add by rock
        int col = (x - MARGIN) / BLOCK_SIZE;
        int row = (y - MARGIN) / BLOCK_SIZE;
        //int col = x / kBlockSize;
        //int row = y / kBlockSize;

        int leftTopPosX = MARGIN + BLOCK_SIZE * col;
        int leftTopPosY = MARGIN + BLOCK_SIZE * row;

        // 根据距离算出合适的点击位置,一共四个点，根据半径距离选最近的
        clickPosRow = -1; // 初始化最终的值
        clickPosCol = -1;
        int len = 0; // 计算完后取整就可以了

        selectPos = false;

        // 确定一个误差在范围内的点，且只可能确定一个出来
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < POS_OFFSET)
        {
            clickPosRow = row;
            clickPosCol = col;
            if (game->gameMapVec[clickPosRow][clickPosCol]==0) {
                selectPos = true;
            }
        }

        len = sqrt((x - leftTopPosX - BLOCK_SIZE) * (x - leftTopPosX - BLOCK_SIZE) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < POS_OFFSET)
        {
            clickPosRow = row;
            clickPosCol = col + 1;
            if (game->gameMapVec[clickPosRow][clickPosCol]==0) {
                selectPos = true;
            }
        }

        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - BLOCK_SIZE) * (y - leftTopPosY - BLOCK_SIZE));
        if (len < POS_OFFSET)
        {
            clickPosRow = row + 1;
            clickPosCol = col;
            if (game->gameMapVec[clickPosRow][clickPosCol]==0) {
                selectPos = true;
            }
        }

        len = sqrt((x - leftTopPosX - BLOCK_SIZE) * (x - leftTopPosX - BLOCK_SIZE) + (y - leftTopPosY - BLOCK_SIZE) * (y - leftTopPosY - BLOCK_SIZE));
        if (len < POS_OFFSET)
        {
            clickPosRow = row + 1;
            clickPosCol = col + 1;

            if (game->gameMapVec[clickPosRow][clickPosCol]==0) {
                selectPos = true;
            }

        }
    }



    // 存了坐标后也要重绘
    update();
}

void subMainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (selectPos == false) {
        return;
    } else {
        selectPos = false;
    }

    chessOneByPerson();

    if (game_type == AI) { //人机模式
        // AI 下棋
        QTimer::singleShot(AI_THINK_TIME, this, SLOT(chessOneByAI()));
    }
}

void subMainWindow::chessOneByPerson()
{
    // 根据当前存储的坐标下子
    // 只有有效点击才下子，并且该处没有子
    if (clickPosRow != -1 && clickPosCol != -1 && game->gameMapVec[clickPosRow][clickPosCol] == 0)
    {
        game->actionByPerson(clickPosRow, clickPosCol);
        clickPosCol2 = clickPosCol1;
        clickPosRow2 = clickPosRow1;//上上步
        clickPosRow1 = clickPosRow;
        clickPosCol1 = clickPosCol;//上步
        update();
    }
}

void subMainWindow::chessOneByAI()
{
    game->actionByAI(clickPosRow, clickPosCol);
    clickPosCol2 = clickPosCol1;
    clickPosRow2 = clickPosRow1;//上上步
    clickPosRow1 = clickPosRow;
    clickPosCol1 = clickPosCol;
    update();
}
