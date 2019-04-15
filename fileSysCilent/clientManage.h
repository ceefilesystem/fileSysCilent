#pragma once

typedef enum ProtocolType
{
	TCP = 0,
	WEBSOCKET = 1
}ProtocolType;

void* initService(ProtocolType type, const char* ip, int port);
void connectService(void* handle);
void setReadCallBack(void* handle, int(*readCallBack) (char*, int));
int sendData(void* handle, const char* buf, int len);
void deleteService(void* handle);