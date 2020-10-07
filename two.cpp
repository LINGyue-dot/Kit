#include "two.h"
#include "ui_two.h"
#include "socket.h"

#include <QDebug>
#include <QTextStream>
#include <QThread>
#include <QTimer>
#include <stdio.h>

Two::Two(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Two)
{

    ui->setupUi(this);
    //================================载入图片=========================================//
    myarray[0]=ui->label;
    myarray[1]=ui->label_2;
    myarray[2]=ui->label_3;
    myarray[3]=ui->label_4;
    myarray[4]=ui->label_5;
    myarray[5]=ui->label_6;
    myarray[6]=ui->label_7;
    myarray[7]=ui->label_8;
    myarray[8]=ui->label_9;
    myarray[9]=ui->label_10;
    myarray[10]=ui->label_11;
    myarray[11]=ui->label_12;
    myarray[12]=ui->label_13;
    myarray[13]=ui->label_14;
    myarray[14]=ui->label_15;
    myarray[15]=ui->label_16;
    myarray[16]=ui->label_17;
    int m=myarray[0]->x();
    int n=myarray[0]->y();
    position[0]=m;
    for (int i=1;i<17 ;i++ )
    {
        myarray[i]->setGeometry(m+25,n,72,141);
        position[i]=m+25;
        m=m+25;
    }

    //================================载入图片=========================================//0
    /**********************************线程***************************************/
    // 动态分配空间, 不能指定父对象
    myT =new MyThread;

    //创建子线程
    thread =new QThread(this);

    //把自定义的线程加入到子线程中
    myT->moveToThread(thread);
    qDebug()<<"主线程："<<QThread::currentThread()<<endl;
    // 点击开始游戏按钮 接收到 startThread信号 调用 myTimeout函数
    connect(this,&Two::startThread,myT,&MyThread::myTimeout);
    // myTimeout函数执行完毕后即子线程执行完毕 发出mySignal信号 然后执行 dealSignal UI发牌
    connect(myT,&MyThread::mySignal,this,&Two::dealSignal,Qt::QueuedConnection);
    // 发送消息
    connect(this,&Two::sendMessage,myT,&MyThread::Send,Qt::QueuedConnection);
    connect(myT,&MyThread::sendSuccess,this,&Two::afterSend);

    // 接收消息
    connect(this,&Two::waitRecv,myT,&MyThread::Read);
    connect(myT,&MyThread::readSuccess,this,&Two::afterGet,Qt::QueuedConnection);

    // 窗口关闭 发送信号 引发槽函数关闭线程
    connect(this,&Two::destroyed,this,&Two::dealClose);
    /**********************************线程***************************************/

}

Two::~Two()
{
    delete ui;
}

void Two::on_pushButton_clicked(){
    emit display(0);
}

/**
 * @brief Two::on_pushButton_2_clicked 出牌
 */
void Two::on_pushButton_2_clicked()
{
    int k=0;
    int m=0;
    for (int i=0;i<17 ;i++ )
    {
        if(myarray[i]->value==10&&myarray[i]->exist==1)
        {
            myarray[i]->move(700+k*25,200);
            k=k+1;
            myarray[i]->exist=0;
            position[i]=0;
        }
    }
    for (int i=0;i<17 ;i++ )
    {
        if(position[i]==0&&myarray[i]->exist==0)
        {
            for (int j=i+1;j<17 ;j++ )
            {
                if(myarray[j]->exist==1)
                {
                    myarray[j]->move(position[j]-25,440);
                    position[j]=position[j]-25;
                }
            }
            myarray[i]->exist=2;
        }
    }
    /********************************发送数据到服务器上*************************************/
    CardShare p1;
    p1.cardArr[0]= 5;
    p1.cardArr[1]=2;
    p1.number =55;

    emit sendMessage(p1); //发送数据

    /********************************发送数据到服务器上*************************************/

}



/**
 * @brief Two::on_pushButton_3_clicked 不出牌
 */
void Two::on_pushButton_3_clicked()
{
    for (int i=0;i<17 ;i++ )

    {
        if(myarray[i]->value==10&&myarray[i]->exist==1)
        {
            myarray[i]->value=100;
            int x=myarray[i]->x();
            int y=myarray[i]->y();
            myarray[i]->move(x,y+50);
        }
    }
}


/**
 * @brief Two::on_pushButton_4_clicked 开始游戏开启线程 连接服务器
 */
void Two::on_pushButton_4_clicked(){

    // 启动线程,开始游戏
    thread->start();
    emit startThread(); // 发射信号 调用connect
}






/*************************************线程操作***************************/

/**
 * @brief Two::dealSignal 线程结束操作显示数据
 */
void Two::dealSignal(CardShare p){
    // 显示数据
    qDebug()<<"dealSignal的数据为：  "<<(p).cardArr[0]<<endl;
    QString s[17];
    s[0]=":/pukeimage1\\1.jpg";
    s[1]=":/pukeimage1\\2.jpg";
    s[2]=":/pukeimage1\\3.jpg";
    s[3]=":/pukeimage1\\4.jpg";
    s[4]=":/pukeimage1\\5.jpg";
    s[5]=":/pukeimage1\\6.jpg";
    s[6]=":/pukeimage1\\7.jpg";
    s[7]=":/pukeimage1\\8.jpg";
    s[8]=":/pukeimage1\\9.jpg";
    s[9]=":/pukeimage1\\10.jpg";
    s[10]=":/pukeimage1\\11.jpg";
    s[11]=":/pukeimage1\\12.jpg";
    s[12]=":/pukeimage1\\13.jpg";
    s[13]=":/pukeimage1\\14.jpg";
    s[14]=":/pukeimage1\\15.jpg";
    for (int i=0;i<17 ;i++ ) {
        QImage image;
        image.load(s[(p).cardArr[i]+1+1]);
        QPixmap pixmap=QPixmap::fromImage(image);
        myarray[i]->setPixmap(pixmap);
        int h=myarray[i]->height();
        int w=myarray[i]->width();
        QPixmap map=pixmap.scaled(w,h,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        myarray[i]->setPixmap(map);
    }
}


/**
 * @brief Two::dealClose 窗口关闭线程停止
 */
void Two::dealClose(){
    qDebug()<<"dealClose线程："<<QThread::currentThread();
    thread->quit();
    thread->wait();
}


/**
 * @brief Two::afterSend 发送成功之后操作
 */
void Two::afterSend(){


    emit waitRecv();
}


/**
 * @brief Two::afterGet  接收到服务器发来的数据成功之后操作
 * @param p 接收到结构体
 */
void Two::afterGet(CardShare p){
    qDebug()<<"afterGet:  "<<p.cardArr[0]<<p.cardArr[1]<<"p.number: "<<p.number<<endl;
}




/*************************************线程操作***************************/
