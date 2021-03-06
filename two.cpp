#include "two.h"
#include "ui_two.h"
#include "socket.h"

#include <QDebug>
#include <QTextStream>
#include <QThread>
#include <QTimer>
#include <stdio.h>
#include<Qpropertyanimation>


Two::Two(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Two)
{

    ui->setupUi(this);
    //================================载入图片=========================================//

    imageImport();
    uiBand();
    startHide();
    hideButton();

    int m=myarray[0]->x();
    int n=myarray[0]->y();
    position[0]=m;
    myarray[0]->hide();
    for (int i=1;i<20 ;i++ )
    {
        myarray[i]->setGeometry(m+25,n,90,150);
        myarray[i]->hide();
        position[i]=m+25;
        m=m+25;
        // 初始化公共牌
        publicCard.cardArr[i]=0;
    }

    //============================创建胜利图片==========================================
    //    QLabel *winLabel=new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/pukeimage1\\1.jpg");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());
    QPixmap tmpPix2;
    tmpPix2.load(":/pukeimage1\\2.jpg");
    defLabel->setGeometry(0,0,tmpPix2.width(),tmpPix2.height());
    defLabel->setPixmap(tmpPix2);
    defLabel->setParent(this);
    defLabel->move((this->width()-tmpPix2.width())*0.5,-tmpPix2.height());


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

/**
 * @brief One::paintEvent 绘图设置背景图片
 * @param event
 */
void Two::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/23wKit/image/bg.jpg"));	//传入资源图片路径
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
    p1.number =num;

    for(int i=0;i<20;i++){
        if(myarray[i]->value==10&&myarray[i]->exist==1)
            p1.cardArr[number++]= myarray[i]->number;
    }


    for(int x =number;x<20;x++)
        p1.cardArr[x]=0;

    int changeNowCard[20],nowCard[20];

    for(int x =0;x<20;x++){
        nowCard[x]=utils::numChangeFirst(p1.cardArr[x]);
        changeNowCard[x] =utils::numChangeFirst(publicCard.cardArr[x]);
    }
    /********************************发送数据到服务器上*************************************/

    if(Compare.isCorrectRule(nowCard)&&((publicCard.number == num)||(Compare.arr1Bigerarr2(changeNowCard,nowCard)))){
        hideButton();

        emit sendMessage(p1); //发送数据
        publicCard.number= num;
        for(int i=0;i<20;i++){
            // 更新公共牌
            publicCard.cardArr[i]=p1.cardArr[i];
        }

        /*****************************开始移动牌到牌桌且 隐藏之前的*********************************************/
        int k=0;
        for (int i=0;i<20 ;i++ ) {
            if(myarray[i]->exist==2)
                myarray[i]->hide();

        }
        for (int i=0;i<20 ;i++ )//移动到中央
        {
            if(myarray[i]->value==10&&myarray[i]->exist==1)
            {
                myarray[i]->move(700+k*25,450);
                k=k+1;
                myarray[i]->exist=0;
                position[i]=0;
            }
        }
        for (int i=0;i<20 ;i++ )//向左对齐
        {
            if(position[i]==0&&myarray[i]->exist==0)
            {
                for (int j=i+1;j<20 ;j++ )
                {
                    if(myarray[j]->exist==1)
                    {
                        myarray[j]->move(position[j]-25,680);
                        position[j]=position[j]-25;
                    }
                }
                myarray[i]->exist=2;
            }
        }
        vic=0;
        for (int i=0;i<20 ;i++ ) {
            if(myarray[i]->exist==1)
            {
                vic++;
            }
        }
        qDebug()<<"vic:"<<vic<<endl;
        if(vic==0)
        {
            qDebug()<<"胜利"<<endl;
            utils::pictureResult(winLabel);
        }
        /*****************************开始移动牌到牌桌且 隐藏之前的*********************************************/
    }else{
        // 不出牌
        for (int i=0;i<20 ;i++ )
        {
            if(myarray[i]->value==10&&myarray[i]->exist==1)
            {
                myarray[i]->value=100;
                int x=myarray[i]->x();
                int y=myarray[i]->y();
                myarray[i]->move(x,y+35);
            }
        }

    }
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
            myarray[i]->move(x,y+35);
        }
    }
    hideButton();
    emit sendMessage(publicCard); //发送数据
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

    for(int i=0;i<15;i++)
    {

        if(num==p.number)//别人都不出的情况
        {
            for(int i=0;i<15;i++)
            {
                myarray2[i]->hide();
            }
            return;
        }
    }


    int n=0;// 记牌器
    for(int i=0;i<15;i++)
    {
        if(p.cardArr[i]!=0)
            n++;
    }


    int flag =0; //p.arr是否与公共牌一致

    for(flag=0;flag<15;flag++){
        // 别的玩家不出牌 计数器不变化
        if(publicCard.cardArr[flag]!=p.cardArr[flag]  ||p.number!=publicCard.number)
            break;
    }
    if(flag ==15)         // 当 p arr 与公共拍一致时候
        n=0;

    switch (num) {
    case 1:
        if(p.number==2)
        {
            for (int i=0;i<15 ;i++ )
            {
                myarray2[i]->setGeometry(1200,m,90,150);

                m=m+35;
            }
            qDebug()<<"327 : line2: "<<line2<<" n"<<n<<"++++++++++++"<<endl;
            line2=line2-n;
            resultJudge(line2,p.number);
            surCard(line1,line2);
        }else if(p.number==3)
        {
            for (int i=0;i<15 ;i++ )
            {
                myarray2[i]->setGeometry(200,m,90,150);

                m=m+35;
            }
            qDebug()<<"339 : line1: "<<line1<<" n"<<n<<"++++++++++++"<<endl;
            line1=line1-n;
            resultJudge(line1,p.number);
            surCard(line1,line2);
        }
        break;
    case 2:
        if(p.number==1)
        {
            for (int i=0;i<15 ;i++ )
            {
                myarray2[i]->setGeometry(200,m,90,150);

                m=m+35;
            }

            qDebug()<<"355 : line1: "<<line1<<" n"<<n<<"++++++++++++"<<endl;
            line1=line1-n;
            resultJudge(line1,p.number);
            surCard(line1,line2);
        }else if(p.number==3)
        {
            for (int i=0;i<15 ;i++ )
            {
                myarray2[i]->setGeometry(1200,m,90,150);

                m=m+35;
            }
            qDebug()<<"367 : line2: "<<line2<<" n"<<n<<"++++++++++++"<<endl;
            line2=line2-n;
            resultJudge(line2,p.number);
            surCard(line1,line2);
        }
        break;
    case 3:
        if(p.number==1)
        {
            for (int i=0;i<15 ;i++ )
            {
                myarray2[i]->setGeometry(1200,m,90,150);

                m=m+35;

            }
            qDebug()<<"383 : line2: "<<line2<<" n"<<n<<"++++++++++++"<<endl;
            line2=line2-n;
            resultJudge(line2,p.number);
            surCard(line1,line2);
        }else if(p.number==2)
        {
            for (int i=0;i<15 ;i++ )
            {
                myarray2[i]->setGeometry(200,m,90,150);

                m=m+35;
            }
            qDebug()<<"395 : line1: "<<line1<<" n"<<n<<"++++++++++++"<<endl;
            line1=line1-n;
            resultJudge(line1,p.number);
            surCard(line1,line2);
        }
        break;
    }
    for(int i=0;i<15;i++)
    {
        if(p.cardArr[i]==0)
            myarray2[i]->hide();
        else
        {
            utils::pictureLoad(myarray2[i],s[utils::numChangeSecond(p.cardArr[i])]);
        }
    }

    // 更新公共牌
    publicCard.number=p.number;
    for(int i =0;i<20;i++){
        publicCard.cardArr[i]=p.cardArr[i];
    }

}

