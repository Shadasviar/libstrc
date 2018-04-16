#include <8051.h>
#include "keyboard.h"

#define KEY (U12 & 0xf0)

__xdata __at 0x8000 unsigned char U15;
__xdata __at 0x8000 unsigned char U12;

const unsigned char column[] = {0xfd, 0xfe, 0xf7, 0xfb}; 

char convert(unsigned char k)
{
	if(k == 0x70) return 0;
	if(k == 0xb0) return 1;
	if(k == 0xd0) return 2;
	if(k == 0xe0) return 3;	
	
	return -1;
}

char keys[4][4] =
{
	{19,15,11,7},
	{18,14,10,6},
	{21,17,13,9},
	{20,16,12,8}
};

char key = 0;		
static char t = 0;	

void get_key (void)
{	
	U15 = column[t];
	
	if(KEY == 0xd0 || KEY == 0xe0 || KEY == 0x70 || KEY == 0xb0) 
	key = keys[t][convert(KEY)];
     
	t++;
	t=t%4;
   
} 




