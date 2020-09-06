#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QPainter>
#include <QMessageBox>
#include <gamemodel.h>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->PLAYER, &QPushButton::clicked, this, &MainWindow::changewin1);

    connect(ui->AI, &QPushButton::clicked, this, &MainWindow::changewin2);

    setWindowTitle("开始界面");

    //处理子窗口信号
    connect(&w, &subMainWindow::mySignal, this, &MainWindow::dealSub);

}


void MainWindow::changewin1()
{
    //子窗口显示
    w.show();
    w.initPERSONGame();
    //主窗口隐藏
    this->hide();
}

void MainWindow::changewin2()
{
    //子窗口显示
    w.show();
    w.initAIGame();
    //主窗口隐藏
    this->hide();
}

void MainWindow::dealSub()
{
    //子窗口隐藏
    w.hide();
    //主窗口显示
    this->show();

    connect(ui->PLAYER, &QPushButton::clicked, this, &MainWindow::changewin1);

    connect(ui->AI, &QPushButton::clicked, this, &MainWindow::changewin2);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{

}
