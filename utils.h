#ifndef UTILS_H
#define UTILS_H
#include<QLabel>
#include<QPropertyAnimation>

class utils
{
public:
    utils();
    static int numChangeFirst(int);
    static int numChangeSecond(int);
    static void pictureResult(QLabel *);
    static void pictureLoad(QLabel *,QString );
};

#endif // UTILS_H
