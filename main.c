/* Uladzislau Harbuz, Yakymyshyn Maxym
 * sdcc 3.6.0 Linux throw USB to RS232 converter
 */

#include <stdlib.h>
#include <8051.h>
#include "led.h"

#if __unix__
#define xdata __xdata
#define at __at
#define sfr __sfr
#define sbit __sbit
#define interrupt __interrupt
#define critical __critical
#endif

char c;
char i = 0;
char buf[5] = {0};

void func_isr(void) interrupt 3 {
	led_update();
}

void serial_isr(void) interrupt 4{
	if (TI) TI = 0;
	if(RI) {
        c = SBUF;
        if (i >= 3) {
            buf[i] = c;
            i = 0;
            printOCT(atoi(buf));
        } else {
            buf[i++] = c;
        }
		RI = 0;
    }
}

main (void){    
    initLED();
                
    while (1)
    {

    }
}
