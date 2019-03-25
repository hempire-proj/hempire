#include "ESP.h"

/*
* @Author: V.E.R. Inc
*/
int main()
{
	int procID = MemClass.getProcess(L"csgo.exe");
	val.gameModule = MemClass.getModule(procID, L"client_panorama.dll");
	val.localPlayer = MemClass.readMem<uintptr_t>(val.gameModule + offset.localPlayer);

	if (val.localPlayer == NULL)
		while (val.localPlayer == NULL)
			val.localPlayer = MemClass.readMem<uintptr_t>(val.gameModule + offset.localPlayer);

	while (true)
	{
		if (GetKeyState(VK_F1) & 1)
			HandleGlow();
		Sleep(1);
	}
	return 0;
}