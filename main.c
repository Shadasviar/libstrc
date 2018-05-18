/* Uladzislau Harbuz, Yakymyshyn Maksym
 * sdcc 3.6.0 Linux throw USB to RS232 converter
 */

#include <stdlib.h>
#include <8051.h>
#include "strc51_time.h"
#include "lcd.h"
#include "led.h"
#include "keyboard.h"


void func_isr(void) __interrupt 3 {
    counter_timer();
    scan_keyboard();
    led_update();
}

main (void) {    
   
    char key = 0;
    struct time tm = {0};
    struct time tmtmp = {0};
    struct time print_time = {0};
    
    initLED();
    LcdInit();
    init_time();
    LcdClrScr();
    
    while (1) {
        printOCT(key);
        
        if (key != get_key()) {
            key = get_key();
            
            set_cursor_pos(0,0);
            gettime(&tmtmp);
            diff_time(&tmtmp, &tm, &print_time);
            LcdPrintHex16((int)print_time.secs);
            print_LCD('.');
            LcdPrintHex16(print_time.msecs);
            
            gettime(&tm);
        }
        
        set_cursor_pos(0,1);
        gettime(&tmtmp);
        diff_time(&tmtmp, &tm, &print_time);
        LcdPrintHex16((int)print_time.secs);
        print_LCD('.');
        LcdPrintHex16(print_time.msecs);
        msleep(1);
    }
}
