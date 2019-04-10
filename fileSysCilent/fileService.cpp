#include "fileService.h"

FSByTcp::FSByTcp(std::string serverIp, int serverPort)
{
	this->serverIp = serverIp;
	this->serverPort = serverPort;
}

FSByTcp::~FSByTcp()
{
}

int FSByTcp::connectService()
{
	return 0;
}

int FSByTcp::recvData(char ** buf, int * len, int flags)
{
	return 0;
}

int FSByTcp::sendData(const char * buf, int len, int flags)
{
	return 0;
}

int FSByTcp::serviceInit()
{
	return 0;
}

void FSByTcp::serviceDestroy()
{
}

FSByWebSocket::FSByWebSocket(std::string serverIp, int serverPort)
{
	this->serverIp = serverIp;
	this->serverPort = serverPort;
}

FSByWebSocket::~FSByWebSocket()
{
}

int FSByWebSocket::startService()
{
	return 0;
}

int FSByWebSocket::recvData(char ** buf, int * len, int flags)
{
	return 0;
}

int FSByWebSocket::sendData(const char * buf, int len, int flags)
{
	return 0;
}

int FSByWebSocket::serviceInit()
{
	return 0;
}

void FSByWebSocket::serviceDestroy()
{
}
