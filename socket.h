#ifndef SOCKET_H
#define SOCKET_H

#include <WinSock2.h>
#include <string>

using namespace std;

class Socket
{
public:
    // 发牌结构体
    struct CardShare {
        int cardArr[20]; // 发配牌数组
        int number; // 玩家编号
    };
    Socket():m_Client(INVALID_SOCKET){} //将socket设置成无效套接字
    bool Init();
    void SettingTimeout(int timeout);
    bool Connect(char* host, unsigned short port);
    int Send(Socket::CardShare p);
    CardShare FirestRead();
    int Read(std::string &recData);
    void Close();

private:
    SOCKET m_Client;
};

#endif // SOCKET_H
