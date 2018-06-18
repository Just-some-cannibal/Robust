#include "core/ISocketClient.h"

using namespace Robust;

ISocketClient::ISocketClient(int socket) : Socket(socket)
{
}

std::string ISocketClient::ReceiveData()
{
    const int bufferSize = 4096;
    std::string buffer;
    size_t i = 0;

    do
    {

        buffer.resize(bufferSize);
        int size = recv(Socket, (char *)buffer.data() + i * bufferSize, bufferSize, 0);
        if (size < 0)
        {
            Robust::err("Error while receiving");
            throw new std::exception;
            break;
        } else if (size == 0) {
            return "";
        }

        ++i;

    } while (buffer[buffer.size()] != '\0');
    return buffer;
}

void ISocketClient::SendData(std::string data) {
    if (0 > send(Socket, data.data(), data.size(), MSG_NOSIGNAL)) {
        std::string err = strerror(errno);
        Robust::err("Error sending packet: ");
    }
}
