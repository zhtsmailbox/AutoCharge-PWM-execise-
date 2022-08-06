#include <reg52.h>
#include <intrins.h>
#include <string.h>

#include "AutoCharge.h"
#include "OledControl.h"
#include "PWM.h"
#include "CountDown.h"

#define uchar unsigned char
#define uint unsigned int





void main()
{
	//
	char fLine[16]={"COUNT DOWN      "};
	char sLine[16]={"       Sec LEFT "};
	int k;
	uint swit,second;
	second	= 5;
	timeN = second;
	swit = 0;
	//PWM control
	timer0Init();
	oledInit();
	button = 1;
	//
	while(1)
	{
		//OLED show
		OLEDPretreat(swit,timeN,&fLine,&sLine);
		OLEDReflash();
		
		//Key scan
		if(button == 0)
		{
			swit = 1;
			countDownReady(timeN);
		}
		
		
		//Timer Countdown
		if(timeN<=0)
		{
			trigger();
			TR1=0;
			timeN = second;
			swit = 0;
			
		}
	
		//RESET argument
		
		
		
		
		while(k--);
		k=100;
		
	}
	// End of Main While
	
}

