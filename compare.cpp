#include "compare.h"

compare::compare()
{

}
void compare::accept(int cardarray[],int len)
{
    for(int i=0;i<len;i++)
    {
        cardarray1[i]=cardarray[0];
    }
}
int compare::Send(int *cardarray, int len)
{
    for(int i=0;i<len;i++)
    {
        cardarray2[i]=cardarray[i];
    }
}
int compare::test()
{
    if(len2==2&&(cardarray2[0]+cardarray2[1]==-1))
    {
        return 1;
    }
    if(len2==4&&cardarray2[0]==cardarray2[1]&&cardarray2[2]==cardarray2[3]&&cardarray2[2]==cardarray2[1])
    {
        if(len1==4&&cardarray1[0]==cardarray1[1]&&cardarray1[2]==cardarray1[3]&&cardarray1[2]==cardarray1[1]&&cardarray1[0]>cardarray2[0])
        {
            return 0;
        }
        return 1;
    }
    if(len1==len2)
    {
        int c1=sort(cardarray2,len2);
        if(c1=1&&cardarray2[0]>cardarray1[1])
        {
           return 1;
        }
        else
        {
            return 0;
        }
    }
}
int compare::sort(int *cardarray,int len)
{
    switch(len)
    {
    case 1:
        return 1
        ;
    case 2:
        if(cardarray[0]==cardarray[1])
            return 1;
        else
            return 0;
        ;
    case 3:
        if(cardarray[0]==cardarray[1]&&cardarray[1]==cardarray[2])
            return 1;
        else
            return 0;
        ;
    case 4:
        if(cardarray[0]==cardarray[1]&&cardarray[1]==cardarray[2])
            return 1;
        else
            return 0;
        ;
    case 5:
        if((cardarray[0]==cardarray[1]&&cardarray[1]==cardarray[2])||cardarray[0]-1==cardarray[1])
        {
            return 1;
        }
        else
        {
            return 0;
        }
    case 6:
        if((cardarray[0]==cardarray[1]&&cardarray[1]==cardarray[2]&&cardarray[2]==cardarray[3])||cardarray[0]-1==cardarray[1])
        {
            return 1;
        }
    default:
        for(int i=0;i<len-1;i++)
        {
            if(cardarray[i]==cardarray[i+1])
            {

            }
            else
            {
                return 0;
            }
        }
        return 1;
    }
}
