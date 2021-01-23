#pragma once
#ifndef __SNAKE_H__
#define __SNAKE_H__

#include"common.h"

extern un8 state;

#define STOP 0

#define Up 1
#define Down 2

#define Left 3
#define Right 4

void mapInti(void);
void oneFrameOption(void);
void printMap(void);
#endif // !__SNAKE_H__
