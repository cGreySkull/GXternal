#include "main.h"

using namespace std;

cEngine g_Main(NULL, "Valve001");

void _BHOP(){
	while (true) {
		auto local = g_Main.GetLocalEntity();
		if (!(local.inAir()) && GetAsyncKeyState(VK_SPACE)) {
			local.forceJump();
		}
		Sleep(1);
	}
	return;
}

void _GLOW() {
	while (true) {
		for (int i = 1; i < 16; i++) {
			auto entity = g_Main.GetEntity(i);
			if (entity.isValidLivePlayer()) {
				if (entity.team() == TEAM_CT) {
					entity.setGlow(0.0f, 0.0f, 1.0f, 0.6f, true);
				}
				else {
					entity.setGlow(1.0f, 0.0f, 0.0f, 0.6f, true);
				}
			}
		}
		Sleep(1);
	}
	return;
}

int main() {
	g_Main.Thread.create("TBHOP", _BHOP);
	g_Main.Thread.create("TGLOW", _GLOW);
	while (true) {
		if (GetAsyncKeyState(VK_END)) {
			g_Main.Thread.endAll();
			break;
		}
		Sleep(300);
	}
	return 0;
}