#pragma once
#include <string>

class fileService
{
	virtual void serviceInit() = 0;
	virtual void serviceDestroy() = 0;

	virtual void connectService() = 0;
	virtual void setReadCallBack(int(*readCallBack) (char*, int)) = 0;
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

	virtual void connectService();
	//处理接受到的数据
	virtual void setReadCallBack(int(*readCallBack) (char*, int));
	virtual int sendData(const char* buf, int len, int flags = 0);
protected:
	virtual void serviceInit();
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

	virtual void connectService();
	//处理接受到的数据
	virtual void setReadCallBack(int(*readCallBack) (char*, int));
	virtual int sendData(const char* buf, int len, int flags = 0);
protected:
	virtual void serviceInit();
	virtual void serviceDestroy();
};


