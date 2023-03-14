#include "MouseHandler.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS			//��ֹ����

void MouseHandler::Init_MouseHandler()
{
	//----------�Ƴ����ٱ༭ģʽ(����win10�û�)----------
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hStdin, mode);
}

int MouseHandler::Start_MouseHandler(ElectronController* controller)
{
	//----------ѭ�����----------
	while (true) {                      			//ѭ�����
		GetCursorPos(&p);                   //��ȡ�������Ļ�ϵ�λ��
		controller->RunMouseTask(p, KEY_DOWN(VK_LBUTTON), KEY_DOWN(VK_RBUTTON));
		//std::cout << "POINT: x" << p.x << ",y: " << p.y <<  std::endl;

		Sleep(50);                  			//�ȴ�100���룬����CPUռ��
	}
	return 0;
}
