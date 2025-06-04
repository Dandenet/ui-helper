
#include "packet.h"

quint16 Packet::crc16(const QByteArray &data) {
  quint16 crc = 0xFFFF;
  for (auto byte : data) {
    crc ^= static_cast<quint8>(byte) << 8;
    for (int i = 0; i < 8; ++i)
      crc = (crc & 0x8000) ? (crc << 1) ^ 0x1021 : crc << 1;
  }
  return crc;
}

QByteArray Packet::createPacket(quint8 id, quint8 type, quint8 module,
                                const QByteArray &payload) {
  QByteArray packet;
  packet.append(StartByte1);
  packet.append(StartByte2);

  QByteArray body;
  body.append(id);
  body.append(type);
  body.append(module);
  body.append(payload);

  quint32 length = body.size() + 2; // +2 байта на CRC
  packet.append(reinterpret_cast<const char *>(&length), sizeof(length));
  packet.append(body);

  quint16 crc = crc16(body);
  packet.append(reinterpret_cast<const char *>(&crc), sizeof(crc));

  return packet;
}

bool Packet::parsePacket(const QByteArray &data, quint8 &id, quint8 &type,
                         quint8 &module, QByteArray &payload) {
  if (data.size() < 9)
    return false;
  if (data[0] != StartByte1 || data[1] != StartByte2)
    return false;

  quint32 length;
  memcpy(&length, data.constData() + 2, sizeof(length));
  if (data.size() < static_cast<int>(length + 6))
    return false;

  id = static_cast<quint8>(data[6]);
  type = static_cast<quint8>(data[7]);
  module = static_cast<quint8>(data[8]);

  int payloadSize = length - 5; // ID(1) + Type(1) + Module(1) + CRC(2)
  payload = data.mid(9, payloadSize);

  quint16 receivedCrc;
  memcpy(&receivedCrc, data.constData() + 9 + payloadSize, sizeof(receivedCrc));

  QByteArray body = data.mid(6, length - 2); // все до CRC
  quint16 computedCrc = crc16(body);

  return receivedCrc == computedCrc;
}
