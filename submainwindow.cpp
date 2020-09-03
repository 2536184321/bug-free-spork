#include "submainwindow.h"

subMainWindow::subMainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("游戏界面");
    b.setParent(this);
    b.setText("返回");

    connect(&b, &QPushButton::clicked, this, &subMainWindow::sendSlot);

    resize(1000, 900);

}

void subMainWindow::sendSlot()
{
    emit mySignal();
}
