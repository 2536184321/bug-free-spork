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


    void changewin();
    void dealSub();
protected:
    //重写绘图事件
    void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui;
    QPushButton b1;
    QPushButton *b2;

    subMainWindow w;
};

#endif // MAINWINDOW_H