/*************************************线程操作***************************/

/**
 * @brief Two::dealSignal 线程结束操作显示数据 ,发牌
 */
void Two::dealSignal(CardShare p){
    // 显示数据

    qDebug()<<"dealSignal的数据为：p.cardArr[16]:  "<<(p).cardArr[16]<<endl;
    int temp =17;
    if(p.number>=10&&p.number<100){// 判断是否为地主,如果不是地主的话 则在百位表示地主是哪个玩家的编号
        temp =20;
        p.number-=10;
        diZhuNum =p.number;
        whichOne =1; //地主第一个出牌
        publicCard.number =p.number; // 刚刚开始出牌的空牌是地主
    }else{

        diZhuNum =p.number/100;
        p.number-=(p.number/100)*100;
        num=p.number;
        if((diZhuNum)%3==num-1){
            whichOne=2;
        }

        if((diZhuNum+1)%3==num-1){

            whichOne=3;
        }
    }
    num=p.number;
    switch (num) {
    case 1:
        if(num==diZhuNum)
        {
            line1=17;
            line2=17;
            ui->lineEdit_3->setText("农民");
            ui->lineEdit_4->setText("农民");
            ui->lineEdit_5->setText("地主");
            showLine();
            surCard(line1,line2);
            utils::pictureLoad(ui->label_39,":/character\\dz.jpg");
            utils::pictureLoad(ui->label_40,":/character\\nong.jpg");
            utils::pictureLoad(ui->label_41,":/character\\nong.jpg");
        }else if(diZhuNum==2)
        {
            line1=17;
            line2=20;
            ui->lineEdit_3->setText("农民");
            ui->lineEdit_4->setText("地主");
            ui->lineEdit_5->setText("农民");
            showLine();
            surCard(line1,line2);
            utils::pictureLoad(ui->label_41,":/character\\dz.jpg");
            utils::pictureLoad(ui->label_40,":/character\\nong.jpg");
            utils::pictureLoad(ui->label_39,":/character\\nong.jpg");
        }else
        {
            line1=20;
            line2=17;
            ui->lineEdit_3->setText("地主");
            ui->lineEdit_4->setText("农民");
            ui->lineEdit_5->setText("农民");
            showLine();
            surCard(line1,line2);
            utils::pictureLoad(ui->label_40,":/character\\dz.jpg");
            utils::pictureLoad(ui->label_41,":/character\\nong.jpg");
            utils::pictureLoad(ui->label_39,":/character\\nong.jpg");
        }
        break;
    case 2:
        if(num==diZhuNum)
        {
            line1=17;
            line2=17;
            ui->lineEdit_3->setText("农民");
            ui->lineEdit_4->setText("农民");
            ui->lineEdit_5->setText("地主");
            showLine();
            surCard(line1,line2);
            utils::pictureLoad(ui->label_39,":/character\\dz.jpg");
            utils::pictureLoad(ui->label_40,":/character\\nong.jpg");
            utils::pictureLoad(ui->label_41,":/character\\nong.jpg");
        }else if(diZhuNum==3)
        {
            line1=17;
            line2=20;
            ui->lineEdit_3->setText("农民");
            ui->lineEdit_4->setText("地主");
            ui->lineEdit_5->setText("农民");
            showLine();
            surCard(line1,line2);
            utils::pictureLoad(ui->label_41,":/character\\dz.jpg");
            utils::pictureLoad(ui->label_40,":/character\\nong.jpg");
            utils::pictureLoad(ui->label_39,":/character\\nong.jpg");
        }else
        {
            line1=20;
            line2=17;
            ui->lineEdit_3->setText("地主");
            ui->lineEdit_4->setText("农民");
            ui->lineEdit_5->setText("农民");
            showLine();
            surCard(line1,line2);
            utils::pictureLoad(ui->label_40,":/character\\dz.jpg");
            utils::pictureLoad(ui->label_41,":/character\\nong.jpg");
            utils::pictureLoad(ui->label_39,":/character\\nong.jpg");
        }
        break;
    case 3:
        if(num==diZhuNum)
        {
            line1=17;
            line2=17;
            ui->lineEdit_3->setText("农民");
            ui->lineEdit_4->setText("农民");
            ui->lineEdit_5->setText("地主");
            showLine();
            surCard(line1,line2);
            utils::pictureLoad(ui->label_39,":/character\\dz.jpg");
            utils::pictureLoad(ui->label_40,":/character\\nong.jpg");
            utils::pictureLoad(ui->label_41,":/character\\nong.jpg");
        }else if(diZhuNum==1)
        {
            line1=17;
            line2=20;
            ui->lineEdit_3->setText("农民");
            ui->lineEdit_4->setText("地主");
            ui->lineEdit_5->setText("农民");
            showLine();
            surCard(line1,line2);
            utils::pictureLoad(ui->label_41,":/character\\dz.jpg");
            utils::pictureLoad(ui->label_40,":/character\\nong.jpg");
            utils::pictureLoad(ui->label_39,":/character\\nong.jpg");
        }else
        {
            line1=20;
            line2=17;
            ui->lineEdit_3->setText("地主");
            ui->lineEdit_4->setText("农民");
            ui->lineEdit_5->setText("农民");
            showLine();
            surCard(line1,line2);
            utils::pictureLoad(ui->label_40,":/character\\dz.jpg");
            utils::pictureLoad(ui->label_41,":/character\\nong.jpg");
            utils::pictureLoad(ui->label_39,":/character\\nong.jpg");
        }
        break;

    }
    int b[3];
    for (int i=0;i<3 ;i++ )
    {
        b[i]=p.cardArr[i+17];
    }
    int tem;
    if(temp==20)
    {
        for(int i=0;i<19;i++)
        {
            for(int j=0;j<19-i;j++)
            {
                if(utils::numChangeFirst(p.cardArr[j])<utils::numChangeFirst(p.cardArr[j+1]))
                {
                    tem=p.cardArr[j];
                    p.cardArr[j]=p.cardArr[j+1];
                    p.cardArr[j+1]=tem;
                }
            }
        }
    }else
    {
        for(int i=0;i<16;i++)
        {
            for(int j=0;j<16-i;j++)
            {
                if(utils::numChangeFirst(p.cardArr[j])<utils::numChangeFirst(p.cardArr[j+1]))
                {
                    tem=p.cardArr[j];
                    p.cardArr[j]=p.cardArr[j+1];
                    p.cardArr[j+1]=tem;
                }
            }
        }
    }
    for (int i=0;i<17 ;i++ ) {
        utils::pictureLoad(myarray[i],s[utils::numChangeSecond(p.cardArr[i])]);
        myarray[i]->number =p.cardArr[i];
    }
    for(int i=17;i<20;i++)
    {
        if(temp==20)
        {
            utils::pictureLoad(myarray[i],s[utils::numChangeSecond(p.cardArr[i])]);
            myarray[i]->number =p.cardArr[i];
            utils::pictureLoad(myarray3[i-17],s[utils::numChangeSecond(b[i-17])]);

            // 2个按钮显示
            showButton();
        }
        else
        {
            utils::pictureLoad(myarray3[i-17],s[utils::numChangeSecond(b[i-17])]);
            myarray[i]->hide();
            myarray[i]->exist=0;
        }
    }



    //    qDebug()<<"475 : whichOne is "<<whichOne<<endl;
    // 地主无需等待，发送后 接收2个
    // 第二位 需要等待一次 再发送 ，再正常等待2次
    // 第三位 直接等待
    if(whichOne ==2){
        // 第二个出牌需要等待一次
        recvFirst =false;
        emit waitRecv();
    }
    if(whichOne ==3){
        //最后一个出牌,等待2次
        recvFirst =true;


        emit waitRecv();
    }
}

