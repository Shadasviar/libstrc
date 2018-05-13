#include "strc51_time.h"
#include <8051.h>

static long posixtime = 0;

/* Used only for msleep because it can store max 10 minuts.*/
static long milliseconds = 0;

/* Hz */
static const long cnt_freq = 3640;


void msleep(int n) {
    long targettime = milliseconds + n;
    while(milliseconds < targettime) __asm__("nop");
}

/* sleep in seconds */
void sleep(int n) {
    long targettime = posixtime + n;
    while(posixtime < targettime) __asm__("nop");
}

void init_time() {
    TMOD &= 0x0F;
    TMOD |= 0x20; 
    IE = 0x88;
}

void counter_timer() {
    static int t = 0;
    static char mt = 0;
    
    if (++mt > 3) {
        mt = 0;
        ++milliseconds;
    }
    
    if (++t >= cnt_freq) {
        ++posixtime;
        t = 0;
    }
}
