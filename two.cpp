#include "two.h"
#include "ui_two.h"

Two::Two(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Two)
{
    ui->setupUi(this);
}

Two::~Two()
{
    delete ui;
}

void Two::on_pushButton_clicked(){
    emit display(0);
}
