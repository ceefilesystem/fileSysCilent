#pragma once

typedef int(*readCallBack) (char* buf, int len);

class wsClient
{
private:
	readCallBack rCallBack;
	readCallBack getReadCallBack();

public:
	wsClient();
	~wsClient();

	void setReadCallBack(readCallBack rCallBack);

	void connectIpv4(const char* ip, int port);
	int sendData(void* in, int len);
};

