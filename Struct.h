#ifndef STRUCT_H
#define STRUCT_H

#include <QMetaType>

// 发牌结构体
typedef struct CardShare {
    int cardArr[20]; // 发配牌数组
    int number; // 玩家编号
}CardShare;
Q_DECLARE_METATYPE(CardShare);




#endif // STRUCT_H
