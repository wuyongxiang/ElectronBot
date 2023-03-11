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

    SOCKET clientSocket;	//初始化一个客户端socket
    int Start_Server(ElectronController* controller);


private:


};


#endif