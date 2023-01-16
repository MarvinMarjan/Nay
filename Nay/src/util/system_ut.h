#pragma once

#include <Windows.h>
#include <strsafe.h>

namespace ut
{
	enum StateKey
	{
		Control = VK_CONTROL,
		LControl = VK_LCONTROL,
		RControl = VK_RCONTROL
	};

	inline bool is_statekey_pressed(StateKey key) {
		return (GetKeyState(key) == -127 || GetKeyState(key) == -128);
	}

	inline void set_mouse_visible(bool state) {
		const CONSOLE_CURSOR_INFO c_info = { 1, state };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c_info);
	}

	inline void set_console_title(LPCWSTR title) {
		TCHAR console_title[MAX_PATH];
		TCHAR current_title[MAX_PATH];


		StringCchPrintf(console_title, MAX_PATH, title, current_title);

		SetConsoleTitle(console_title);
	}
}