#ifndef MR_BASE_SERVER_H_
#define MR_BASE_SERVER_H_
#include <tbnet.h>

class MrBaseServer : public tbnet::IServerAdapter
{
  public:
    MrBaseServer();
    ~MrBaseServer();
    void start();
    void stop();
    void set_packet_factory(tbnet::IPacketFactory *factory);
    int set_dev_name(const char *dev);
    int set_listen_port(const int port);
    tbnet::IPacketHandler::HPRetCode handlePacket(tbnet::Connection *connection, tbnet::Packet *packet);
  private:
    const static int DEV_NAME_LENGTH = 32;
  private:
    tbnet::Transport transport_;
    tbnet::DefaultPacketStreamer streamer_;
    tbnet::IPacketFactory *packet_factory_;
    char dev_name_[DEV_NAME_LENGTH];
    int port_;
};

#endif
