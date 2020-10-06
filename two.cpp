#include "two.h"
#include "ui_two.h"
#include "socket.h"

#include <QDebug>
#include <QTextStream>
#include <QTimer>
#include <stdio.h>

Two::Two(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Two)
{

    ui->setupUi(this);

    // 定时器
//    myTimer = new QTimer(this);
//    myTimer->start(100); // 设置100ms，定时触发timeout型号
//    connect(myTimer,&QTimer::timeout,
//            [=]()
//    {
//        p2=clientSockt.FirestRead();
//        if(p2.cardArr[0]!=0)
//            myTimer->stop();
//    }
//    );


    //*******************************连接服务器****************************************/
    QTextStream cout(stdout, QIODevice::WriteOnly);//  声明cout

    //    Socket clientSockt;
    clientSockt.Init();
    clientSockt.Connect("127.0.0.1",8000);
    clientSockt.SettingTimeout(1); // 一秒后自动断开
    //    Socket::CardShare p2;
    //    connect(p2, SIGNAL(signal()), this, SLOT(slot()));

//    p2=clientSockt.FirestRead(); //第一次接收 ，即发牌
    //    for(int i=0;i<17;i++)
    //        cout<<p2.cardArr[i]<<"+++++++++++++++++"<<endl;
    //    cout<< p2.number<<endl;
    //    cout<<"Send:"<<clientSockt.Send("hellpo",sizeof("hellpo"));
    //    string c;
    //    clientSockt.Read(c);

    Socket::CardShare p;
    p.cardArr[0]= 1;
    p.cardArr[1]=2;
    p.number =3;
    //    clientSockt.Send(p); // 发送
    //    Socket::CardShare p3=clientSockt.FirestRead(); // 接收
    //    cout<< p3.cardArr[0]<<p3.cardArr[1]<<p3.number<<"+++++++++"<<endl;
    //*******************************连接服务器****************************************//



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
    // 分配空间
    thread =new MyThread(this);
    connect(thread,&MyThread::IsDone,this,&Two::DeadDone);
    /**********************************线程***************************************/

}

Two::~Two()
{
    delete ui;
}

void Two::on_pushButton_clicked(){
    emit display(0);
}
//=========================================出牌=========================================//
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
    Socket::CardShare p1;
    p1.cardArr[0]= 5;
    p1.cardArr[1]=2;
    p1.number =55;
    clientSockt.Send(p1); // 发送
    /********************************发送数据到服务器上*************************************/
    Socket::CardShare p2=clientSockt.FirestRead(); // 接收
    Socket::CardShare p3=clientSockt.FirestRead(); // 接收
    /********************************接收数据从服务器上*************************************/

    /********************************接收数据从服务器上*************************************/
}
//============================================出牌=====================================//

//=======================================不出=============================================//
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
    thread->start(); // 开启线程
    //
    while(1){
        p2=clientSockt.FirestRead();
        if(p2.cardArr[0]!=0)
            break;
        QThread::sleep(1);
    }//第一次接收 ，即发牌
    qDebug()<<p2.cardArr[1]<<endl;
    ///
}






/*************************************线程操作***************************/
/**
 * @brief Two::DeadDone 线程结束操作
 */
void Two::DeadDone(){
    qDebug()<<"+++++++++++"<<p2.cardArr[0]<<p2.cardArr[1]<<endl;
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
        image.load(s[p2.cardArr[i]+1+1]);
        QPixmap pixmap=QPixmap::fromImage(image);
        myarray[i]->setPixmap(pixmap);
        int h=myarray[i]->height();
        int w=myarray[i]->width();
        QPixmap map=pixmap.scaled(w,h,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        myarray[i]->setPixmap(map);
    }
}


/*************************************线程操作***************************/
