#pragma once

#define BASE 0x00400000

struct 
{
	DWORD Event_BotAdded	= 0x11223E;
	DWORD Event_ChangeParty = 0xD6310;
	DWORD Event_Damage		= 0x1C223;
	DWORD Event_SwitchGun	= 0xC8938;
	DWORD Event_Fire        = 0xC7282; 
	DWORD Event_FireRate    = 0xC73EA;

	DWORD Patch_Recoil = 0xC2EB9;



	DWORD Player			= 0x17E0A8;
	DWORD Botlist			= 0x191FCC;

	DWORD Grenade			= 0x140;

	DWORD Gun_MTP57			= 0x0140;
	DWORD Gun_Sniper		= 0x13c;
	DWORD Gun_ARD_10		= 0x138;
	DWORD Gun_V19			= 0x134;
	DWORD Gun_TMP			= 0x130;


	DWORD Pos_Z				= 0x28;
	DWORD Pos_X				= 0x2C;
	DWORD Pos_Y				= 0x30;

	DWORD Rot_X				= 0x34;
	DWORD Rot_Y				= 0x38;

} Offsets;