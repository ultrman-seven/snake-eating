#include"common.h"
#include<intrins.h>
// 138a 138b
sbit dat0_138_a = P1 ^ 1;
sbit dat1_138_a = P1 ^ 1;
sbit dat2_138_a = P1 ^ 1;
sbit dat0_138_b = P1 ^ 1;
sbit dat1_138_b = P1 ^ 1;
sbit dat2_138_b = P1 ^ 1;

sbit shift = P1 ^ 1;
sbit transfer = P1 ^ 1;
sbit sda = P1 ^ 1;

void setHc138(un8 dat)
{
	if (dat >= 8)
	{
		dat -= 8;
		dat0_138_a = dat % 2;
		dat /= 2;
		dat1_138_a = dat % 2;
		dat /= 2;
		dat2_138_a = dat % 2;
		dat /= 2;
	}
	else
	{
		dat0_138_b = dat % 2;
		dat /= 2;
		dat1_138_b = dat % 2;
		dat /= 2;
		dat2_138_b = dat % 2;
		dat /= 2;
	}
}

void sendHc595Data(un16 dat)
{
	un8 count;
	for (count = 0; count < 16; count++)
	{
		sda = dat >> 15;
		dat <<= 1;
		shift = 0;
		_nop_();
		shift = 1;
	}
	transfer = 0;
	_nop_();
	transfer = 1;
}