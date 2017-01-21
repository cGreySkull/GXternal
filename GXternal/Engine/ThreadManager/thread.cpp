#include "thread.h"

bool cThreadManager::create(char* threadName, void* funcPtr) {
	HANDLE newThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)funcPtr, 0, 0, 0);
	if (!newThread) {
		Console::pprint("TM", 0x0C, "Could not create thread %s", threadName);
		return false;
	}
	Console::pprint("TM", 0x0F, "Created thread %s", threadName);
	threadList.push_back(sThread(threadName, newThread, funcPtr));
	return true;
}

bool cThreadManager::end(char* threadName) {
	for (auto m : threadList) {
		if (!_stricmp(threadName, m.name)) {
			if (TerminateThread(m.threadHandle, 0)) {
				Console::pprint("TM", 0x0F, "Thread %s ended", m.name);
				return true;
			}
			else {
				Console::pprint("TM", 0x0C, "Could not end thread %s", m.name);
				return false;
			}
		}
	}
}

void cThreadManager::endAll() {
	for (auto m : threadList) {
		end(m.name);
	}
}