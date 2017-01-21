#pragma once
#ifndef GSK_ENGINE_COMMON
#define GSK_ENGINE_COMMON

#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>

#define GetArgs(from, to) va_list args; va_start(args, from); vsprintf_s(to, from, args); va_end(args);

#define FL_ONGROUND (1 << 0)

enum eTeam {
	TEAM_Unk = 0,
	TEAM_Unk2,
	TEAM_T,
	TEAM_CT
};

struct sGlowEntity {
public:
	DWORD* entityPointer;
	float r, g, b, a;
private:
	char unk1[16];
public:
	bool RenderWhenOccluded;
	bool RenderWhenUnoccluded;
	bool FullBloom;
private:
	char unk2[14];
};

#endif