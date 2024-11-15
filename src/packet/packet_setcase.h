#ifndef PACKET_SETCASE_H
#define PACKET_SETCASE_H

#include "network/aopacket.h"

class PacketSetcase : public AOPacket
{
public:
  PacketSetcase(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
};
#endif
