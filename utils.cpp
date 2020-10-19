#include "utils.h"

utils::utils()
{

}


/**
 * @brief utils::numChangeFirst 将随机值转化为比较值
 * @param x 随机值
 * @return  比较值
 */
int utils::numChangeFirst(int x)
{
    if(x>=0&&x<20)
    {
        return x;
    }else if(x>20&&x<40)
    {
        return x-20;
    }else if(x>40&&x<60)
    {
        return x-40;
    }else
    {
        return x-60;
    }
}


/**
 * @brief utils::numChangeSecond 将随机值转化为数组值
 * @param x 随机值
 * @return  数组值
 */
int utils::numChangeSecond(int x)
{
    if(x>0&&x<20)
    {
        return x-1;
    }else if(x>20&&x<40)
    {
        return x-6;
    }else if(x>20&&x<60)
    {
        return x-13;
    }else
    {
        return x-20;
    }
}

/**
 * @brief utils::pictureResult  胜利失败图片显示
 * @param pic
 */
void utils::pictureResult(QLabel *pic)
{
    QPropertyAnimation *anmationl=new QPropertyAnimation(pic,"geometry");
    anmationl->setDuration(1000);
    anmationl->setStartValue(QRect(pic->x(),pic->y(),pic->width(),pic->height()));
    anmationl->setEndValue(QRect(pic->x(),pic->y()+400,pic->width(),pic->height()));
    anmationl->setEasingCurve(QEasingCurve::OutBounce);
    anmationl->start();
}
/**
 * @brief utils::pictureLoad    加载图片
 * @param lab   控件
 * @param str   路径
 */
void utils::pictureLoad(QLabel *lab,QString str)
{
    QImage image;
    image.load(str);
    QPixmap pixmap=QPixmap::fromImage(image);
    lab->setPixmap(pixmap);
    int h=lab->height();
    int w=lab->width();
    QPixmap map=pixmap.scaled(w,h,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    lab->setPixmap(map);
    lab->show();
}
