/* Uladzislau Harbuz, Yakymyshyn Maksym
 * sdcc 3.6.0 Linux throw USB to RS232 converter
 */

#include "defines.h"
#include <8051.h>
#include "strc51_time.h"
#include "sort.h"

#define MAX_ARRAY_SIZE 1024

void func_isr(void) __interrupt 3 {
    counter_timer();
}

static void init()
{
    SCON = 0x50;
    TMOD &= 0x0F;
    TMOD |= 0x20;
    TH1 = TL1 = 253;
    TCON = 0x40;
    PCON = 0x80;
}

static char getchar()
{
    while(!RI);
    RI = 0;
    return SBUF;
}

static void putchar(char c)
{
    while(!TI);
    SBUF = c;
    TI=0;
}

static int size = 0;
__xdata static uint8_t array1[MAX_ARRAY_SIZE];
__xdata static uint8_t array2[MAX_ARRAY_SIZE];

static void read_array() {
    uint8_t i = 0;
    size = (uint8_t)getchar();
    getchar(); // ignore space
    if (size > MAX_ARRAY_SIZE) return;

    while (i < size) {
        array1[i] = (uint8_t)getchar();
        array2[i] = array1[i];
        getchar(); //ignore next space;
    }
}

static void print_array(uint8_t* a, uint8_t size) {
    uint8_t i = 0;
    putchar(size);
    putchar(' ');

    while (i < size) {
        putchar(a[i]);
        putchar(' ');
        msleep(5);
    }
}

static void unsafe_put_str_ln(char* str) {
    while (*str != '\n') {
        putchar(*str++);
        msleep(5);
    }
}

main (void) {  
    while (1) {
        uint8_t i = 0;
        uint8_t x = 0;

        struct time tm = {0};
        struct time tmtmp = {0};
        struct time print_time = {0};
   
        init();
        init_time();

        read_array();
        gettime(&tm);
        gettime(&tmtmp);
        bubble_sort(array1, size);
        diff_time(&tmtmp, &tm, &print_time);

        unsafe_put_str_ln("bubble sort: ");
        print_array(array1, size);
        unsafe_put_str_ln("time:");
        putchar(print_time.msecs);
        unsafe_put_str_ln(" ms.");

        sleep(5);
   
        gettime(&tm);
        gettime(&tmtmp);
        insert_sort(array2, size);
        diff_time(&tmtmp, &tm, &print_time);

        unsafe_put_str_ln("insertion sort: ");
        print_array(array1, size);
        unsafe_put_str_ln("time:");
        putchar(print_time.msecs);
        unsafe_put_str_ln(" ms.");
    }
}
