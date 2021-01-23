#include"hc.h"
#include"snake.h"
#include<STDLIB.H>
#define DISAPPEAR 0
#define APPEAR 1

un8 state = 0;
un16 mapInList[16] = { 0 };
un16 error[16] = {
0x4E51, 0x555D, 0xC05E, 0x455E, 0xC05F, 0x465F, 0xC05F, 0x5555,
0x728A, 0x8A72, 0x037A, 0x827A, 0x03FA, 0xAAAA, 0x03FA, 0x6ABA };

struct position
{
	char x;
	char y;
};
struct position head = { 7,7 };
struct position tail = { 8,7 };
struct position food = { 9,7 };

void printMap(void)
{
	un8 count = 16;
	while (count--)
	{
		sendHc595Data(mapInList[count]);
		setHc138(count);
		delay(255);
		sendHc595Data(0x00);
	}
}

//下一个蛇头
un8 snakeHeadMove(void)
{
	switch (state)
	{
	case Up:
		return --head.y;
	case Down:
		return ++head.y;
	case Left:
		return --head.x;
	case Right:
		return ++head.x;
	default:
		break;
	}
}

bit checkNum(un16 num, char y)
{
	y = 15 - y;
	if (y >= 0 && y <= 15)
	{
		while (y--)
			num /= 2;
		return num % 2;
	}
	else
		return 0;
}

//下一个蛇尾
void sankeTailMove()
{
	if (checkNum(mapInList[tail.x], tail.y + 1))
		tail.y++;
	else
		if (checkNum(mapInList[tail.x], tail.y - 1))
			tail.y--;
		else
			if (checkNum(mapInList[tail.x + 1], tail.y))
				tail.x++;
			else
				tail.x--;
}

void dotSet(struct position address, bit option)
{
	un16 set;
	set = 0x0001 << (15 - address.y);
	if (option)
		mapInList[address.x] |= set;
	else
		mapInList[address.x] &= (~set);
}

void createFood(void)
{
	while (checkNum(mapInList[food.x], food.y))
	{
		food.x = rand() % 16;
		food.y = rand() % 16;
	}
	dotSet(food, APPEAR);
}

void gameOver(void)
{
	un8 count = 16;
	while (count--)
		mapInList[count] = error[count];
	state = STOP;
	while (!state)
		printMap();
	mapInti();
}

void oneFrameOption(void)
{
	un8 gameFlag, count = 255;
	if ((gameFlag = snakeHeadMove()) && gameFlag <= 15)
	{

		if (head.x == food.x && head.y == food.y)
			createFood();
		else
			if (checkNum(mapInList[head.x], head.y))
				gameOver();
		dotSet(head, APPEAR);
		dotSet(tail, DISAPPEAR);
		sankeTailMove();
		while (count--)
			printMap();
	}
	else
		gameOver();
}

void mapInti(void)
{
	un8 count;
	un8 sed;
	for (count = 0; count < 16; count++)
		mapInList[count] = 0;
	head.x = head.y = tail.x = food.x = 7;
	tail.x = 8;
	food.x = 9;
	state = Right;
	dotSet(head, APPEAR);
	dotSet(tail, APPEAR);
	srand(&sed);
	createFood();
}