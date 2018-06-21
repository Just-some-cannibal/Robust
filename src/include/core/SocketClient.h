#pragma once

#include <string>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

#include "util/logger.h"

namespace Robust
{
class SocketClient
{
  protected:
    // Returns a string from the data returned from the socket
    // Returns a zero sized string if no data could be received
    std::string ReceiveData();

    // Takes in a string to be sent to client
    void SendData(std::string);

    // FD for the client socket
    int Socket;

  public:
    // Takes in client FD for a higher level interface to the socket
    SocketClient(int);
    virtual ~SocketClient();
};
} // namespace Robust