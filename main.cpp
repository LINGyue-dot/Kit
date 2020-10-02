#include "widget.h"
#include "socket.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    Socket clientSocket;
    clientSocket.ClientSocket();
    return a.exec();
}
