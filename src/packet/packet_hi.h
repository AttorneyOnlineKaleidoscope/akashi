#ifndef PACKET_HI_H
#define PACKET_HI_H

#include "network/aopacket.h"

class PacketHI : public AOPacket
{
public:
  PacketHI(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual void handlePacket(AreaData *area, AOClient &client) const;

private:
  QString header;
};
#endif
