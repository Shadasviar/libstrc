#include <8051.h>
#include "keyboard.h"

xdata at 0x8000 unsigned char U15;
xdata at 0x8000 unsigned char U12;

const unsigned char column[] = {0xfd, 0xfe, 0xf7, 0xfb}; 

c
#define KEY (U12 & 0xf0)

char keys[][] =
{
	{18,14,10,6},//0
	{19,15,11,7},//1
	{20,16,12,8},//2
	{21,17,13,9} //3
};

int key =-1;		
static int t = 0;	

void get_key (void)
{	
	U15 = column[t];
	
	if(KEY == 0xd0 || KEY == 0xe0 || KEY == 0x70 || KEY == 0xb0) 
	key = keys[t][KEY];
     
	t++;
	t=t%4;
   
} 




