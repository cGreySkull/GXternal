#pragma once
#ifndef GSK_ENGINE_OFFSETMGR
#define GSK_ENGINE_OFFSETMGR

#include "..\MemoryManager\memory.h"
#include "..\ConsoleManager\console.h"
#include "..\Common.h"

#define AddOffset(to, offname, mod, sig, offset, additional, refscan) \
				to = memoryManager->read<DWORD>(memoryManager->scan(mod.moduleName, sig, refscan) + offset) + additional;\
				Console::pprint(2, "OM", 0x0F, "%s: 0x%.8X (%s + 0x%.8X)",offname, to, mod.moduleName, to - mod.base);

#define AddVOffset(to, offname, mod, sig, offset, additional, refscan) \
				to = memoryManager->read<DWORD>(memoryManager->scan(mod.moduleName, sig, refscan) + offset) + additional;\
				Console::pprint(2, "OM", 0x0F, "%s: 0x%X",offname, to);


class cOffsetManager {
public:
	cOffsetManager(cMemoryManager* memManager);
	DWORD GlowObjectManager;
	DWORD EntityList;
	DWORD LocalPlayer;
	DWORD PlayerResource;
	DWORD ForceAttack;
	DWORD ForceJump;

	DWORD Health;
	DWORD Flags;
	DWORD GlowIndex;
	DWORD Team;
private:
	cMemoryManager* memoryManager;

};

#endif