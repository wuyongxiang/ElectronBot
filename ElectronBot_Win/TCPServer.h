#include "electron_controller.h"
#ifndef ELECTRONBOTSDK_TCPSERVER_H
#define ELECTRONBOTSDK_TCPSERVER_H

class __declspec(dllexport) TCP_Server
{
public:
    TCP_Server()
    {

    }

    ~TCP_Server()
    {

    }

    SOCKET clientSocket;	//��ʼ��һ���ͻ���socket
    int Start_Server(ElectronController* controller);


private:


};


#endif