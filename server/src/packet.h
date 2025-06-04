#pragma once
#include <QByteArray>
#include <QtGlobal>

class Packet {
public:
  static constexpr char StartByte1 = 'u';
  static constexpr char StartByte2 = 'h';

  static QByteArray createPacket(quint8 id, quint8 type, quint8 module,
                                 const QByteArray &payload);
  static bool parsePacket(const QByteArray &data, quint8 &id, quint8 &type,
                          quint8 &module, QByteArray &payload);

private:
  static quint16 crc16(const QByteArray &data);
};