#ifndef COMPARE_H
#define COMPARE_H


class compare
{
public:
    compare();
    int cardarray1[13];
    int len1;
    int cardarray2[13];
    int len2;
    int Send(int cardarray[], int len);
    void accept(int cardarray[],int len);
    int test();
    int sort(int cardarray[],int len);
};

#endif // COMPARE_H
