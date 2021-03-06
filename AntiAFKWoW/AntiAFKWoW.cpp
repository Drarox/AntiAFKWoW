// AntiAFKWoW.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <ctime>

void keyPress(DWORD key, DWORD time);

int main()
{

	bool    enabled = false;
	bool    enabled2 = false;
	int     i = 0;
	WORD    vKeyWalk[4] = { 0x53, 0x44, 0x53, 0x44 }; //w, a, s, d { 0x53, 0x44, 0x53, 0x44 };
	clock_t tmr = clock();

	std::cout << "Press numpad 1 to toggle " << std::endl;

	while (!GetAsyncKeyState(VK_F10))
	{
		if (GetAsyncKeyState(VK_NUMPAD1))
		{
			enabled = !enabled;
			std::cout << (enabled ? "Enabled" : "Disabled") << std::endl;
		}

		if (GetAsyncKeyState(VK_NUMPAD2))
		{
			enabled2 = !enabled2;
			std::cout << (enabled2 ? "Enabled2" : "Disabled2") << std::endl;
		}

		if (enabled && (clock() - tmr > 600000)) //600000ms = 10min
		{
			tmr = clock();

			if (i > 3)
				i = 0;

			keyPress(vKeyWalk[i], 100); //walk

			std::cout << "Click" << std::endl;

			i++;
		}

		if (enabled2 && (clock() - tmr > 600000)) //600000ms = 10min
		{
			tmr = clock();

			if (i > 3)
				i = 0;

			keyPress(vKeyWalk[i], 100); //walk

			std::cout << "Click" << std::endl;

			int msgboxID = MessageBox(
				NULL,
				(LPCWSTR)L"Click",
				(LPCWSTR)L"Oui",
				MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
			);

			i++;
		}

		Sleep(100);
	}
}

void keyPress(DWORD key, DWORD time)
{
	INPUT   input;
	input.type = INPUT_KEYBOARD;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.dwFlags = 0;

	input.ki.wScan = MapVirtualKey(key, MAPVK_VK_TO_VSC);
	input.ki.wVk = key;

	SendInput(1, &input, sizeof(INPUT));
	Sleep(time);

	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}