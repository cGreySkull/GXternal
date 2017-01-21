#include "memory.h"

cMemoryManager::cMemoryManager(char* windowName, char* className) {
	_windowName = windowName; _className = className;
	Console::pprint("MM", 0x0F, "Searching for window %s @ class %s", _windowName, _className);
	HWND windowHandle;
	while (!(windowHandle = Console::findWindow(_windowName, _className))) {
		Sleep(1000);
	}
	Console::pprint(1,"MM", 0x0F, "Window found!");
	GetWindowThreadProcessId(windowHandle, &_PID);
	Console::pprint(1, "MM", 0x0F, "Process ID: %X", _PID);
	_PHandle = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, false, _PID);
	if (!_PHandle) ExitProcess(EXIT_FAILURE);
}

cMemoryManager::~cMemoryManager() {
	if (_PHandle) {
		CloseHandle(_PHandle);
		Console::pprint("MM", 0x0C, "Closing process handle");
	}
}

sModule cMemoryManager::getModule(char* moduleName) {
	for (auto m : loadedModules) {
		if (!_stricmp(moduleName, m.moduleName)) {
			return m;
		}
	}
	int localAttempts = 0;
	while (!retrieveModule(moduleName)) {
		if (localAttempts > 120) {
			Console::pprint("MM", 0x0C, "Failed to load module %s", moduleName);
			return sModule(moduleName);
		}
		localAttempts++;
		Sleep(1000);
	}
	return loadedModules.back();
}

bool cMemoryManager::retrieveModule(char* moduleName) {
	HANDLE moduleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 moduleEntry;
	moduleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, _PID);

	if (moduleSnap == INVALID_HANDLE_VALUE)
		return false;

	moduleEntry.dwSize = sizeof(MODULEENTRY32);

	if (!Module32First(moduleSnap, &moduleEntry))
		return false;

	do {
		if (!_stricmp(moduleName, moduleEntry.szModule)) {
			sModule tempModule(moduleName);
			tempModule.base = (DWORD)moduleEntry.modBaseAddr;
			tempModule.size = (DWORD)moduleEntry.modBaseSize;
			tempModule.end = tempModule.base + tempModule.size;
			loadedModules.push_back(tempModule);
			Console::pprint("MM", 0x0F, "Module %s loaded", moduleName);
			Console::pprint(1, "MM", 0x0F, "Base: 0x%.8X", tempModule.base);
			Console::pprint(1, "MM", 0x0F, "End: 0x%.8X", tempModule.end);
			Console::pprint(1, "MM", 0x0F, "Size: 0x%.8X", tempModule.size);
			CloseHandle(moduleSnap);
			return true;
		}
	} while (Module32Next(moduleSnap, &moduleEntry));

	CloseHandle(moduleSnap);
	return false;
}

DWORD cMemoryManager::refScan(sModule module, BYTE* address) {
	BYTE* bytes = (BYTE*)VirtualAlloc(0, module.size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	ReadProcessMemory(_PHandle, (LPCVOID)module.base, bytes, module.size, NULL);
	for (DWORD i = 0; i < module.size; i++) {
		if (bytes[i] == address[0]) {
			for (unsigned int x = 0;; x++) {
				if (x == 5) {
					return module.base + i;
				}
				if (bytes[i + x] == address[x])continue; else break;
			}
		}
	}
	return NULL;
}

DWORD cMemoryManager::scan(char* moduleName, std::string signature, bool reference) {
	sModule scannedModule = getModule(moduleName);
	if (scannedModule.base) {
		BYTE* bytes = (BYTE*)VirtualAlloc(0, scannedModule.size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		ReadProcessMemory(_PHandle, (LPCVOID)scannedModule.base, bytes, scannedModule.size, NULL);
		for (DWORD i = 0; i < scannedModule.size; i++) {
			if (bytes[i] == ScanParseByte(0)) {
				for (unsigned int x = 0;; x++) {
					if (x == ScanParseLength()) {
						if (reference) {
							VirtualFree(bytes, 0, MEM_RELEASE);
							BYTE refCount[5] = { 0x68, 0x00, 0x00, 0x00, 0x00 };
							*(DWORD*)&refCount[1] = (DWORD)(scannedModule.base + i);
							return refScan(scannedModule, refCount);
						}
						VirtualFree(bytes, 0, MEM_RELEASE);
						return scannedModule.base + i;
					}
					if (ScanParseMask(x, "??")) {
						if (bytes[i + x] == ScanParseByte(x)) continue; else break;
					}
				}
			}
		}
		VirtualFree(bytes, 0, MEM_RELEASE);
	}
	return NULL;
}