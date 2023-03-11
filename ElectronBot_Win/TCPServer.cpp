#define _WINSOCK_DEPRECATED_NO_WARNINGS			//防止报错
#include <iostream>
#include <WinSock2.h>
#include "TCPServer.h"
using namespace std;

#pragma comment(lib,"ws2_32.lib")

int TCP_Server::Start_Server(ElectronController* controller)
{
	clientSocket = INVALID_SOCKET;
	/*初始化启动信息*/
	WORD sockVersion = MAKEWORD(2, 2);//调用2.2版本的socket
	WSADATA wsaData;				  //WSA(Windows Sockets Asynchronous)异步套接字

	//将指定版本的socket与该应用程序绑定
	if (WSAStartup(sockVersion, &wsaData) != 0)	//返回为0则表示初始化成功
		return 0;

	/*创建服务器Socket*/
	//AF_INET，使用IPV4通信；SOCK_STREAM，使用流式套接字；IPPROTO_TCP，采用TCP协议

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)			//如果创建失败，则输出错误
	{
		cout << "socket Error" << WSAGetLastError() <<endl;
		WSACleanup();			//中止Windows Sockets DLL的使用；与上面WSAStartup()配套使用
		return 0;
	}
	//创建服务器Socket套接字成功后

	/*sockaddr_in是一个结构体，需要指定 协议族 + IP地址 + 端口号*/
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;				//指定协议族，AF_INET<->IPV4；AF_INET6<->IPV6
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;	//指定IP地址
	serverAddr.sin_port = htons(3008);				//指定端口号

	//Socket绑定地址，第二个参数注意需要使用强制转换
	if (::bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		cout << "Bind Error" << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}

	//建立监听客户端请求的信号，设置最多有5个客户端
	if (listen(serverSocket, 5) == SOCKET_ERROR)//如果建立失败
	{
		cout << "Listen Error" << endl;
		closesocket(serverSocket);				//关闭Socket套接字
		WSACleanup();
		return 0;
	}
	cout << "listening" << endl;
	//开始不断处理各个客户端请求
	while (true)
	{
		
		sockaddr_in clientAddr;					//客户端的地址结构
		int iAddrLength = sizeof(clientAddr);	//求出该结构的长度
		cout << "loading" << endl;
		//接收客户端的连接请求。第一个参数为服务端Socket,第二个参数用来接收从客户端传来的地址，第三个参数为地址结构的长度
		clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &iAddrLength);//accept为阻塞函数

		if (clientSocket == INVALID_SOCKET)		//如果接收失败
		{
			cout << "Accept Error !" << WSAGetLastError() << endl;
			closesocket(serverSocket);
			WSACleanup();
			return 0;
		}
		//inet_ntoa将网络地址转换为字符输出
		const char* ip = inet_ntoa(clientAddr.sin_addr);
		
		cout << ip << "连接成功" << endl;
		//开始不断接收该客户端数据
		char buffFromClient[1024];			//用于接收客户端传来的数据
		while (true)
		{
			memset(buffFromClient, 0, sizeof(buffFromClient));
			//recv也为阻塞函数，只有客户端发送数据过来后，程序才会往下继续走
			int iLenOfRecvData = recv(clientSocket, buffFromClient, sizeof(buffFromClient), 0);

			if (iLenOfRecvData > 0)		//如果接收的数据不为空
			{
				controller->MsgFromTCP(buffFromClient, clientSocket);
			}
			else
			{
				cout << ip << "服务器断开，无接收..." << endl;
				break;
			}
		}
		closesocket(clientSocket);//关闭与该客户端的套接字
	}
	closesocket(serverSocket);//关闭服务器套接字
	WSACleanup();
}
