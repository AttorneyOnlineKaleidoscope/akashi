#ifndef PACKET_PW_H
#define PACKET_PW_H

#include "network/aopacket.h"

class PacketPW : public AOPacket
{
public:
  PacketPW(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;
};
#endif
