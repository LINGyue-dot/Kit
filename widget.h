#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qt_windows.h>
#include <Windowsx.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class One;
class Two;
class QStackedLayout;
class QVBoxLayout;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    One *one;
    Two *two;
    QStackedLayout *stackLayout;
    QVBoxLayout *mainLayout;
};
#endif // WIDGET_H
