#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);


protected:
    // virtual 函数
    //  线程处理函数
    // 不可以直接调用，要通过start间接调用
    void run();


signals:
    void IsDone();

};

#endif // MYTHREAD_H
