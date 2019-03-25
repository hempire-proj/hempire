#pragma once
#include "Init.h"


struct GlowStruct
{
	BYTE base[4];
	float red;
	float green;
	float blue;
	float alpha;
	BYTE buffer[16];
	bool renderWhenOccluded;
	bool renderWhenUnOccluded;
	bool fullBloom;
	BYTE buffer1[5];
	int glowStyle;
};

GlowStruct SetGlowColor(GlowStruct Glow, uintptr_t entity)
{
	bool defusing = MemClass.readMem<bool>(entity + offset.isDefusing);
	if (defusing)
	{
		Glow.red = 1.0f;
		Glow.green = 1.0f;
		Glow.blue = 1.0f;
	}
	else
	{
		int health = MemClass.readMem<int>(entity + offset.health);
		Glow.red = health * -0.01 + 1;
		Glow.green = health * 0.01;
	}
	Glow.alpha = 1.0f;
	Glow.renderWhenOccluded = true;
	Glow.renderWhenUnOccluded = false;
	return Glow;
}

void SetTeamGlow(uintptr_t entity, int glowIndex)
{
	GlowStruct TGlow;
	TGlow = MemClass.readMem<GlowStruct>(val.glowObject + (glowIndex * 0x38));

	TGlow.blue = 1.0f;
	TGlow.alpha = 1.0f;
	TGlow.renderWhenOccluded = true;
	TGlow.renderWhenUnOccluded = false;
	MemClass.writeMem<GlowStruct>(val.glowObject + (glowIndex * 0x38), TGlow);
}

void SetEnemyGlow(uintptr_t entity, int glowIndex)
{
	GlowStruct EGlow;

	EGlow = MemClass.readMem<GlowStruct>(val.glowObject + (glowIndex * 0x38));
	EGlow = SetGlowColor(EGlow, entity);
	MemClass.writeMem<GlowStruct>(val.glowObject + (glowIndex * 0x38), EGlow);
}

void HandleGlow()
{
	val.glowObject = MemClass.readMem<uintptr_t>(val.gameModule + offset.dwGlowObjectManager);
	int myTeam = MemClass.readMem<int>(val.localPlayer + offset.team);

	for (short int i = 0; i < 64; i++)
	{
		uintptr_t entity = MemClass.readMem<uintptr_t>(val.gameModule + offset.entityList + i * 0x10);
		if (entity != NULL)
		{
			int glowIndx = MemClass.readMem<int>(entity + offset.glowIndex);
			int entityTeam = MemClass.readMem<int>(entity + offset.team);

			if (myTeam == entityTeam)
				SetTeamGlow(entity, glowIndx);
			else
				SetEnemyGlow(entity, glowIndx);
		}
	}
}
