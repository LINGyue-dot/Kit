#include "mylabel.h"

mylabel::mylabel(QWidget *parent) : QLabel(parent)
{

}
void mylabel::mousePressEvent(QMouseEvent *e)
{
    int x=this->x();
    int y=this->y();
    if(value==100)
    {
        if(exist==1)
        {
            this->move(x,y-50);
            value=10;
        }
    }else
    {
        if(exist==1){
            this->move(x,y+50);
            value=100;
        }
    }
}

