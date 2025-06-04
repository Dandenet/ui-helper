#pragma once
#include "packet.h"
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class TcpServer : public QTcpServer {
  Q_OBJECT
public:
  TcpServer(QObject *parent = nullptr) {
    connect(this, &QTcpServer::newConnection, this,
            &TcpServer::handleNewConnection);
  }

  void start(quint16 port) {
    if (!listen(QHostAddress::Any, port))
      qWarning() << "Server failed to start!";
    else
      qDebug() << "Server started on port" << port;
  }

private slots:
  void handleNewConnection() {
    auto socket = nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, [socket]() {
      QByteArray data = socket->readAll();
      quint8 id, type, module;
      QByteArray payload;

      if (Packet::parsePacket(data, id, type, module, payload)) {
        qDebug() << "Received packet:"
                 << "ID:" << id << "Type:" << type << "Module:" << module
                 << "Payload:" << payload;
        // Пример ответа
        QByteArray response = Packet::createPacket(0x02, 0x01, module, "OK");
        socket->write(response);
      } else {
        qDebug() << "Invalid packet received";
      }
    });
  }
};