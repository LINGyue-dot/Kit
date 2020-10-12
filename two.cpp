#include "two.h"
#include "ui_two.h"
#include "socket.h"

#include <QDebug>
#include <QTextStream>
#include <QThread>
#include <QTimer>
#include <stdio.h>

int num;
Two::Two(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Two)
{

    ui->setupUi(this);
    //================================载入图片=========================================//
    s[0]=":/pukeimage1\\3.jpg";
    s[1]=":/pukeimage1\\4.jpg";
    s[2]=":/pukeimage1\\5.jpg";
    s[3]=":/pukeimage1\\6.jpg";
    s[4]=":/pukeimage1\\7.jpg";
    s[5]=":/pukeimage1\\8.jpg";
    s[6]=":/pukeimage1\\9.jpg";
    s[7]=":/pukeimage1\\10.jpg";
    s[8]=":/pukeimage1\\11.jpg";
    s[9]=":/pukeimage1\\12.jpg";
    s[10]=":/pukeimage1\\13.jpg";
    s[11]=":/pukeimage1\\14.jpg";
    s[12]=":/pukeimage1\\15.jpg";
    s[13]=":/pukeimage1\\2.jpg";
    s[14]=":/pukeimage1\\1.jpg";


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
    myarray[17]=ui->label_18;
    myarray[18]=ui->label_19;
    myarray[19]=ui->label_20;
    myarray2[0]=ui->label_21;
    myarray2[1]=ui->label_22;
    myarray2[2]=ui->label_23;
    myarray2[3]=ui->label_24;
    myarray2[4]=ui->label_25;
    myarray2[5]=ui->label_26;
    myarray2[6]=ui->label_27;
    myarray2[7]=ui->label_28;
    myarray2[8]=ui->label_29;
    myarray2[9]=ui->label_30;
    myarray2[10]=ui->label_31;
    myarray2[11]=ui->label_32;
    myarray2[12]=ui->label_33;
    myarray2[13]=ui->label_34;
    myarray2[14]=ui->label_35;
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    for(int i=0;i<15;i++)
    {
        myarray2[i]->hide();
    }
    int m=myarray[0]->x();
    int n=myarray[0]->y();
    position[0]=m;
    myarray[0]->hide();
    for (int i=1;i<20 ;i++ )
    {
        myarray[i]->setGeometry(m+25,n,72,141);
        myarray[i]->hide();
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
    CardShare p1;
    int number =0;
    p1.number =55;
    int k=0;
    int m=0;
    for (int i=0;i<20 ;i++ ) {
        if(myarray[i]->exist==2)
            myarray[i]->hide();

    }
    for (int i=0;i<20 ;i++ )
    {
        if(myarray[i]->value==10&&myarray[i]->exist==1)
        {
            myarray[i]->move(700+k*25,200);
            k=k+1;
            myarray[i]->exist=0;
            position[i]=0;
            p1.cardArr[number++]= myarray[i]->number;
        }
    }
    for (int i=0;i<20 ;i++ )
    {
        if(position[i]==0&&myarray[i]->exist==0)
        {
            for (int j=i+1;j<20 ;j++ )
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
    for(int x =number;x<15;x++)
        p1.cardArr[x]=0;
    /********************************发送数据到服务器上*************************************/

    emit sendMessage(p1); //发送数据
    /********************************发送数据到服务器上*************************************/
}

/**
 * @brief Two::on_pushButton_3_clicked 不出牌
 */
void Two::on_pushButton_3_clicked()
{
    for (int i=0;i<20 ;i++ )

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
    ui->pushButton_4->hide();
    ui->pushButton->setEnabled(false);
}


/**
 * @brief Two::showTable 别的玩家的出牌
 * @param p
 */
void Two::showTable(CardShare p){


    int m=100;
    switch (num) {
    case 1:
        if(p.number==2)
        {
            for (int i=0;i<15 ;i++ )
            {
                myarray2[i]->setGeometry(700,m,72,141);

                m=m+25;
            }
        }else if(p.number==3)
        {
            for (int i=0;i<15 ;i++ )
            {
                myarray2[i]->setGeometry(200,m,72,141);

                m=m+25;
            }
        }
        break;
    case 2:
        if(p.number==1)
        {
            for (int i=0;i<15 ;i++ )
            {
                myarray2[i]->setGeometry(700,m,72,141);

                m=m+25;
            }
        }else if(p.number==3)
        {
            for (int i=0;i<15 ;i++ )
            {
                myarray2[i]->setGeometry(200,m,72,141);

                m=m+25;
            }
        }
        break;
    case 3:
        if(p.number==1)
        {
            for (int i=0;i<15 ;i++ )
            {
                myarray2[i]->setGeometry(200,m,72,141);

                m=m+25;
            }
        }else if(p.number==2)
        {
            for (int i=0;i<15 ;i++ )
            {
                myarray2[i]->setGeometry(700,m,72,141);

                m=m+25;
            }
        }
        break;
    }
    for (int i=0;i<15 ;i++ )
    {
        myarray2[i]->setGeometry(200,m,72,141);

        m=m+25;
    }
    for(int i=0;i<15;i++)
    {
        if(p.cardArr[i]==0)
            myarray2[i]->hide();
        else
        {
            QImage image2;
            image2.load(s[p.cardArr[i]-1]);
            QPixmap pixmap2=QPixmap::fromImage(image2);
            myarray2[i]->setPixmap(pixmap2);
            int h2=myarray2[i]->height();
            int w2=myarray2[i]->width();
            QPixmap map2=pixmap2.scaled(w2,h2,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            myarray2[i]->show();
            myarray2[i]->setPixmap(map2);
        }
    }
}

/*************************************线程操作***************************/

/**
 * @brief Two::dealSignal 线程结束操作显示数据
 */
void Two::dealSignal(CardShare p){
    // 显示数据
    qDebug()<<"dealSignal的数据为：p.cardArr[16]:  "<<(p).cardArr[16]<<endl;
    int temp =17;
    if(p.number>=10){// 判断是否为地主
        temp =20;
        p.number-=10;
        qDebug()<<"p.arr[19]:  "<<p.cardArr[19]<<endl;
    }
    num=p.number;
    for (int i=0;i<17 ;i++ ) {

        QImage image;
        image.load(s[(p).cardArr[i]-1]);
        myarray[i]->number =p.cardArr[i];
        QPixmap pixmap=QPixmap::fromImage(image);
        myarray[i]->setPixmap(pixmap);
        int h=myarray[i]->height();
        int w=myarray[i]->width();
        QPixmap map=pixmap.scaled(w,h,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        myarray[i]->setPixmap(map);
        myarray[i]->show();
    }
    for(int i=17;i<20;i++)
    {
        if(temp==20)
        {
            QImage image3;
            image3.load(s[(p).cardArr[i]-1]);
            myarray[i]->number =p.cardArr[i];
            QPixmap pixmap3=QPixmap::fromImage(image3);
            myarray[i]->setPixmap(pixmap3);
            int h3=myarray[i]->height();
            int w3=myarray[i]->width();
            QPixmap map3=pixmap3.scaled(w3,h3,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            myarray[i]->setPixmap(map3);
            myarray[i]->show();
            ui->pushButton_2->show();
            ui->pushButton_3->show();

        }
        else
        {
            myarray[i]->hide();
        }
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

    // 发送成功后接收2次
    emit waitRecv();
    recvFirst =true;
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
}

/**
 * @brief Two::afterGet  接收到服务器发来的数据成功之后操作
 * @param p 接收到结构体
 */
void Two::afterGet(CardShare p){
    qDebug()<<"afterGet:  "<<p.cardArr[0]<<p.cardArr[1]<<"p.number: "<<p.number<<endl;
    showTable(p);
    // 如果仅接受了一次消息
    if(recvFirst){
//        emit waitRecv();
        recvFirst =false;
        ui->pushButton_2->show();
        ui->pushButton_3->show();
    }
}

/*************************************线程操作***************************/
