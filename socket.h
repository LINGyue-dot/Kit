#ifndef SOCKET_H
#define SOCKET_H

#include <WinSock2.h>
#include <string>
#include"Struct.h"
#include <QDebug>


using namespace std;

class Socket
{
public:
    Socket():m_Client(INVALID_SOCKET){} //将socket设置成无效套接字
    bool Init();
    void SettingTimeout(int timeout);
    bool Connect(char* host, unsigned short port);
    int Send(CardShare p);
    CardShare FirestRead();
    int Read(std::string &recData);
    void Close();

private:
    SOCKET m_Client;
};

#endif // SOCKET_H
