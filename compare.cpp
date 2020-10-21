#include "compare.h"
compare::compare()
{
}
/**
 * @brief compare::isCorrectRule 出牌是否符合规则
 * @param arr
 * @return
 */
bool compare::isCorrectRule(int *arr){
    int arrLength =returnLength(arr);
    int nnnn=0;
    int *value=&nnnn;

    if(arrLength==1||isDouble(arr,arrLength)||isThreeNot(arr,arrLength)||
            isThreeTakeSingle(arr,arrLength,value)||isThreeTakeDouble(arr,arrLength,value)||
            isFourTakeTwo(arr,arrLength,value)||isFourTakeTwoDouble(arr,arrLength,value)||
            isConnectSingle(arr,arrLength)||isConnectDouble(arr,arrLength)||isPlaneTakeTwo(arr,arrLength)||
            isPlaneTakeDouble(arr,arrLength)||isBoom(arr,arrLength)||isKingBoom(arr,arrLength)||
            isPlaneTakeNot(arr,arrLength))
        return true;
    else
        return false;
}
/**
 * @brief compare::arr1Bigerarr2 比较arr1和arr2的大小，如果arr1大 就return true
 * @param arr1  牌桌上的牌
 * @param arr2  要出的牌
 * @return
 */
bool compare::arr1Bigerarr2(int arr1[],int arr2[]){
    int arr1Length =returnLength(arr1);
    int arr2Length=returnLength(arr2);
    // 当 长度不相等时候，除非是炸弹或者王炸要不无法比较
    if(arr1Length!=arr2Length){
        // 牌桌上无牌时候
        if(arr1Length==0)
            return true;
        // 要出的是王炸 , 牌桌上不是炸弹，而出的是
        if(isKingBoom(arr2,arr2Length)||(!isBoom(arr1,arr1Length)&&!isKingBoom(arr1,arr1Length)&&isBoom(arr2,arr2Length)))
            return true;
        return false;
    }
    // 长度相等时候比较, 先对规则
    if(arr1Length==arr2Length){
        int arr1Value=0;
        int arr2Value=0;
        // 1 张
        if(arr2Length ==1 && arr2[0]>arr1[0])
                    return true;
        // 2 对子
        if(arr2Length==2&&arr2[0]==arr2[1]){
            if(arr2[0]>arr1[0])
                return true;
            else
                return false;
        }
        // 3 3不带
        if(arr2Length==3&&arr2[0]==arr2[1]==arr2[2]){
            if(arr2[0]>arr1[0])
                return true;
            else
                return false;
        }
        //  4  可能是3+1  或者炸弹
        if(arr2Length==4){
            // 都为3+1
            if(isThreeTakeSingle(arr1,arr1Length,&arr1Value)&&isThreeTakeSingle(arr2,arr2Length,&arr2Value)){
                if(arr1Value<arr2Value)
                    return true;
                else
                    return false;
            }
            // 都为炸弹
            if(isBoom(arr1,arr1Length)&&isBoom(arr2,arr2Length)){
                if(arr1[0]<arr2[0])
                    return true;
                else
                    return false;
            }

            // 3+1 boom
            if(isThreeTakeSingle(arr1,arr1Length,&arr1Value)&&isBoom(arr2,arr2Length))
                return true;
            return false;
        }
        // 5  连牌或者 3+一对 顺子
        if(arr2Length==5){
            // 连牌
            if(isConnectSingle(arr1,arr1Length)&&isConnectSingle(arr2,arr2Length)){
                if(arr2[0]>arr1[0])
                    return true;
                else
                    return false;
            }
            // 3+一对
            if(isThreeTakeDouble(arr1,arr1Length,&arr1Value)&&isThreeTakeDouble(arr2,arr2Length,&arr2Value)){
                if(arr1Value<arr2Value)
                    return true;
                else
                    return false;
            }
            return false;
        }
        // 6 连牌 连对   4带2张单  4带一对 飞机
        if(arr2Length==6){
            // 连牌
            if(isConnectSingle(arr1,arr1Length)&&isConnectSingle(arr2,arr2Length)){
                if(arr2[0]>arr1[0])
                    return true;
                else
                    return false;
            }
            // 连对
            if(isConnectDouble(arr1,arr1Length)&&isConnectDouble(arr2,arr2Length)){
                if(arr1[0]<arr2[0])
                    return true;
                else
                    return false;
            }
            // 4带2张
            if(isFourTakeTwo(arr1,arr1Length,&arr1Value)&&isFourTakeTwo(arr2,arr2Length,&arr2Value)){
                if(arr1Value<arr2Value)
                    return true;
                else
                    return false;
            }
            // 飞机
            if(isPlaneTakeNot(arr1,arr1Length)&&isPlaneTakeNot(arr2,arr2Length)){
                if(arr1[0]<arr2[0])
                    return true;
                else
                    return false;
            }
            return false;
        }
        // 大于等于7  连对  连牌
        //飞机带数量级单牌（可以不连续），飞机带数量级对子（可以不连续）
        // 4 带2对
        if(arr2Length>=7){
            // 连对
            if(isConnectDouble(arr1,arr1Length)&&isConnectDouble(arr2,arr2Length)){
                if(arr1[0]<arr2[0])
                    return true;
                else
                    return false;
            }
            // 连牌
            if(isConnectSingle(arr1,arr1Length)&&isConnectSingle(arr2,arr2Length)){
                if(arr1Length<arr2Length)
                    return true;
                else
                    return false;
            }
            // 飞机带数量级对子
            if(isPlaneTakeDouble(arr1,arr1Length)&&isPlaneTakeDouble(arr2,arr2Length)){
                if(arr1[0]<arr2[0])
                    return true;
                else
                    return false;
            }
            //飞机带数量级单牌
            if(isPlaneTakeTwo(arr1,arr1Length)&&isPlaneTakeTwo(arr2,arr2Length)){
                if(arr1[0]<arr2[0])
                    return true;
                else
                    return false;
            }
            // 4带 2个对子，对子没有限制
            if(isFourTakeTwoDouble(arr1,arr1Length,&arr1Value)&&isFourTakeTwoDouble(arr2,arr2Length,&arr2Value)){
                if(arr1Value<arr2Value)
                    return true;
                else
                    return false;
            }
            // 飞机
            if(isPlaneTakeNot(arr1,arr1Length)&&isPlaneTakeNot(arr2,arr2Length)){
                if(arr1[0]<arr2[0])
                    return true;
                else
                    return false;
            }
        }
        return false;
    }
    return true;
}
/**
 * @brief compare::returnLength 返回数组长度
 * @param arr
 * @return
 */
