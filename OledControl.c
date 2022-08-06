
#ifndef __STRING_H__
#include <string.h>
#endif

#ifndef __REG52_H__
#include <reg52.h>
#endif

//OLED argument,databus connected to P0
sbit RS = P3^5;
sbit RW = P3^6;
sbit OLEDEN = P3^4;
sbit OLEDBUSY = P0^7;
sfr  OLEDInfo = 0xA0;

sbit DULA = P2^6;
sbit WELA = P2^7;

char firstLine[16]={"                "}; //OFF/ON show start 0x80+12
char secondLine[16]={"                "};  //num show start 0x80+0x40



int writeCom(unsigned char COM)
{
	int i;
	RS = 0;
	RW = 0;
	OLEDEN = 1;
	OLEDInfo = COM;
	i=300;
	while(i--);
	OLEDEN = 0;
	return 1;
}

int writeData(unsigned char DATA)
{
	int i;
	RS = 1;
	RW = 0;
	OLEDEN = 1;
	OLEDInfo = DATA;
	i = 300;
	while(i--);
	OLEDEN = 0;
	return 1;
}

void oledInit()
{
	DULA = 0;
	WELA = 0;
	OLEDEN = 0;
	writeCom(0x38);
	writeCom(0x0c);
	writeCom(0x06);
	writeCom(0x01);
	writeCom(0x80);
}
//5位整数变char
char* numToChar(int num)
{
	int temp,len;
	char res[5]={"     "};
	char* p;
	len = 4;
	while(num && (len>=0))
	{
		if(num == 0)
			return -1;
		temp = num%10+48;
		num = num/10;
		res[len]=temp;
		len--;
	}
	p = res;
	return p;
}


void OLEDPretreat(unsigned int SWIT,unsigned int SEC,char line1[16],char line2[16])
{
	int i;
	unsigned int swit = SWIT;
	unsigned int sec = SEC;
	char _Otemp[5]={"     "};
	char* _Onum;
	
	//switch swit init to firstline
	if(swit == 0)
	{
		_Otemp[0]='R';
		_Otemp[1]='E';
		_Otemp[2]='A';
		_Otemp[3]='D';
		_Otemp[4]='Y';
	}
	else
	{
		_Otemp[0]='S';
		_Otemp[1]='T';
		_Otemp[2]='A';
		_Otemp[3]='R';
		_Otemp[4]='T';
	}
	for(i=11;i<16;i++)
	{
		line1[i]=_Otemp[i-11];
	}
	
	
	//num init to secondline
	_Onum = numToChar(sec);
	for(i=0;i<5;i++)
	{
		line2[i]=*_Onum;
		_Onum++;
	}
	
	for(i=0;i<16;i++)
	{
		firstLine[i]=line1[i];
	}
	
	for(i=0;i<16;i++)
	{
		secondLine[i]=line2[i];
	}
}
void OLEDReflash()
{
	int i;
	writeCom(0x80);
	for(i=0;i<16;i++)
	{
		writeData(firstLine[i]);
	}
	writeCom(0x80+0x40);
	for(i=0;i<16;i++)
	{
		writeData(secondLine[i]);
	}
	OLEDEN = 0;
}