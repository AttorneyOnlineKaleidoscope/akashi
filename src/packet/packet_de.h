#ifndef PACKET_DE_H
#define PACKET_DE_H

#include "network/aopacket.h"

class PacketDE : public AOPacket
{
public:
  PacketDE(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
};
#endif
