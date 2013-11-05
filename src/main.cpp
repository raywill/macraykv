#include <tbsys.h>
#include "mr_base_server.h"

int main()
{
  MrBaseServer base_server;

  TBSYS_LOGGER.setLogLevel("info");
  TBSYS_LOGGER.setMaxFileSize(1 * 1024L * 1024L);
  
  base_server.set_listen_port(19851);
  base_server.set_dev_name("lo");
  base_server.start();
  TBSYS_LOG(INFO, "server start");
  while(true)
  {
    usleep(1000);
  }
}
