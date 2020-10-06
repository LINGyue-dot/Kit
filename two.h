#ifndef TWO_H
#define TWO_H

#include "mythread.h"
#include <QWidget>
#include  "socket.h"
#include <mylabel.h>

namespace Ui {
class Two;
}

class Two : public QWidget
{
    Q_OBJECT

signals:
    void display(int number);

public:
    explicit Two(QWidget *parent = nullptr);
    ~Two();

    void DeadDone(); // 线程结束处理槽函数
    void TimeOut(); // 定时器结束处理


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked(); // 点击开始游戏开启连接服务器线程

private:
    Ui::Two *ui;

    MyThread *thread;
    QTimer *myTimer;

    mylabel *myarray[20];
    int position[20];

    Socket clientSockt;
    Socket::CardShare p2;
};

#endif // TWO_H
