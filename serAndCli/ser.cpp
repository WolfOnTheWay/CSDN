# include<iostream>
# include<WinSock2.h>
# include<WS2tcpip.h>
# pragma comment (lib,"ws2_32.lib")
# include<assert.h>
using namespace std;

int main()
{
	//����һ���ṹ�� ���ڴ洢ws2_32.dll�������Ϣ
	WSADATA  wsaData;
	//��ʼ��DLL�⣬��ָ��Winsock�淶�İ汾
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sockaddr_in sockAddr;
	//�����׽���
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
		cout << "һ���������Ѿ���������" << endl;
	}
	const char *str = "heart ";
	send(cliSock, str, strlen(str) + sizeof(char), NULL);


	closesocket(servSock);
	closesocket(cliSock);

	WSACleanup();


	system("pause");
	return 0;
}