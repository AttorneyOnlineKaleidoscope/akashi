#ifndef PACKET_CC_H
#define PACKET_CC_H

#include "network/aopacket.h"

class PacketCC : public AOPacket
{
public:
  PacketCC(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
};
#endif
