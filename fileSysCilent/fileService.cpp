#include "fileService.h"

FSByTcp::FSByTcp()
{
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

FSByHttp::FSByHttp()
{
}

FSByHttp::~FSByHttp()
{
}

int FSByHttp::connectService()
{
	return 0;
}

int FSByHttp::recvData(char ** buf, int * len, int flags)
{
	return 0;
}

int FSByHttp::sendData(const char * buf, int len, int flags)
{
	return 0;
}

int FSByHttp::serviceInit()
{
	return 0;
}

void FSByHttp::serviceDestroy()
{
}

FSByWebSocket::FSByWebSocket()
{
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
