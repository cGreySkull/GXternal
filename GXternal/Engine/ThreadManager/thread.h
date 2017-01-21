#pragma once
#ifndef GSK_ENGINE_THREAD
#define GSK_ENGINE_THREAD

#include "..\ConsoleManager\console.h"
#include "..\Common.h"

struct sThread {
	sThread(char* cname, HANDLE chandle, void* fPtr) {
		strcpy_s(name, cname);
		threadHandle = chandle;
		funcPtr = fPtr;
	}
	char name[64];
	HANDLE threadHandle;
	void* funcPtr;
};

class cThreadManager {
public:
	bool create(char* threadName, void* funcPtr);
	bool end(char* threadName);
	void endAll();
private:
	std::vector<sThread> threadList;
};

#endif