#pragma once
#ifndef GSK_ENGINE_CONSOLE
#define GSK_ENGINE_CONSOLE

#include "..\Common.h"

namespace Console {
	void setTitle(char* newTitle, ...);
	HWND findWindow(char* windowName, char* className = NULL);
	void setCursor(SHORT x, SHORT y);
	void setCursor(bool state);
	WORD setColor(WORD color);
	WORD getColor();
	void cprint(char* msg, ...);
	void cprint(WORD color, char* msg, ...);
	void pprint(char* prefix, WORD color, char* msg, ...);
	void pprint(int level, char* prefix, WORD color, char* msg, ...);
}

#endif