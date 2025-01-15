#pragma once
#include <Windows.h>
#include <mutex>
#include <vector>
#include "game_struct.h"

extern DWORD32 NumberOfBot;
extern std::mutex gmutex;
extern PEntity Player;
extern PBot BotList;

