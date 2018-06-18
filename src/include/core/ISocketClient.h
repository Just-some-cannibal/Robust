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
class ISocketClient
{
protected:
    std::string ReceiveData();
    void SendData(std::string);
    int Socket;
public:
    // Takes in socket to communicate with
    ISocketClient(int);
    virtual void Run() {}
};
} // namespace Robust