#include "socket.h"

/*************************************/
#include <string>
#pragma comment(lib,"ws2_32.lib")
#define RECV_BUFFER_SIZE (32*1024)
/*************************************/


/*************************************/
#include <QTextStream>
#include <stdio.h>
/*************************************/




/**
 * @brief Socket::Init 连接初始化 wsdata等相关配置
 * @return socket初始化成功与否
 */
bool Socket::Init()
{
    WSADATA wsaData;
    WORD wVersionRet;            //调用版本返回值
    //初始化winsock库
    wVersionRet = MAKEWORD(2,2);
    if (WSAStartup(wVersionRet, &wsaData) != 0)//加载套接字库 以及确认socket版本
    {
        // 初始化winsock服务失败，socket错误
        return false;
    }

    // 检测是否支持2.2版本的socket
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        WSACleanup();

        // socket错误
        return false;
    }

    //创建客户端套接字
    m_Client=socket(AF_INET,SOCK_STREAM,0);//流式套接字（SOCK_STREAM），数据报套接字（SOCK_DGRAM），原始套接字（SOCK_RAW）。基于TCP的socket编程是采用的流式套接字。
    //protocol:协议类型，通常是IPPROTO_TCP或IPPROTO_UDP
    if(INVALID_SOCKET == m_Client)
    {
        //释放winsock库
        WSACleanup();
        return false;
    }

    return true;
}

/**
 * @brief Socket::SettingTimeout 时间设置
 * @param timeout
 */
void Socket::SettingTimeout(int timeout)
{
    int milSecond = 0;           //超时时限（毫秒）
    milSecond = timeout * 1000;
    // 设置发送时限
    setsockopt(m_Client, SOL_SOCKET, SO_SNDTIMEO, (char*)&milSecond, sizeof(int));
    // 设置接收时限
    setsockopt(m_Client, SOL_SOCKET, SO_RCVTIMEO, (char*)&milSecond, sizeof(int));
}

/**
 * @brief Socket::Connect 连接
 * @param serverIp
 * @param serverPort
 * @return 成功与否
 */
bool Socket::Connect(char* serverIp, unsigned short serverPort)
{
    SOCKADDR_IN    server_addr;  // 服务端socket地址

    //TCP协议
    //指明远程服务的地址信息（IP地址、端口号等）
    memset(&server_addr ,0,sizeof(SOCKADDR_IN));   //先将保存地址server置零
    server_addr.sin_family=PF_INET; //声明地址格式是TCP/IP格式
    server_addr.sin_port=htons(serverPort); //指明连接服务器的端口号，htons可用于主机序与网络序之间的转化
    server_addr.sin_addr.s_addr=inet_addr(serverIp);//指明连接服务器的IP地址,sin_addr字段也是一个结构体，
    //sin_addr.s_addr用于最终保存IP地址
    //inet_addr inet_addr()用于将 形如的"127.0.0.1"字符串转换为IP地址格式
    //连接指明的服务器上
    int nRet=connect(m_Client,(struct sockaddr *)&server_addr,sizeof(SOCKADDR_IN));//连接后可以用sClient来使用这个连接
    if(SOCKET_ERROR == nRet)
    {
        // 关闭连接
        closesocket(m_Client);
        // 释放winsock
        WSACleanup();
        return false;
    }
    return true;
}

/**
 * @brief Socket::Send
 * @param writeBuf
 * @param len
 * @return
 */
int Socket::Send(CardShare p)
{
    // 向服务端发送数据
    int nRet =send(m_Client, (char*)&p, sizeof(CardShare), 0);
    if (nRet <= 0)
    {
        // 无法向服务器发送数据
        nRet = -1;
        return nRet;
    }
    return 0;
}

/**
 * @brief Socket::FirestRead 发牌
 * @return
 */
CardShare Socket::FirestRead(){
    CardShare cardArr;
    char temp[200];
    memset(temp, 0, sizeof(temp));
    qDebug()<<"recv"<<recv(m_Client, temp, 101, 0)<<endl;;
    memcpy(&cardArr, temp, sizeof(CardShare));
    return cardArr;
}

/**
 * @brief Socket::Read
 * @param recData
 * @return
 */
int Socket::Read(string &recData)
{
    char readBuf[RECV_BUFFER_SIZE]={0};
    memset(readBuf,'\0',sizeof(readBuf));
    recData[0]='1';
    QTextStream cout(stdout, QIODevice::WriteOnly);//  声明cout
    cout<<"First recv"<<recv(m_Client, readBuf, RECV_BUFFER_SIZE, 0)<<endl;
    cout<<"recv"<<readBuf<<endl;
    return 0;
//    // 接收服务端返回的数据
//    char readBuf[RECV_BUFFER_SIZE] = {0};
//    recData.clear();

//    int nRet = 	recv(m_Client, readBuf, RECV_BUFFER_SIZE, 0);// 返回收到数据的大小
//    cout<<readBuf<<"```````````````````"<<endl;
//    if (nRet <= 0)
//    {
//        // 服务器未返回数据
//        nRet = -1;
//        return nRet;
//    }
//    recData.append(readBuf,nRet);
}

/**
 * @brief Socket::Close
 */
void Socket::Close()
{
    if( m_Client != INVALID_SOCKET )
    {
        m_Client = INVALID_SOCKET;
        // 关闭连接
        closesocket( m_Client );
        // 释放winsock
        WSACleanup();
    }
}
