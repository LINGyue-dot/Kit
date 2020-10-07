#ifndef MYLABEL_H
#define MYLABEL_H
#include<QMouseEvent>
#include <QLabel>

class mylabel : public QLabel
{
    Q_OBJECT
public:
    explicit mylabel(QWidget *parent = nullptr);
    int value=100;
    int exist=1;
    int number;
protected:
    void mousePressEvent(QMouseEvent *e);

};

#endif // MYLABEL_H
