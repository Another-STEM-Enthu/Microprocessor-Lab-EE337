#include <at89c5131.h>
#include "lcd.h"

code unsigned char startt[]="  START PROGRAM ";						
code unsigned char input1[]="   FIRST INPUT  ";						
code unsigned char inputnext[]="   NEXT INPUT   ";						

void main()
{
	lcd_init();
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);	
	P1 = 0x00H;
	msdelay(4);
	lcd_write_string(startt);
	msdelay(5000);
	
	Acc = P1;
	P1.7 = Acc[7];
	P1.6 = Acc[6];
	P1.5 = Acc[5];
	P1.4 = Acc[4];

	lcd_cmd(0xC0);													//Move cursor to 2nd line of LCD
	msdelay(4);
	lcd_write_string(display_msg2);
	while(1);
		
}