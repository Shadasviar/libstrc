#include <8051.h>
#include "lcd.h"
#include "strc51_time.h"

__xdata __at 0x8000 unsigned char U12;

static char E = 0x08;
static char RS = 0x04;


static void send_cmd_8(unsigned char cmd)
{
    P1=cmd;
    P1=cmd | E;
    P1=cmd & !E;
}

static void send_cmd(unsigned char cmd)
{
    P1=cmd & 0xf0;
    P1=(cmd & 0xf0) | E; 
    P1=(cmd & 0xf0) & !E;
    P1=(cmd << 4) & 0xf0; 
    P1=((cmd << 4) & 0xf0) | E;
    P1=((cmd << 4) & 0xf0) & !E;
}

void print_LCD(unsigned char data)
{
    P1=(data & 0xf0) | RS;
    P1=((data & 0xf0) | E) | RS;
    P1=((data & 0xf0) & !E) | RS;
    P1=((data << 4) & 0xf0) | RS;
    P1=(((data << 4) & 0xf0) | E) | RS;
    P1=(((data << 4) & 0xf0) & !E) | RS;
}

void set_cursor_pos(char x, char y) {
    char i = y == 0 ? 0x80 : 0xC0;
    i |= x;
    send_cmd(i);
    msleep(2);
}


void print_LCD_at(char c, char x, char y) {
    set_cursor_pos(x,y);
    print_LCD(c);
}


void clr_scr() {
    send_cmd(0x01);
    msleep(3);
}


void init_LCD()
{
    SCON = 0x50;
    TMOD &= 0x0F;
    TMOD |= 0x20; 
    TH1 = TL1 = 253;
    TCON = 0x40;
    PCON = 0x80;
    IE =    0x88;

    msleep(15);
    send_cmd_8(0x30);
    msleep(5);
    send_cmd_8(0x30);
    msleep(1);
    send_cmd_8(0x30);
    msleep(5);
    send_cmd_8(0x20);
    msleep(1);
    send_cmd(0x2C);
    msleep(1);
    send_cmd(0x08);
    msleep(1);
    send_cmd(0x0C);
    msleep(1);
    send_cmd(0x06);
    msleep(1);
    send_cmd(0x14);
    msleep(1);
}