/**
 * @brief Two::dealClose 窗口关闭线程停止
 */
void Two::dealClose(){
    //    qDebug()<<"dealClose线程："<<QThread::currentThread();
    thread->quit();
    thread->wait();
}

/**
 * @brief Two::afterSend 发送成功之后操作
 */
void Two::afterSend(){
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    // 发送成功后接收2次
    recvFirst =true;
    emit waitRecv();


}

/**
 * @brief Two::afterGet  接收到服务器发来的数据成功之后操作
 * @param p 接收到结构体
 */
void Two::afterGet(CardShare p){
    qDebug()<<"afterGet:  "<<p.cardArr[0]<<p.cardArr[1]<<"p.number: "<<p.number<<endl;
    showTable(p); // 展示数据
    // 再发送之后接收2次
    if(recvFirst){
        emit waitRecv();
        recvFirst =false;
        return ;
    }

    // 展示2个按钮 出牌和不出牌
    showButton();


}

/*************************************线程操作***************************/


/**
 * @brief Two::resultJudge
 * @param x 剩余张数
 * @param y 接受到的编号
 */
void Two::resultJudge(int x, int y)
{
    if(x==0)//别人打完牌
    {
        if(y==diZhuNum)
        {

            qDebug()<<"失败"<<endl;
            utils::pictureResult(winLabel);
            banButton();
        }else if(num!=diZhuNum) //收到的不是地主，同时自己也不是地主
        {
            qDebug()<<"获胜"<<endl;
            utils::pictureResult(winLabel);
            banButton();
        }else                   //自己是地主
        {
            qDebug()<<"失败"<<endl;
            utils::pictureResult(defLabel);
            banButton();

        }
    }
}




