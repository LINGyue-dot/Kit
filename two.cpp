#include "two.h"
#include "ui_two.h"
#include "socket.h"

#include <QTextStream>
#include <stdio.h>

mylabel *myarray[20];
int position[20];

Two::Two(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Two)
{

    ui->setupUi(this);

    //*******************************连接服务器****************************************//
    QTextStream cout(stdout, QIODevice::WriteOnly);//  声明cout

    Socket clientSockt;
    clientSockt.Init();
    clientSockt.Connect("127.0.0.1",8000);

    Socket::CardShare p2=clientSockt.FirestRead();
    for(int i=0;i<=9;i++)
        cout<<p2.cardArr[i]<<"+++++++++++++++++"<<endl;
    cout<< p2.number<<endl;
//    cout<<"Send:"<<clientSockt.Send("hellpo",sizeof("hellpo"));
//    string c;
//    clientSockt.Read(c);
    cout<<"Send:"<<clientSockt.Send("hellpo",sizeof("hellpo"));
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
    s[15]=":/pukeimage1\\16.jpg";
    s[16]=":/pukeimage1\\17.jpg";
    for (int i=0;i<10 ;i++ ) {
        QImage image;
        image.load(s[p2.cardArr[i]+1+1]);
        QPixmap pixmap=QPixmap::fromImage(image);
        myarray[i]->setPixmap(pixmap);
        int h=myarray[i]->height();
        int w=myarray[i]->width();
        QPixmap map=pixmap.scaled(w,h,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

        myarray[i]->setPixmap(map);
    }
    //================================载入图片=========================================//0


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
