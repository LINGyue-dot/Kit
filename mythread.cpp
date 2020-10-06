#include "mythread.h"

#include <QThread>
#include <QDebug>

MyThread::MyThread(QObject *parent) : QObject(parent)
{
//    this->isGet =false;

    // clientSocket 初始化
    clientSocket.Init();
    clientSocket.Connect("127.0.0.1",8000);
    clientSocket.SettingTimeout(1); // 一秒后自动断开
}

/**
 * @brief MyThread::myTimeout 第一次获取即获取发牌
 */
void MyThread::myTimeout(){
    CardShare p;
    while(1){
        QThread::sleep(1);
        qDebug()<<"FirstGets子线程："<<QThread::currentThread();
        p=clientSocket.FirestRead();
        qDebug()<< "p :  "<< (p).cardArr[0]<<endl;
        if(p.cardArr[0]!=0)
            break;
    }
    qDebug()<<"成功接收  :"<<(p).cardArr[0]<<endl;
    emit mySignal(p); // 发出信号表示完成
}



/**
 * @brief MyThread::Send 发送函数
 * @param p 需要发送的结构体
 */
void MyThread::Send(CardShare p){
    while(1){
        QThread::sleep(1);
        qDebug()<<"Send子线程："<<QThread::currentThread();
        int i =clientSocket.Send(p);
        if(i>0)
            break;
    }
    emit sendSuccess();
}

/**
 * @brief Read 接收数据
 * @param p
 */
void MyThread::Read(){
    CardShare p;


    emit  readSuccess(p);
}