/**
 * @brief Two::pictureLoad 导入图片
 */
void Two::imageImport()
{
    s[0]=":/pukeimage1\\3.jpg";s[15]=":/pukeimage1\\16.jpg";s[28]=":/pukeimage1\\29.jpg";s[41]=":/pukeimage1\\42.jpg";
    s[1]=":/pukeimage1\\4.jpg";s[16]=":/pukeimage1\\17.jpg";s[29]=":/pukeimage1\\30.jpg";s[42]=":/pukeimage1\\43.jpg";
    s[2]=":/pukeimage1\\5.jpg";s[17]=":/pukeimage1\\18.jpg";s[30]=":/pukeimage1\\31.jpg";s[43]=":/pukeimage1\\44.jpg";
    s[3]=":/pukeimage1\\6.jpg";s[18]=":/pukeimage1\\19.jpg";s[31]=":/pukeimage1\\32.jpg";s[44]=":/pukeimage1\\45.jpg";
    s[4]=":/pukeimage1\\7.jpg";s[19]=":/pukeimage1\\20.jpg";s[32]=":/pukeimage1\\33.jpg";s[45]=":/pukeimage1\\46.jpg";
    s[5]=":/pukeimage1\\8.jpg";s[20]=":/pukeimage1\\21.jpg";s[33]=":/pukeimage1\\34.jpg";s[46]=":/pukeimage1\\47.jpg";
    s[6]=":/pukeimage1\\9.jpg";s[21]=":/pukeimage1\\22.jpg";s[34]=":/pukeimage1\\35.jpg";s[47]=":/pukeimage1\\48.jpg";
    s[7]=":/pukeimage1\\10.jpg";s[22]=":/pukeimage1\\23.jpg";s[35]=":/pukeimage1\\36.jpg";s[48]=":/pukeimage1\\49.jpg";
    s[8]=":/pukeimage1\\11.jpg";s[23]=":/pukeimage1\\24.jpg";s[36]=":/pukeimage1\\37.jpg";s[49]=":/pukeimage1\\50.jpg";
    s[9]=":/pukeimage1\\12.jpg";s[24]=":/pukeimage1\\25.jpg";s[37]=":/pukeimage1\\38.jpg";s[50]=":/pukeimage1\\51.jpg";
    s[10]=":/pukeimage1\\13.jpg";s[25]=":/pukeimage1\\26.jpg";s[38]=":/pukeimage1\\39.jpg";s[51]=":/pukeimage1\\52.jpg";
    s[11]=":/pukeimage1\\14.jpg";s[26]=":/pukeimage1\\27.jpg";s[39]=":/pukeimage1\\40.jpg";s[52]=":/pukeimage1\\53.jpg";
    s[12]=":/pukeimage1\\15.jpg";s[27]=":/pukeimage1\\28.jpg";s[40]=":/pukeimage1\\41.jpg";s[53]=":/pukeimage1\\54.jpg";
    s[13]=":/pukeimage1\\2.jpg";
    s[14]=":/pukeimage1\\1.jpg";

}

