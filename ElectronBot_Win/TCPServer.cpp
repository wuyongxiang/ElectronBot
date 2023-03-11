#define _WINSOCK_DEPRECATED_NO_WARNINGS			//��ֹ����
#include <iostream>
#include <WinSock2.h>
#include "TCPServer.h"
using namespace std;

#pragma comment(lib,"ws2_32.lib")

int TCP_Server::Start_Server(ElectronController* controller)
{
	clientSocket = INVALID_SOCKET;
	/*��ʼ��������Ϣ*/
	WORD sockVersion = MAKEWORD(2, 2);//����2.2�汾��socket
	WSADATA wsaData;				  //WSA(Windows Sockets Asynchronous)�첽�׽���

	//��ָ���汾��socket���Ӧ�ó����
	if (WSAStartup(sockVersion, &wsaData) != 0)	//����Ϊ0���ʾ��ʼ���ɹ�
		return 0;

	/*����������Socket*/
	//AF_INET��ʹ��IPV4ͨ�ţ�SOCK_STREAM��ʹ����ʽ�׽��֣�IPPROTO_TCP������TCPЭ��

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)			//�������ʧ�ܣ����������
	{
		cout << "socket Error" << WSAGetLastError() <<endl;
		WSACleanup();			//��ֹWindows Sockets DLL��ʹ�ã�������WSAStartup()����ʹ��
		return 0;
	}
	//����������Socket�׽��ֳɹ���

	/*sockaddr_in��һ���ṹ�壬��Ҫָ�� Э���� + IP��ַ + �˿ں�*/
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;				//ָ��Э���壬AF_INET<->IPV4��AF_INET6<->IPV6
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;	//ָ��IP��ַ
	serverAddr.sin_port = htons(3008);				//ָ���˿ں�

	//Socket�󶨵�ַ���ڶ�������ע����Ҫʹ��ǿ��ת��
	if (::bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		cout << "Bind Error" << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}

	//���������ͻ���������źţ����������5���ͻ���
	if (listen(serverSocket, 5) == SOCKET_ERROR)//�������ʧ��
	{
		cout << "Listen Error" << endl;
		closesocket(serverSocket);				//�ر�Socket�׽���
		WSACleanup();
		return 0;
	}
	cout << "listening" << endl;
	//��ʼ���ϴ�������ͻ�������
	while (true)
	{
		
		sockaddr_in clientAddr;					//�ͻ��˵ĵ�ַ�ṹ
		int iAddrLength = sizeof(clientAddr);	//����ýṹ�ĳ���
		cout << "loading" << endl;
		//���տͻ��˵��������󡣵�һ������Ϊ�����Socket,�ڶ��������������մӿͻ��˴����ĵ�ַ������������Ϊ��ַ�ṹ�ĳ���
		clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &iAddrLength);//acceptΪ��������

		if (clientSocket == INVALID_SOCKET)		//�������ʧ��
		{
			cout << "Accept Error !" << WSAGetLastError() << endl;
			closesocket(serverSocket);
			WSACleanup();
			return 0;
		}
		//inet_ntoa�������ַת��Ϊ�ַ����
		const char* ip = inet_ntoa(clientAddr.sin_addr);
		
		cout << ip << "���ӳɹ�" << endl;
		//��ʼ���Ͻ��ոÿͻ�������
		char buffFromClient[1024];			//���ڽ��տͻ��˴���������
		while (true)
		{
			memset(buffFromClient, 0, sizeof(buffFromClient));
			//recvҲΪ����������ֻ�пͻ��˷������ݹ����󣬳���Ż����¼�����
			int iLenOfRecvData = recv(clientSocket, buffFromClient, sizeof(buffFromClient), 0);

			if (iLenOfRecvData > 0)		//������յ����ݲ�Ϊ��
			{
				controller->MsgFromTCP(buffFromClient, clientSocket);
			}
			else
			{
				cout << ip << "�������Ͽ����޽���..." << endl;
				break;
			}
		}
		closesocket(clientSocket);//�ر���ÿͻ��˵��׽���
	}
	closesocket(serverSocket);//�رշ������׽���
	WSACleanup();
}
