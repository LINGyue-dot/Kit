#ifndef COMPARE_H
#define COMPARE_H
#include <QtDebug>

class compare
{
public:
    compare();
    // 出牌是否符合规则，符合规则就return true
    static bool correctRules(int arr1[]);

     // 比较arr1和arr2的大小，如果arr1大 就return true
    static bool arr1Bigerarr2(int arr1[],int arr2[]);
};

#endif // COMPARE_H
