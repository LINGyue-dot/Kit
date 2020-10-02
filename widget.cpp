#include "widget.h"
#include "ui_widget.h"
#include "one.h"
#include "two.h"
#include <QStackedLayout>
#include <QPushButton>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
//     //设置主界面大小
    setFixedSize(840,625);
//    // 设置无边框
//    setWindowFlags(Qt::FramelessWindowHint);
//    // 背景透明
//    setAttribute(Qt::WA_TranslucentBackground, true);
//*********************************点击按钮页面切换**********************************//
    one = new One;
    two = new Two;
    stackLayout =new QStackedLayout;
    stackLayout->addWidget(one);
    stackLayout->addWidget(two);
    connect(one,&One::display,stackLayout,&QStackedLayout::setCurrentIndex);
    connect(two,&Two::display,stackLayout,&QStackedLayout::setCurrentIndex);
    mainLayout =new QVBoxLayout;
    mainLayout->addLayout(stackLayout);
    setLayout(mainLayout);
//*********************************点击按钮页面切换**********************************//
}

Widget::~Widget()
{

}


