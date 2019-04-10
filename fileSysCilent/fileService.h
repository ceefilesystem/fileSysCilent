#pragma once
#include <string>

class fileService
{
	virtual int serviceInit() = 0;
	virtual void serviceDestroy() = 0;

	virtual int connectService() = 0;
	virtual int recvData(char **buf,  int *len, int flags) = 0;
	virtual int sendData(const char* buf, int len, int flags) = 0;
};

class uvClient;
class wsClient;

//////////////////////////tcp //////////////////////////
class FSByTcp : public fileService
{
private:
	std::string serverIp;
	int serverPort;

	uvClient* uc;

public:
	FSByTcp(std::string serverIp, int serverPort);
	virtual ~FSByTcp();

	virtual int connectService();
	virtual int recvData(char **buf, int *len, int flags);
	virtual int sendData(const char* buf, int len, int flags);
protected:
	virtual int serviceInit();
	virtual void serviceDestroy();
};

//////////////////////////websocket //////////////////////////
class FSByWebSocket : public fileService
{
private:
	std::string serverIp;
	int serverPort;

	wsClient* wc;

public:
	FSByWebSocket(std::string serverIp, int serverPort);
	virtual ~FSByWebSocket();

	virtual int startService();
	virtual int recvData(char **buf, int *len, int flags);
	virtual int sendData(const char* buf, int len, int flags);
protected:
	virtual int serviceInit();
	virtual void serviceDestroy();
};


