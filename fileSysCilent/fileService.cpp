#include "fileService.h"
#include "uvClient.h"
#include "wsClient.h"

FSByTcp::FSByTcp(std::string serverIp, int serverPort)
{
	this->serverIp = serverIp;
	this->serverPort = serverPort;
}

FSByTcp::~FSByTcp()
{
	serviceDestroy();
}

void FSByTcp::serviceInit()
{
	this->uc = new uvClient();
	return;
}

void FSByTcp::serviceDestroy()
{
	if (uc)
		delete uc;
}

void FSByTcp::connectService()
{
	serviceInit();
	uc->connectIpv4(this->serverIp.c_str(), this->serverPort);
	return ;
}

void FSByTcp::setReadCallBack(int(*readCallBack)(char *, int))
{
	this->uc->setReadCallBack(readCallBack);
}

int FSByTcp::sendData(const char * buf, int len, int flags)
{
	return uc->sendData((void*)buf, len);
}

FSByWebSocket::FSByWebSocket(std::string serverIp, int serverPort)
{
	this->serverIp = serverIp;
	this->serverPort = serverPort;
}

FSByWebSocket::~FSByWebSocket()
{
	serviceDestroy();
}

void FSByWebSocket::serviceInit()
{
	this->wc = new wsClient();
	return;
}

void FSByWebSocket::serviceDestroy()
{
	if (wc)
		delete wc;
}

void FSByWebSocket::connectService()
{
	serviceInit();
	wc->connectIpv4(this->serverIp.c_str(), this->serverPort);
	return;
}

void FSByWebSocket::setReadCallBack(int(*readCallBack)(char *, int))
{
	this->wc->setReadCallBack(readCallBack);
}

int FSByWebSocket::sendData(const char * buf, int len, int flags)
{
	return 0;
}

void * initService(void * handle)
{
	fileService* fs= (fileService*)handle;
	return fs;
}

void connectService(void * handle)
{
	fileService* fs = (fileService*)handle;
	fs->connectService();
}

void setReadCallBack(void * handle, int(*readCallBack)(char *, int))
{
	fileService* fs = (fileService*)handle;
	fs->setReadCallBack(readCallBack);
}

int sendData(void * handle, const char * buf, int len)
{
	fileService* fs = (fileService*)handle;
	return fs->sendData(buf, len);
}

void deleteService(void * handle)
{
	delete (fileService*)handle;
}
