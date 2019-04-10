#pragma once
#include "uvTask.h"

typedef int(*readCallBack) (char* buf, int len);
typedef int(*writeCallBack) (char* buf, int len);

class uvClient
{
private:
	readCallBack rCallBack;
	writeCallBack wCallBack;

private:
	uv_loop_t* loop;
	uv_tcp_t tcpConn;
	uv_connect_t connectReq;
	uv_thread_t connectThr;

	const char* ip;
	int port;

	static void on_thread_cb(void*);
	static void on_connect_cb(uv_connect_t* req, int status);

public:
	uvClient();
	~uvClient();

	void setReadCallBack(readCallBack rCallBack);
	void setWriteCallBack(writeCallBack wCallBack);

	readCallBack getReadCallBack();
	writeCallBack getWriteCallBack();

	void connectIpv4(const char* ip, int port);
};

