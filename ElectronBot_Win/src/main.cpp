#include"../electron_controller.h"
#include "../TCPServer.h"
#include"../MouseHandler.h"
#include"../CaptureDlib.h"
#include <iostream>
#include <thread>
#include <windows.h>
#include <stdio.h>

using namespace std;

ElectronController* controller = new ElectronController();

void startTCP(ElectronController* controller)
{
    TCP_Server tcpServer;
    tcpServer.Start_Server(controller);
}
MouseHandler handler;
void startMouseHandler(ElectronController* controller)
{
    handler.Start_MouseHandler(controller);
}


bool Ctrlhandler(DWORD fdwctrltype, ElectronController* controller)
{
    switch (fdwctrltype)
    {
        // handle the ctrl-c signal.
    case CTRL_C_EVENT:
        printf("ctrl-c event\n\n");
        return(true);
        // ctrl-close: confirm that the user wants to exit.
    case CTRL_CLOSE_EVENT:

        //控制台结束时 要做的事情
        printf("ctrl-close event\n\n");
        Sleep(200);
        return(false);
        // pass other signals to the next handler.
    case CTRL_BREAK_EVENT:
        Sleep(200);
        printf("ctrl-break event\n\n");
        return false;
    case CTRL_LOGOFF_EVENT:
        Sleep(200);
        printf("ctrl-logoff event\n\n");
        return false;
    case CTRL_SHUTDOWN_EVENT:
        controller->Disconnect();
        printf("Robot Disconnected.\n");
        Sleep(200);
        printf("ctrl-shutdown event\n\n");
        return false;
    default:
        return false;
    }
}
int main()
{
    int mode = 0;// 0:直播模式 1：自动运行模式
    
    //屏幕整体尺寸
    HDC hdc = GetDC(NULL);
    int cx = GetDeviceCaps(hdc, DESKTOPHORZRES);
    int cy = GetDeviceCaps(hdc, DESKTOPVERTRES);
    ReleaseDC(NULL, hdc);

    if (controller->Connect())
        printf("Robot connected!\n");
    else
    {
        printf("Connect failed!\n");
        getchar();
        return 0;
    }

    if (mode == 0) {

        CaptureDlib cLib;
        cLib.Init_CaptureDlib(controller);

    }else if (mode == 1) {
        handler.Init_MouseHandler();
        //写正常代码
        thread tcpThread(startTCP, controller);
        thread mouseThread(startMouseHandler, controller);
        controller->Init(cx, cy);
        //controller->Disconnect();
        //printf("Robot Disconnected.\n");
    }
    getchar();
    return 0;
}

