/* Uladzislau Harbuz, Yakymyshyn Maxym
 * sdcc 3.6.0 Linux throw USB to RS232 converter
 */

#include <stdlib.h>
#include <8051.h>
#include "led.h"
#include "keyboard.h"
#include "lcd.h"
#include "strc51_time.h"


extern char key;

void func_isr(void) __interrupt 3 {
    led_update();
    get_key();
    counter_timer();
}

main (void){    
    
    char t = 0;
    
    initLED();
    init_LCD();
    init_time();
                    
    while (1)
    {
        printOCT(key++);
        clr_scr();
        print_LCD_at('X', t, 0);
        print_LCD_at('Y', t+1, 0);
        print_LCD_at('I', t+2, 0);
        if (++t > 16) t = 0;
        sleep(1);
    }
}
