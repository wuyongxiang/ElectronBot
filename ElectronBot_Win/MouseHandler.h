#ifndef ELECTRONBOTSDK_MOUSEHANDLER_H
#define ELECTRONBOTSDK_MOUSEHANDLER_H
#include "electron_controller.h"
#include <windows.h>                			//GetAsyncKeyState����ͷ�ļ�
#include <iostream>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)  //������ⰴ���ĵ���¼�


class __declspec(dllexport) MouseHandler
{
public:
    MouseHandler()
    {

    }

    ~MouseHandler()
    {

    }

    POINT p;
    void Init_MouseHandler();
    int Start_MouseHandler(ElectronController* controller);


private:


};

#endif