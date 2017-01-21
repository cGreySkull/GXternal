#include "engine.h"

cEngine::cEngine(char* processName, char* className) {
	Console::setTitle("%.8XG%.8XE");
	Console::pprint("EN", 0x0F, "Loading Engine functions");
	Mem = new cMemoryManager(processName, className);
	Console::pprint("EN", 0x0F, "Loading Offset Manager");
	Offset = new cOffsetManager(Mem);
}

cEntityManager cEngine::GetEntity(int eID) {
	return cEntityManager(eID, Mem, Offset);
}

cEntityManager cEngine::GetLocalEntity() {
	return cEntityManager(Mem, Offset);
}