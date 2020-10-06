#include "mythread.h"

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}


void MyThread::run(){
    emit IsDone();
}
