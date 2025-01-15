#pragma once
#include <Windows.h>  




#define CONCAT(a, b) CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a ## b


#define PADDING(t,n) t CONCAT(p,__COUNTER__)  [(n)/sizeof(t)];


 typedef  __pragma(pack(push, 1)) struct
{
	PADDING(DWORD, 4)

    float ZO;
	float XO;
	float YO;

	PADDING(DWORD, (0x28-((3 * 4) + 4)))

	float Z;						  
	float X;
	float Y;
	float RotX;
	float RotY;

	PADDING(BYTE, ((0xEC - (0x28 + (5 * 4)))))

	DWORD Health;

	PADDING(BYTE, ((0x205 - (0xEC+4))))

	char* Name;

} __pragma(pack(pop)) Entity, * PEntity;

typedef struct
{
	PEntity * BotList;
	PADDING(DWORD, 4)
	DWORD   NumberOfBot;

} Bot, *PBot;





