# include<iostream>
# include<WinSock2.h>
# include<WS2tcpip.h>
# pragma comment (lib,"ws2_32.lib")
# include<assert.h>
using namespace std;

int main()
{
	//
	WSADATA  wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sockaddr_in sockAddr;
	//创建套接字
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	memset(&sockAddr, 0, sizeof(sockAddr));

	sockAddr.sin_family = PF_INET;
	int inetPtonRes = InetPton(AF_INET, "127.0.0.1", &sockAddr.sin_addr.s_addr);
	assert(inetPtonRes != 0);
	sockAddr.sin_port = htons(6000);

	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	char buffer[50] = { 0 };
    cout << "buffer" << buffer << endl;
	recv(sock, buffer, 50, NULL);
	
	cout << "来自服务器的：" << buffer << endl;

	closesocket(sock);
	

	WSACleanup();

	system("pause");
	return 0;
}