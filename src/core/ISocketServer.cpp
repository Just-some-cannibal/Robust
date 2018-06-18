#include "core/ISocketServer.h"

using namespace Robust;

ISocketServer::ISocketServer(int port) : Port(port),
										 ListenerThread(&ISocketServer::Listener, this)
{
}

void ISocketServer::Join()
{
	if (ListenerThread.joinable())
		ListenerThread.join();
}

void ISocketServer::Detach()
{
	if (ListenerThread.joinable())
		ListenerThread.detach();
}

ISocketServer::~ISocketServer()
{
	close(ServerSock);
}

int ISocketServer::MakeSocket()
{
	int serverSock;
	sockaddr_in echoserver = {0};

	// Creates socket object
	if ((serverSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		Robust::log("Can't open socket");
		throw new std::exception;
	}

	echoserver.sin_family = AF_INET;				// Internet/IP
	echoserver.sin_addr.s_addr = htonl(INADDR_ANY); // Incoming addr
	echoserver.sin_port = htons(Port);				// server port

	// Binds it to specified port
	if (bind(serverSock, (struct sockaddr *)&echoserver, sizeof(echoserver)) < 0)
	{
		Robust::err("Can't bind socket");
		throw new std::exception;
	}

	// Listens to the server sock
	if (listen(serverSock, 5) < 0) {
		Robust::err("Cant listen to socket");
	}

	return serverSock;
}

int ISocketServer::WaitForClient()
{
	sockaddr_in client_addr = {0};
	socklen_t client_len = sizeof(sockaddr_in);
	int client = accept(ServerSock, (struct sockaddr *)&client_addr, &client_len);
	if (client < 0)
	{
		std::string err = strerror(errno);
		Robust::err("Cant accept client: " + err);
		throw new std::exception;
	}
	return client;
}

void ISocketServer::Listener()
{
	ServerSock = MakeSocket();
	for (;;)
	{
		try
		{
			int clientSock = WaitForClient();
			std::thread thread (&ISocketServer::HandleRequest, this, clientSock);
			thread.detach();
		}
		catch (...)
		{
			Robust::log("Error when handling request");
		}
	}
}