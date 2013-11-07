#include <tbsys.h>
#include <tbnet.h>
#include "cutil/error_code.h"
#include "mr_base_server.h"

using namespace tbnet;
using namespace tbsys;

MrBaseServer::MrBaseServer()
{
}

MrBaseServer::~MrBaseServer()
{
}


void MrBaseServer::start()
{
  int ret = CU_SUCCESS;
  char spec[32];

  streamer_.setPacketFactory(packet_factory_);

  snprintf(spec, 32, "tcp::%d", port_);
  spec[31] = '\0';
  
  if (NULL == transport_.listen(spec, &streamer_, this))
  {
    ret = CU_LISTEN_ERROR;
  }
  else
  {
    TBSYS_LOG(INFO, "start listening on port %d", port_);
    transport_.start();
    transport_.wait();
  }
}


void MrBaseServer::stop()
{
  transport_.stop();
  transport_.wait();
}


void MrBaseServer::set_packet_factory(tbnet::IPacketFactory *factory)
{
  packet_factory_ = factory;
}

int MrBaseServer::set_dev_name(const char *dev)
{
  int ret = CU_INVALID_ARGUMENT;
  if (NULL != dev)
  {
    strncpy(dev_name_, dev, DEV_NAME_LENGTH);
    ret = CU_SUCCESS;
  }
  dev_name_[DEV_NAME_LENGTH - 1] = '\0';
  TBSYS_LOG(INFO, "set dev=%s", dev_name_);
  return ret;
}


int MrBaseServer::set_listen_port(const int port)
{
  int ret = CU_INVALID_ARGUMENT;
  if (port > 0)
  {
    port_ = port;
    TBSYS_LOG(INFO, "set port=%d", port);
  }
  else
  {
    TBSYS_LOG(WARN, "set invalid port=%d", port);
  }
  return ret;
}


tbnet::IPacketHandler::HPRetCode MrBaseServer::handlePacket(tbnet::Connection *connection, tbnet::Packet *packet)
{
  tbnet::IPacketHandler::HPRetCode rc = tbnet::IPacketHandler::FREE_CHANNEL;
  if (!packet->isRegularPacket())
  {
    TBSYS_LOG(WARN, "control packet, packet code: %d", ((tbnet::ControlPacket*)packet)->getCommand());
  } 
  else
  {
  }

  return rc;
}
