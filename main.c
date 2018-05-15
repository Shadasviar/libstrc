/* Uladzislau Harbuz, Yakymyshyn Maxym
 * sdcc 3.6.0 Linux throw USB to RS232 converter
 */

#include <stdlib.h>
#include <8051.h>
#include "strc51_time.h"
#include "lcd.h"


void func_isr(void) __interrupt 3 {
    counter_timer();
}

main (void) {    
   
    char c = 0;
    
    LcdInit();
    init_time();
    LcdClrScr();
    
    while (1) {
        ShowProgressTriangle(c++);
        if (c >= 16) {
            LcdClrScr();
            LcdPrintHex16(c);
        }
        if (c >= 32) {
            LcdClrScr();
            c = 0;
        }
        sleep(1);
    }
}
