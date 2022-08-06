#ifndef _Oled_Control_
#define _Oled_Control_
#endif

//function
int writeCom(unsigned char COM);

int writeData(unsigned char DATA);

void oledInit();

char* numToChar(int num);

void OLEDPretreat(unsigned int SWIT,unsigned int SEC,char line1[16],char line2[16]);

void OLEDReflash();

