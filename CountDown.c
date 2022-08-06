#ifndef __REG52_H__
#include <reg52.h>
#endif

extern unsigned int timeN;
extern unsigned int PWM;
int round=0;

void trigger()
{
	int i,j;
	while(PWM<2304)
	{
		PWM++;
		for(i=0;i<100;i++)
		{
			;
		}
	}
	for(i=0;i<100;i++)
	{
		for(j=0;j<300;j++)
		{
			;
			;
			;
		}
	}
	while(PWM>461)
	{
		PWM--;
		for(i=0;i<100;i++)
		{
			;
		}
	}
	PWM=461;
}

void countDownReady(unsigned int timeNum)
{
	timeN = timeNum;
	round = 0;
	TMOD = 0x11;
	TH1 = (65535-15535)/256;
	TL1 = (65535-15535)%256;
	EA =1;
	ET1 = 1;
	TR1=1;
}


void timer1() interrupt 3
{
	round++;
	TH1 = (65535-15535)/256;
	TL1 = (65535-15535)%256;
	if(round >=49)
	{
		round = 0; 
		if(timeN>0)
		{
			timeN--;
		}
		
	}
}