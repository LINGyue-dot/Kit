#ifndef TWO_H
#define TWO_H

#include "mythread.h"
#include "Struct.h"
#include  "socket.h"
#include "mylabel.h"
#include "compare.h"
#include <QWidget>

namespace Ui {
class Two;
}

class Two : public QWidget
{
    Q_OBJECT

signals:
    void display(int number);

    void startThread(); // 启动子线程的信号

    void sendMessage(CardShare p); // 发送消息的信号

    void waitRecv();

    void closeThread();
public:
    explicit Two(QWidget *parent = nullptr);
    ~Two();

    void showTable(CardShare p);// 将牌显示到牌桌中间
    int fun1(int x);
    int fun2(int x);


public slots:
    void dealSignal(CardShare p); // 线程结束处理信号

    void dealClose(); // 处理关闭窗口

    void afterSend(); // 发送成功处理

    void afterGet(CardShare p); //接收成功后操作

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked(); // 点击开始游戏开启连接服务器线程

private:
    Ui::Two *ui;

    MyThread *myT;
    QThread *thread;
    QTimer *myTimer;

    mylabel *myarray[20];
    int position[20];
    int a[5]={0,0,0,0,0};
    QString s[54];
    QLabel *myarray2[15];

    Socket clientSockt;
    CardShare p2;
    bool recvFirst;
};

#endif // TWO_H
