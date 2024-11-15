#include "packet/packet_pw.h"
#include "server.h"

#include <QDebug>

PacketPW::PacketPW(QStringList &contents)
    : AOPacket(contents)
{}

PacketInfo PacketPW::getPacketInfo() const
{
  PacketInfo info{.acl_permission = ACLRole::Permission::NONE, .min_args = 1, .header = "PW"};
  return info;
}

void PacketPW::handlePacket(AreaData *area, AOClient &client) const
{
  Q_UNUSED(area)

  client.m_password = m_content[0];
}
