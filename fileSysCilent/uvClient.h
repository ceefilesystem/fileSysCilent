#pragma once
#include "uvTask.h"

typedef int(*readCallBack) (char* buf, int len);

class uvClient
{
	friend static void on_thread_cb(void*);
	friend static void on_connect_cb(uv_connect_t*, int);
	friend static void on_read_cb(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf);

private:
	readCallBack rCallBack;
	readCallBack getReadCallBack();

private:
	uv_loop_t* loop;
	uv_tcp_t tcpConn;
	uv_connect_t connectReq;
	uv_thread_t connectThr;

	const char* ip;
	int port;

public:
	uvClient();
	~uvClient();

	void setReadCallBack(readCallBack rCallBack);

	void connectIpv4(const char* ip, int port);
	int sendData(void* in, int len);
};

