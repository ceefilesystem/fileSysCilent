#include <iostream>
#include <Windows.h>
#include "clientManage.h"

int readcallback(char* buf, int len)
{
	printf("len: %d, buf:%s \n", len, buf);
	return len;
}

int main()
{
	void* handle = initService(ProtocolType::TCP, "127.0.0.1", 9998);
	connectService(handle);
	setReadCallBack(handle, readcallback);

	while (true)
	{
		try
		{
			sendData(handle, "1234", 4);
			sendData(handle, "3333", 5);
			Sleep(1000);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			break;
		}
	}

	deleteService(handle);
	system("pause");
	return 0;
}