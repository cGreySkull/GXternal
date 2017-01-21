#pragma once
#ifndef GSK_ENGINE_ENTITY
#define GSK_ENGINE_ENTITY

#include "..\ConsoleManager\console.h"
#include "..\MemoryManager\memory.h"
#include "..\OffsetManager\offsetMGR.h"
#include "..\Common.h"

class cEntityManager {
public:
	cEntityManager(int entityID, cMemoryManager* memManager, cOffsetManager* offManager);
	cEntityManager(cMemoryManager* memManager, cOffsetManager* offManager);
	void forceJump();
	int health();
	bool inAir();
	byte flags();
	int glowIndex();
	eTeam team();
	bool isValidLivePlayer();
	void setGlow(float r, float g, float b, float a, bool throughWalls);
private:
	cMemoryManager* memoryManager;
	cOffsetManager* offsetManager;
	DWORD entityPointer;
	int entityID;
};

#endif