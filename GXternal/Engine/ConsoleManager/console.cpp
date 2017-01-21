#include "console.h"

namespace Console {
	void setTitle(char* newTitle, ...) {
		char buf[64];
		GetArgs(newTitle, buf);
		SetWindowText(GetConsoleWindow(), buf);
	}

	HWND findWindow(char* windowName, char* className) {
		return FindWindowA(className, windowName);
	}

	void setCursor(SHORT x, SHORT y) {
		COORD newPos = { x,y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPos);
	}

	void setCursor(bool state) {
		HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(outputHandle, &cursorInfo);
		cursorInfo.bVisible = state;
		SetConsoleCursorInfo(outputHandle, &cursorInfo);
	}

	WORD setColor(WORD color) {
		HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		HANDLE inputHandle = GetStdHandle(STD_INPUT_HANDLE);
		WORD oldColor = getColor();
		SetConsoleTextAttribute(outputHandle, color);
		FlushConsoleInputBuffer(inputHandle);
		return oldColor;
	}

	WORD getColor() {
		HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO CSBI;
		GetConsoleScreenBufferInfo(outputHandle, &CSBI);
		return CSBI.wAttributes;
	}

	void cprint(char* msg, ...) {
		char buf[64];
		GetArgs(msg, buf);
		printf("%s", buf);
	}

	void cprint(WORD color, char* msg, ...) {
		char buf[64];
		GetArgs(msg, buf);
		WORD oldColor = setColor(color);
		printf("%s", buf);
		setColor(oldColor);
	}

	void pprint(char* prefix, WORD color, char* msg, ...) {
		char buf[64];
		GetArgs(msg, buf);
		WORD oldColor = setColor(0x0B);
		printf("[%s] ", prefix);
		setColor(color);
		printf("%s\n", buf);
		setColor(oldColor);
	}

	void pprint(int level, char* prefix, WORD color, char* msg, ...) {
		char buf[64];
		GetArgs(msg, buf);
		WORD oldColor = setColor(0x0B);
		for (int i = 0; i < level; i++) {
			printf("   ");
		}
		printf("%c[%s] ",0xC3, prefix);
		setColor(color);
		printf("%s\n", buf);
		setColor(oldColor);
	}
}