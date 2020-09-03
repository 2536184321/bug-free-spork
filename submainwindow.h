#ifndef SUBMAINWINDOW_H
#define SUBMAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class subMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit subMainWindow(QWidget *parent = nullptr);

    void sendSlot();

signals:
    //信号在此声明，使用：emit mySignal();
    void mySignal();

public slots:

private:
    QPushButton b;
};

#endif // SUBMAINWINDOW_H
