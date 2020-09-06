#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;//执行MainWindow的构造函数

    w.show();

    return a.exec();
}
