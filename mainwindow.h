#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "submainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



    void changewin1();

    void changewin2();

    void dealSub();

protected:
    //重写绘图事件
    void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui;

    //声明子窗口对象
    subMainWindow w;

};

#endif // MAINWINDOW_H
