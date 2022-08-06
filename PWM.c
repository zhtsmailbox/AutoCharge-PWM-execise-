#ifndef __REG52_H__
#include <reg52.h>
#endif

extern unsigned int PWM;
sbit engin = P1^0;

void timer0Init()
{
	//18432 = (20ms/(1/(11.0592/12)))*10^3 round needed by 20ms
	//PWM = 461 - 2304 rounds
	PWM = 461;
	TMOD = 0x11;
	TH0 = (65535-PWM)/256;
	TL0 = (65535-PWM)%256;
	EA =1;
	ET0 = 1;
	engin = 0;
	TR0=1;
}

void timer0() interrupt 1
{
	int i = (int)engin;
	TH0=(65535-i*(16605-PWM)-(1-i)*PWM)/256;
	TL0=(65535-i*(16605-PWM)-(1-i)*PWM)%256;
	engin = 1-i;
}