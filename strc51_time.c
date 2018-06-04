#include "defines.h"
#include "strc51_time.h"
#include <8051.h>

static volatile long posixtime = 0;

/* Used only for msleep because it can store max 10 minuts.*/
static volatile int milliseconds = 0;
static volatile int mcounter = 0;

/* Hz */
static const long cnt_freq = 3640;


void msleep(int n) {
    mcounter = 0;
    while(mcounter < n) __asm__(nop);
}

/* sleep in seconds */
void sleep(int n) {
    long targettime = posixtime + n;
    while(posixtime < targettime) __asm__(nop);
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
        ++mcounter;
    }
    
    if (++t >= cnt_freq) {
        ++posixtime;
        milliseconds = 0;
        t = 0;
    }
    
}

int getmsecs() {
    return milliseconds;
}

long getsecs() {
    return posixtime;
}

void gettime(struct time *out) {
    out->secs = posixtime;
    out->msecs = milliseconds;
}

/* Return 1 if a > b, 0 if a == b, -1 if a < b */
int cmp_time(struct time *a, struct time *b) {
    if (a->secs == b->secs) {
        if (a->msecs < b->msecs) return -1;
        if (a->msecs > b->msecs) return 1;
        return 0;
    }
    if (a->secs < b->secs) return -1;
    return 1;
}

void diff_time(struct time *a, struct time *b, struct time *out) {
    out->secs = a->secs - b->secs;
    out->msecs = a->msecs - b->msecs;
}
