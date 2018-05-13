#ifndef LCD_H
#define LCD_H

void print_LCD(unsigned char c);
void init_LCD();
void set_cursor_pos(char x, char y);
void print_LCD_at(char c, char x, char y);

#endif /* LCD_H */
