#include "MouseHandler.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS			//防止报错

void MouseHandler::Init_MouseHandler()
{
	//----------移除快速编辑模式(对于win10用户)----------
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hStdin, mode);
}

int MouseHandler::Start_MouseHandler(ElectronController* controller)
{
	//----------循环检测----------
	while (true) {                      			//循环检测
		GetCursorPos(&p);                   //获取鼠标在屏幕上的位置
		controller->RunMouseTask(p, KEY_DOWN(VK_LBUTTON), KEY_DOWN(VK_RBUTTON));
		//std::cout << "POINT: x" << p.x << ",y: " << p.y <<  std::endl;

		Sleep(50);                  			//等待100毫秒，减少CPU占用
	}
	return 0;
}
