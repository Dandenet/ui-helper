#include <QCoreApplication>
#include "tcp_server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TcpServer server;
    server.start(8888);

    return a.exec();
}