int compare::returnLength(int *arr){
    int length=0;
    for(int i=0;i<15;i++){
        if(arr[i]==0)
            break;
        length++;
    }
    return length;
}
/**
 * @brief compare::isArrEqual 判断数组在一定长度内是否相等
 * @param arr
 * @param begin 开始的数组下标
 * @param end 结束的数组下标
 * @return
 */
bool compare::isArrEqual(int arr[],int begin,int end){
    bool flag =1;
    for(int j=begin+1;j<=end;j++){
        if(arr[begin]!=arr[j])
            flag=false;
    }
    return flag;
}
/**********************************规则判断****************************************/
/**
 * @brief compare::isDouble 是否为对子
 * @param arr
 * @param lenght
 * @return
 */
bool compare::isDouble(int *arr,int length){
    if(length!=2||arr[0]!=arr[1])
        return false;
    else
        return true;
}
/**
 * @brief compare::isThreeNot 3不带
 * @param arr
 * @param length
 * @return
 */
bool compare::isThreeNot(int *arr,int length){
    if(length!=3||arr[0]!=arr[1]||arr[0]!=arr[2]||arr[1]!=arr[2])
        return false;
    else
        return true;
}
/**
 * @brief compare::isThreeTakeSingle 3+1
 * @param arr
 * @param length
 * @return
 */
bool compare::isThreeTakeSingle(int *arr,int length,int *value){
    if(isArrEqual(arr,0,2)){
        *value=arr[0];
        return true;
    }
    if(isArrEqual(arr,1,3)){
        *value= arr[1];
        return true;
    }
    return false;
}
/**
 * @brief compare::isThreeTakeTwo 3+一对
 * @param arr
 * @param length
 * @return
 */
bool compare::isThreeTakeDouble(int*arr,int length,int *value){
    if(length!=5)
        return false;
    if(isArrEqual(arr,0,2)&&isArrEqual(arr,3,4)){
        *value = arr[0];
        return true;
    }
    if(isArrEqual(arr,0,1)&&isArrEqual(arr,2,4)){
        *value=arr[2];
        return true;
    }
    return false;
}
/**
 * @brief isFourTakeSingle 4+2单张
 * @param arr
 * @param length
 * @return
 */
bool compare::isFourTakeTwo(int*arr,int length,int *value){
    if(length!=6)
        return false;
    if(isArrEqual(arr,0,3)){
        *value = arr[0];
        return true;
    }
    if(isArrEqual(arr,2,5)){
        *value =arr[2];
        return true;
    }
    return false;
}
/**
 * @brief compare::isFourTakeTwoDouble 4+2对子
 * @param arr
 * @param length
 * @return
 */
