#ifndef LCD_H
#define LCD_H

void LcdInit();
void LcdClrScr();
void ShowProgressTriangle(char idx);
void LcdPrintHex16(unsigned int x);

void set_cursor_pos(char x, char y);
void print_LCD(unsigned char data);

#endif /* LCD_H */
