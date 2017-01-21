#include "entity.h"

cEntityManager::cEntityManager(int eID, cMemoryManager* memManager, cOffsetManager* offManager) {
	entityID = eID;
	memoryManager = memManager;
	offsetManager = offManager;
	entityPointer = memoryManager->read<DWORD>(offsetManager->EntityList + (entityID * 0x10));
}

cEntityManager::cEntityManager(cMemoryManager* memManager, cOffsetManager* offManager) {
	memoryManager = memManager;
	offsetManager = offManager;
	entityPointer = memoryManager->read<DWORD>(offsetManager->LocalPlayer);
}

int cEntityManager::health() {
	return memoryManager->read<int>(entityPointer, offsetManager->Health);
}

byte cEntityManager::flags() {
	return memoryManager->read<byte>(entityPointer, offsetManager->Flags);
}

bool cEntityManager::inAir() {
	return !(flags() & FL_ONGROUND);
}

void cEntityManager::forceJump() {
	memoryManager->write(offsetManager->ForceJump, 0, 0x6);
}

int cEntityManager::glowIndex() {
	return memoryManager->read<int>(entityPointer, offsetManager->GlowIndex);
}

void cEntityManager::setGlow(float r, float g, float b, float a, bool throughWalls) {
	DWORD dwGlowObject = memoryManager->read<DWORD>(offsetManager->GlowObjectManager);
	sGlowEntity tempGlow = memoryManager->read<sGlowEntity>(dwGlowObject, glowIndex()*sizeof(sGlowEntity));
	tempGlow.r = r; tempGlow.g = g; tempGlow.b = b; tempGlow.a = a;
	tempGlow.RenderWhenOccluded = throughWalls;
	tempGlow.RenderWhenUnoccluded = !throughWalls;
	memoryManager->write(dwGlowObject, glowIndex() * sizeof(sGlowEntity), tempGlow);
}

eTeam cEntityManager::team() {
	return memoryManager->read<eTeam>(entityPointer, offsetManager->Team);
}

bool cEntityManager::isValidLivePlayer() {
	int HP = health();
	eTeam TM = team();
	if ((HP > 0 && HP <= 100) && (TM == TEAM_CT || TM == TEAM_T))
		return true;
	return false;
}