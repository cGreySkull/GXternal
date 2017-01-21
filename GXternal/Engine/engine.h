#pragma once
#ifndef GSK_ENGINE
#define GSK_ENGINE

#include "ConsoleManager\console.h"
#include "MemoryManager\memory.h"
#include "EntityManager\entity.h"
#include "ThreadManager\thread.h"

#include "OffsetManager\offsetMGR.h"

class cEngine {
public:
	cEngine(char* processName, char* className = NULL);
	cMemoryManager* Mem;
	cOffsetManager* Offset;
	cEntityManager GetEntity(int eID);
	cEntityManager GetLocalEntity();
	cThreadManager Thread;
private:
};

#endif