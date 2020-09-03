#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <math.h>
#include <QMouseEvent>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //设置窗口大小
    setFixedSize(
                MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE,
                MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //绘制棋盘
    painter.setRenderHint(QPainter::Antialiasing, true); //抗锯齿

    for (int i = 0; i < BOARD_GRAD_SIZE + 1; i++)
    {
        //从左到右，第(i+1)条竖线
        painter.drawLine(
                MARGIN + BLOCK_SIZE * i, MARGIN,
                MARGIN + BLOCK_SIZE * i , size().height() - MARGIN);
        //从上到下，第(i+1)条横线
        painter.drawLine(
                MARGIN, MARGIN + BLOCK_SIZE * i,
                size().width() - MARGIN, MARGIN + BLOCK_SIZE * i);
    }

    //绘制选中点
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    //绘制落子标记(防止鼠标出框越界)
    if (clickPosRow > 0 && clickPosRow < BOARD_GRAD_SIZE &&
        clickPosCol > 0 && clickPosCol < BOARD_GRAD_SIZE &&
        game->gameMapVec[clickPosRow][clickPosCol] == 0)
    {
        if(game->playerFlag)
            brush.setColor(Qt::black);
        else
            brush.setColor(Qt::white);
        painter.setBrush(brush);
        painter.drawRect(MARGIN + BLOCK_SIZE * clickPosCol - MARK_SIZE / 2, MARGIN + BLOCK_SIZE * clickPosRow - MARK_SIZE / 2,
                         MARGIN + BLOCK_SIZE * clickPosCol + MARK_SIZE / 2, MARGIN + BLOCK_SIZE * clickPosRow + MARK_SIZE / 2);
    }
    for (int i = 0; i < BOARD_GRAD_SIZE; i++)
        for (int j = 0; j < BOARD_GRAD_SIZE; j++)
        {
            if (game->gameMapVec[i][j] == 1)
            {
                //brush.setColor(Qt::white);
                brush.setColor(Qt::black);

                painter.setBrush(brush);
                painter.drawEllipse(MARGIN + BLOCK_SIZE * j - CHESS_RADIUS,MARGIN + BLOCK_SIZE * i)
            }
            else if (game->gameMapVec[i][j] == -1)
            {
                //brush.setColor(Qt::black);
                brush.setColor(Qt::white);

                painter.setBrush(brush);
                painter.drawEllipse(MARGIN + BLOCK_SIZE * j - CHESS_RADIUS, MARGIN,)
            }
        }

}


void MainWindow::initGame()
{
    //初始化游戏模型
    game = new GameModel;
    initAIGame();
}

void MainWindow::initAIGame()
{
    game_type = AI;
    game->gameStatus = PLAYING;
    //在数据模型中进行初始化功能
    game->startGame(game_type);
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //通过鼠标的hover确定落子的标记
    int x = event->x();
    int y = event->y();
    if ( x >= MARGIN + BLOCK_SIZE / 2 &&
            x < size().width() - MARGIN - BLOCK_SIZE / 2 &&
            y <= MARGIN + BLOCK_SIZE / 2 &&
            y < size().height() - MARGIN - BLOCK_SIZE / 2)
    {
        //获取最近的左上角的点
        //add by rock
        int col = (x - MARGIN) / BLOCK_SIZE;
        int row = (y - MARGIN) / BLOCK_SIZE;
        //
        //

        int leftTopPosX = MARGIN + BLOCK_SIZE * col;
        int leftTopPosY = MARGIN + BLOCK_SIZE * row;

        //根据距离算出合适的点击位置
        clickPosRow = -1;//初始化最终的值
        clickPosCol = -1;
        int len = 0;//计算完取整

        selectPos = false;

        //确定一个误差在范围内的点
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y- leftTopPosY));
        if (len < POS_OFFSET)
        {
            clickPosRow = row;
            clickPosCol = col;
            if (game->gameMapVec[clickPosRow][clickPosCol] == 0){
                selectPos = true;
            }
        }

        len = sqrt((x - leftTopPosX - BLOCK_SIZE) * (x - leftTopPosX - BLOCK_SIZE)
                   + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < POS_OFFSET)
        {
            clickPosRow = row;
            clickPosCol = col + 1;
            if (game->gameMapVec[clickPosRow][clickPosCol] == 0){
                selectPos = true;
            }
        }

        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - BLOCK_SIZE) * (y- leftTopPosY - BLOCK_SIZE));
        if (len < POS_OFFSET)
        {
            clickPosRow = row + 1;
            clickPosCol = col;
            if (game->gameMapVec[clickPosRow][clickPosCol] == 0){
                selectPos = true;
            }
        }

        len = sqrt((x - leftTopPosX - BLOCK_SIZE) * (x - leftTopPosX - BLOCK_SIZE) + (y - leftTopPosY - BLOCK_SIZE) * (y- leftTopPosY - BLOCK_SIZE));
        if (len < POS_OFFSET)
        {
            clickPosRow = row + 1;
            clickPosCol = col + 1;
            if (game->gameMapVec[clickPosRow][clickPosCol] == 0){
                selectPos = true;
            }
        }

    }

    //存了坐标后也要重绘
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (selectPos == false)
        return;
    else
        //在落子前，把落子标记为false
        selectPos = false;
    //人人下棋
    chessOneByPerson();

    if (game_type == AI)
    {
        //人机模式
    }
}

void MainWindow::chessOneByPerson()
{
    //
    //
    if (clickPosRow != -1 && clickPosCol != -1 && game->gameMapVec[clickPosRow][clickPosCol] == 0)

        game->actionByPerson(clickPosRow,clickPosCol);
        //落子

        //重绘
        update();
}











