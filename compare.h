#ifndef COMPARE_H
#define COMPARE_H
#include <QtDebug>

class compare
{
public:
    // 1 2 改为 12 13
    // 大小王改为 大王15 小王14
    //K Q J改为11 10 9
    //其余在牌值的基础上全部减二
    // 默认的arr成员都是经过排序 由 3- 大王（真值由0-15）
    // 默认的arr成员都为
    // 先判断长度，如果长度不相等 除非 是炸弹或者是王炸
    // 长度为 2 可能是王炸，可能是对子
    // 长度为 4 可能是 3+1 ，炸弹
    // 长度为 5 可能是连牌可能是 3+一个对
    // 长度为 6 可能是连牌可能是连对可能是4带2张单，4带一对
    // 长度大于等于7 连对或者连牌，飞机带数量级单牌（单牌不连续），飞机带数量级个对子（可以不连续）， 4带2对
    compare();

    // 比较arr1和arr2的大小，如果arr1大 就return true
    bool arr1Bigerarr2(int arr1[],int arr2[]);

    // 返回数组长度
    int returnLength(int arr[]);

    // 判断数组中是否相等
    bool isArrEqual(int arr[],int begin,int end);

private:
    bool isSingle(int *arr,int length); //单张
    bool isDouble(int *arr,int length); //对子张
    bool isThreeNot(int *arr,int length); // 3不带
    bool isThreeTakeSingle(int *arr,int length,int*value); // 3带一
    bool isThreeTakeDouble(int *arr,int length,int*value); //3带2
    bool isFourTakeTwo(int *arr,int length,int*value);// 4带2张单牌
    bool isFourTakeTwoDouble(int *arr,int length,int*value); // 4带一对
    bool isConnectSingle(int *arr,int length);// 连牌
    bool isConnectDouble(int *arr, int length); // 连对
    bool isPlaneTakeTwo(int *arr,int length); // 飞机带单牌
    bool isPlaneTakeDouble(int *arr,int length); //飞机带对子
    bool isBoom(int *arr,int length); //炸弹
    bool isKingBoom(int *arr,int length);//王炸
};

#endif // COMPARE_H
