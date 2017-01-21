#pragma once
#ifndef GSK_ENGINE_MEMORYM
#define GSK_ENGINE_MEMORYM

#include "..\Common.h"
#include "..\ConsoleManager\console.h"

#define ScanParseLength() (signature.find_first_of('?') == signature.npos ? signature.length() : signature.length()/2)
#define ScanParseMask(i, c) (signature.find_first_of('?') == signature.npos ? true : signature.substr(i*2, 2) != c)
#define ScanParseByte(i) (signature.find_first_of('?') == signature.npos ? signature[i] : strtol(signature.substr(i*2,2).c_str(), 0, 16))

struct sModule {
	sModule(char* modName) {
		base = 0x0; size = 0x0; end = 0x0;
		strcpy_s(moduleName, modName);
	}
	char moduleName[32];
	DWORD base, size, end;
};

class cMemoryManager {
public:
	cMemoryManager(char* windowName, char* className);
	sModule getModule(char* moduleName);

	template <class T> T read(char* moduleName, DWORD offset) {
		auto m = getModule(moduleName);
		if (m.base) {
			T readMemory;
			ReadProcessMemory(_PHandle, (LPCVOID)(m.base + offset), &readMemory, sizeof(T), NULL);
			return readMemory;
		}
		return (T)0;
	}

	template <class T> T read(DWORD address, DWORD offset = NULL) {
		T readMemory;
		ReadProcessMemory(_PHandle, (LPCVOID)(address + offset), &readMemory, sizeof(T), NULL);
		return readMemory;
	}

	template <class T> bool write(char* moduleName, DWORD offset, T value) {
		auto m = getModule(moduleName);
		if (m.base) {
			return WriteProcessMemory(_PHandle, (LPVOID)(m.base + offset), (T*)value, sizeof(T), NULL);
		}
		return false;
	}

	template <class T> bool write(DWORD base, DWORD offset = NULL, T value = NULL) {
		return WriteProcessMemory(_PHandle, (LPVOID)(base + offset), &value, sizeof(T), NULL);
	}

	DWORD scan(char* moduleName, std::string signature, bool reference);

private:
	~cMemoryManager();
	char* _windowName;
	char* _className;
	DWORD _PID;
	HANDLE _PHandle;
	bool retrieveModule(char* moduleName);
	DWORD refScan(sModule module, BYTE* address);
	std::vector<sModule> loadedModules;
};

#endif