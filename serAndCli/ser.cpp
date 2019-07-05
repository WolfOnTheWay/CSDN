# include<iostream>
# include<WinSock2.h>
# include<WS2tcpip.h>
# pragma comment (lib,"ws2_32.lib")
# include<assert.h>
using namespace std;

int main()
{
	//定义一个结构体 用于存储ws2_32.dll的相关信息
	WSADATA  wsaData;
	//初始化DLL库，以指明Winsock规范的版本
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sockaddr_in sockAddr;
	//创建套接字
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	memset(&sockAddr, 0, sizeof(sockAddr));

	sockAddr.sin_family = PF_INET;
	int inetPtonRes = InetPton(AF_INET,"127.0.0.1", &sockAddr.sin_addr.s_addr );
	assert(inetPtonRes != 0);
	sockAddr.sin_port = htons(6000);

	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	listen(servSock, 20);

	SOCKADDR cliAddr;
	int cliAddrSize = sizeof(SOCKADDR);
	
	SOCKET cliSock = accept(servSock, (SOCKADDR*)&cliAddr, &cliAddrSize);
	if (cliSock != 0)
	{
		cout << "一个服务器已经连接上了" << endl;
	}
	const char *str = "heart ";
	send(cliSock, str, strlen(str) + sizeof(char), NULL);


	closesocket(servSock);
	closesocket(cliSock);

	WSACleanup();


	system("pause");
	return 0;
}