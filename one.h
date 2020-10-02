#ifndef ONE_H
#define ONE_H

#include <QWidget>
#include "two.h"
#include <QPainter>

namespace Ui {
class One;
}

class One : public QWidget
{
    Q_OBJECT

public:
    explicit One(QWidget *parent = nullptr);
    ~One();

protected:
    // 重绘事件
    void paintEvent(QPaintEvent *event);

private slots:
    void on_logoinButton_clicked();
private:
    Ui::One *ui;
    Two *two;

signals:
    // 用于切换页面
    void display(int number);
};

#endif // ONE_H
