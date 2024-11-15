#include "packet/packet_ch.h"
#include "akashiutils.h"
#include "server.h"

#include <QDebug>

PacketCH::PacketCH(QStringList &contents)
    : AOPacket(contents)
{}

PacketInfo PacketCH::getPacketInfo() const
{
  PacketInfo info{.acl_permission = ACLRole::Permission::NONE, .min_args = 1, .header = "CH"};
  return info;
}

void PacketCH::handlePacket(AreaData *area, AOClient &client) const
{
  Q_UNUSED(area)
  // Why does this packet exist
  // At least Crystal made it useful
  // It is now used for ping measurement
  client.sendPacket("CHECK");
}
