#include "core/ISocketServer.h"
#include "core/SocketClient.h"
#include <signal.h>

using namespace Robust;

class TestSocketServer : public ISocketServer
{
  public:
    TestSocketServer() : ISocketServer(20000)
    {
    }

  private:
    void HandleRequest(int port)
    {
        SocketClient socket(port);
        std::string received;
        do
        {
            try
            {
                received = socket.ReceiveData();
                Robust::log("Received: " + std::to_string(received.size()));
                socket.SendData("HTTP/1.1 200 OK\nContent-Length: 11\n\nHello World");
            }
            catch (...)
            {
                Robust::err("An error has occured. Closing socket");
            }
        } while (received.size() > 0);
    }
};

int main()
{
    TestSocketServer server;
    server.Join();
}