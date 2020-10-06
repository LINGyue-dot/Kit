#ifndef TWO_H
#define TWO_H

#include "mythread.h"
#include <QWidget>

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


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked(); // 点击开始游戏开启连接服务器线程

private:
    Ui::Two *ui;

    MyThread *thread;
};

#endif // TWO_H
