#include"common.h"
#include"snake.h"
sbit keyUp;
sbit keyDown;
sbit keyLeft;
sbit keyRight;
sbit keySpace;
#define PRESSED (!(keyUp&&keyDown&&keyLeft&&keyRight&&keySpace))
un8 tempKey;
void delay(un16 n)
{
	while (n--)
		;
}

void checkKeys(void)
{
	if (PRESSED)
	{
		if (state)
		{
			if (!keyUp && (state != Down))
				state = Up;
			if (!keyDown && (state != Up))
				state = Down;
			if (!keyLeft && (state != Right))
				state = Left;
			if (!keyRight && (state != Left))
				state = Right;
		}
		if (!keySpace)
			if (state)
			{
				tempKey = state;
				state = STOP;
			}
			else
				state = tempKey;
	}
}

main()
{
	mapInti();
	state = STOP;
	while (1)
	{
		checkKeys();
		if (state)
			oneFrameOption();
		else
			printMap();
	}
}