/**
 * @brief Two::showButton   显示出牌和不出按钮
 */
void Two::showButton()
{
    ui->pushButton_2->show();
    ui->pushButton_3->show();
}

/**
 * @brief Two::hideButton   隐藏出牌和不出按钮
 */
void Two::hideButton()
{
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
}

/**
 * @brief ::Two::banButton  禁用出牌和不出按钮
 */
void Two::banButton()
{
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
}

/**
 * @brief Two::surCard  显示别家的剩余牌
 * @param line1 上家的牌数
 * @param line2 下家的牌数
 */
void Two::surCard(int line1, int line2)
{
    s1=QString::number(line1);
    s2=QString::number(line2);
    ui->lineEdit->setText(s1);
    ui->lineEdit_2->setText(s2);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
}

/**
 * @brief Two::uiBand 将控件和数组绑定
 */
void Two::uiBand()
{
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
    myarray3[0]=ui->label_36;
    myarray3[1]=ui->label_37;
    myarray3[2]=ui->label_38;
}
/**
 * @brief Two::showLine 显示lineEdit
 */
void Two::showLine()
{
    ui->lineEdit->show();
    ui->lineEdit_2->show();
    ui->lineEdit_3->show();
    ui->lineEdit_4->show();
    ui->lineEdit_5->show();
}
/**
 * @brief Two::startHide    开始时隐藏控件
 */
void Two::startHide()
{
    ui->label_39->hide();
    ui->label_40->hide();
    ui->label_41->hide();
    for(int i=0;i<15;i++)
    {
        myarray2[i]->hide();
    }
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->lineEdit_5->hide();
    ui->lineEdit_3->setEnabled(false);
    ui->lineEdit_4->setEnabled(false);
    ui->lineEdit_5->setEnabled(false);

    for(int i=0;i<3;i++)
    {
        myarray3[i]->hide();
    }
}