bool compare::isFourTakeTwoDouble(int *arr,int length,int *value){
    if(length!=8)
        return false;
    // 100 010 001
    //1 00
    if(isArrEqual(arr,0,3)&&isArrEqual(arr,4,5)&&isArrEqual(arr,6,7)){
        *value=arr[0];
        return true;
    }
    if(isArrEqual(arr,0,1)&&isArrEqual(arr,2,5)&&isArrEqual(arr,6,7)){
        *value=arr[2];
        return true;
    }
    if(isArrEqual(arr,0,1)&&isArrEqual(arr,2,3)&&isArrEqual(arr,4,7)){
        *value =arr[4];
        return true;
    }
    return false;
}
/**
* @brief compare::isConnectSingle 连牌
* @param arr
* @param length 至少5张连续 3-K -A (1--11)
* @return
*/
bool compare::isConnectSingle(int *arr,int length){
    if(length<5)
        return false;
    if(arr[length-1]>13)
        return false;
    for(int j=1;j<length;j++){
        if(arr[j-1]!=arr[j]+1)
            return false;
    }
    return true;
}
/**
* @brief compare::isConnectDouble 连对
* @param arr
* @param length 连对至少
* @return
*/
bool compare::isConnectDouble(int*arr,int length){
    if(length<6)
        return false;
    int content=1;
    if(arr[0]!=arr[1])
        return false;
    int temp=2;
    for(int i =3;i<length;i=temp+1){
        if((arr[i]==arr[temp] )&&( arr[i]==arr[temp-1]-1)){
            content++;
            temp=i+1;

        }
        else {
            content=0;
            return false;
        }
    }
    if(content>=3)
        return true;
    return false;
}
/**
 * @brief compare::isPlaneTakeNot 飞机不带
 * @param arr
 * @param length
 * @return
 */
bool compare::isPlaneTakeNot(int *arr,int length){
    if(length<6||length%3!=0)
        return false;
    int begin =0;
    int end=begin+2;
    while(end<length){
        if(!isArrEqual(arr,begin,end))
            return false;
        begin=end+1;
        end=begin+2;
    }
    return true;
}
/**
* @brief compare::isPlaneTakeTwo 飞机带单牌 (会包含isPlaneDouble)
* @param arr
* @param length
* @return
*/
bool compare::isPlaneTakeTwo(int * arr,int length){
    if(length<8)
        return false;
    int begin =0;
    int end =begin+2;
    int planeContent=0;
    int single =0;
    int beginNumber=-1;
    int flag=0; // 开始3张牌
    while (end<length) {
        if(isArrEqual(arr,begin,end)){
            if(flag==-1)
                return false;
            if(beginNumber==-1){ // 第一个
                beginNumber=arr[begin];
            }else{ // 不是第一个时候
                if(beginNumber-1!=arr[begin])
                    return false;
                else
                    beginNumber =arr[begin];
            }
            flag=1;
            begin+=3;
            planeContent++;
        }else{
            if(flag==1)
                flag=-1;
            begin++;
            single++;
        }
        end=begin+2;
    }
    if(planeContent==single)
        return true;
    else
        return false;
}
/**
* @brief compare::isPlaneTakeDouble 飞机带对子
* @param arr
* @param length
* @return
*/
bool compare::isPlaneTakeDouble(int *arr,int length){
    if(length<10)
        return false;
    int begin =0;
    int end =begin+2;
    int planeContent=0;
    int doubles =0;
    int beginNumber =-1;
    int flag=0; // 开始3张牌
    while (end<length) {
        if(isArrEqual(arr,begin,end)){
            if(flag==-1)
                return false;
            if(beginNumber==-1){ // 第一个
                beginNumber=arr[begin];
            }else{ // 不是第一个时候
                if(beginNumber-1!=arr[begin])
                    return false;
                else
                    beginNumber =arr[begin];
            }
            flag=1;
            begin+=3;
            planeContent++;
        }else{
            if(flag==1)
                flag=-1;
            if(!isArrEqual(arr,begin,begin+1))
                return false;
            begin+=2;
            doubles++;
        }
        end=begin+2;
    }
    if(planeContent==doubles)
        return true;
    else
        return false;
}
/**
* @brief compare::isBoom 炸弹
* @param arr
* @param length
* @return
*/
bool compare::isBoom(int *arr,int length){
    if(length!=4)
        return false;
    for(int i =1;i<4;i++){
        if(arr[i]!=arr[i-1])
            return false;
    }
    return true;
}
/**
* @brief compare::isKingBoom 王炸
* @param arr
* @param length
* @return
*/
bool compare::isKingBoom(int *arr,int length){
    if(length==2&&arr[0]==15&&arr[1]==14)
        return true;
    else
        return false;
}
/**********************************规则判断****************************************/
/**************************************************************/
/**************************************************************/
