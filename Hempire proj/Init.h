#pragma once
#include <Windows.h>
#include <iostream>
#include "MemMan.h"
#include "csgo.hpp"
MemMan MemClass;

struct offsets
{
	uintptr_t localPlayer = hazedumper::signatures::dwLocalPlayer;
	uintptr_t entityList = hazedumper::signatures::dwEntityList;
	uintptr_t dwGlowObjectManager = hazedumper::signatures::dwGlowObjectManager;
	uintptr_t glowIndex = hazedumper::netvars::m_iGlowIndex;
	uintptr_t team = hazedumper::netvars::m_iTeamNum;
	uintptr_t health = hazedumper::netvars::m_iHealth;
	uintptr_t isDefusing = hazedumper::netvars::m_bIsDefusing;
} offset;

struct variables
{
	uintptr_t localPlayer;
	uintptr_t gameModule;
	uintptr_t glowObject;
} val;
