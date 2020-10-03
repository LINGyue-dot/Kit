#ifndef TWO_H
#define TWO_H

#include <QWidget>

namespace Ui {
class Two;
}

class Two : public QWidget
{
    Q_OBJECT

signals:
    void display(int number);
public:
    explicit Two(QWidget *parent = nullptr);
    ~Two();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Two *ui;
};

#endif // TWO_H
