#ifndef MYTHREADS_H
#define MYTHREADS_H

#include "socket.h"
#include "Struct.h"
#include <QObject>


class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

public slots:
    // 第一次获取数据，即获取发牌
    void myTimeout();
    // 发送
    void Send(CardShare p);
    // 接收
    void Read();

signals:
    void mySignal(CardShare p);// 第一次获取，即获取发牌
    void sendSuccess(); //消息发送成功
    void readSuccess(CardShare p); //接收消息成功
private:
    Socket clientSocket;
};

#endif // MYTHREADS_H
