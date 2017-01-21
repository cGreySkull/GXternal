#include "offsetMGR.h"

cOffsetManager::cOffsetManager(cMemoryManager* memManager) {
	memoryManager = memManager;
	sModule CDLL = memoryManager->getModule("client.dll"); 
	sModule EDLL = memoryManager->getModule("engine.dll");
	Console::pprint("OM", 0x0F, "Starting offset scan");
	Console::pprint(1, "OM", 0x0F, "Main classes");
	AddOffset(GlowObjectManager, "GlowObjectManager", CDLL, "2BC8A1????????89", 0x3, 0, false);
	AddOffset(EntityList, "EntityList", CDLL, "535657BE????????BF????????8D4900", 0x9, 0, false);
	AddOffset(LocalPlayer, "LocalPlayer", CDLL, "8D049242568D3485????????8915", 0x8, 0x4, false);
	AddOffset(PlayerResource, "PlayerResource", CDLL, "8B0D????????81C1????????578B01FF50348945AC83F803", 0x2, 0, false)
	AddOffset(ForceAttack, "ForceAttack", CDLL, "740823D78915????????8B15????????F6C203740383CE04", 0x6, 0, false);
	AddOffset(ForceJump, "ForceJump", CDLL, "740823D78915????????8B15????????F6C203740383CE08", 0x6, 0, false);
	Console::pprint(1, "OM", 0x0F, "Variables");
	AddVOffset(Health, "Health", CDLL, "8B8F????????8948088BCEC7", 0x2, 0, false);
	AddVOffset(Flags, "Flags", CDLL, "8A86????????F6D0A801", 0x2, 0, false);
	AddVOffset(GlowIndex, "GlowIndex", CDLL, "8B83????????8A5DFF", 0x2, 0, false);
	AddVOffset(Team, "Team", CDLL, "8B89????????E9????????CCCCCCCCCC8B81", 0x2, 0, false);
}