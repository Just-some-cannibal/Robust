#include "core/ISocketServer.h"
#include "core/ISocketClient.h"
#include <signal.h>

using namespace Robust;

class TestSocket : public ISocketClient
{
  public:
    TestSocket(int socket) : ISocketClient(socket)
    {
    }

    void Run()
    {
        std::string received;
        do
        {
            try
            {
                received = ReceiveData();
                Robust::log("Received: " + std::to_string(received.size()));
                SendData("HTTP/1.1 200 OK\nContent-Length: 11\n\nHello World");
            }
            catch (...)
            {
                Robust::err("An error has occured. Closing socket");
            }
        } while (received.size() > 0);
        close(Socket);
    }
};

class TestSocketServer : public ISocketServer
{
  public:
    TestSocketServer() : ISocketServer(20000)
    {
    }

  private:
    void HandleRequest(int port)
    {
        TestSocket socket(port);
        socket.Run();
    }
};

int main()
{
    TestSocketServer server;
    server.Join();
}