/* Uladzislau Harbuz, Yakymyshyn Maxym
 * sdcc 3.6.0 Linux throw USB to RS232 converter
 */

#include <stdlib.h>
#include <8051.h>
#include "led.h"
#include "keyboard.h"


char c;
char i = 0;
char buf[5] = {0};

void func_isr(void) __interrupt 3 {
	led_update();
	get_key();
}

main (void){    
	
	
    initLED();
                
    while (1)
    {
		 
		printOCT(key);
    }
}
