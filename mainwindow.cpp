#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("开始界面");
    b1.setParent(this);
    b1.setText("下一步");
    b1.move(100, 100);

    b2 = new QPushButton(this);
    b2->setText("close");

    //显示子窗口

    connect(&b1, &QPushButton:: released, this, &MainWindow::changewin);

    //自定义槽，普通函数的用法
    connect(b2, &QPushButton::released, this, &MainWindow::close);

    //处理子窗口信号
    connect(&w, &subMainWindow::mySignal, this, &MainWindow::dealSub);

    resize(1000, 900);

}


void MainWindow::changewin()
{
    //子窗口显示
    w.show();
    //主窗口隐藏
    this->hide();
}
void MainWindow::dealSub()
{
    //子窗口隐藏
    w.hide();
    //主窗口显示
    this->show();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(rect(), QPixmap("D:\QTproject\day01\07\Image\\001.jpg"));
}
