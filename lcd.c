#include <8051.h>
#include "lcd.h"
#include "strc51_time.h"

static const char E = 0x08;
static const char RS = 0x04;

#define GET_OCTET(x,n) ((x & (0xF << 4*n)) >> (4*n)))

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


static void print_LCD_at(char c, char x, char y) {
    set_cursor_pos(x,y);
    print_LCD(c);
}


void LcdClrScr() {
    send_cmd(0x01);
    msleep(3);
}


void ShowProgressTriangle(char idx) {
    print_LCD_at(idx%8, idx, idx < 8 ? 1 : 0);
    if (idx >= 8) print_LCD_at(7, idx, 1);
    msleep(1);
}

static char octet_to_hex_char(char x) {
    if (x < 10) {
        return '0' + x;
    }
    
    if (x >= 0xA && x <= 0xF) {
        return 'A' + (x-10);
    }
    
    return '-';
}

void LcdPrintHex16(unsigned int x) {
    print_LCD('0');
    msleep(1);
    print_LCD('x');
    msleep(1);
    print_LCD(octet_to_hex_char(GET_OCTET(x,3));
    msleep(1);
    print_LCD(octet_to_hex_char(GET_OCTET(x,2));
    msleep(1);
    print_LCD(octet_to_hex_char(GET_OCTET(x,1));
    msleep(1);
    print_LCD(octet_to_hex_char(GET_OCTET(x,0));
    msleep(1);
}

static void init_triangle() {
    char i = 0;
    char j = 0;
    
    for (j = 0; j < 8; ++j) {
        send_cmd(0x40 | (j*8));
        msleep(2);
        for (i = 0; i < 8; ++i) {
            print_LCD(j >= 7-i ? 0x1F : 0x00);
            msleep(1);
        }
    }
}

void LcdInit()
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
    
    init_triangle();
}
