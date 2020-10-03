#include "one.h"
#include "ui_one.h"

One::One(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::One)
{
    ui->setupUi(this);
}

One::~One()
{
    delete ui;
}

void One::on_logoinButton_clicked(){
    emit display(1);
    QString s=ui->lineEdit->text(); //返回输入文本
             //传送输入文本

}

/**
 * @brief One::paintEvent 绘图设置背景图片
 * @param event
 */
void One::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap("../Kit/image/f.jpg"));	//传入资源图片路径
}

