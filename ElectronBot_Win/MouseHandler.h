#ifndef ELECTRONBOTSDK_MOUSEHANDLER_H
#define ELECTRONBOTSDK_MOUSEHANDLER_H
#include "electron_controller.h"
#include <windows.h>                			//GetAsyncKeyState所需头文件
#include <iostream>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)  //用来检测按键的点击事件


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