#include <at89c5131.h>
#include "lcd.h"

code unsigned char startt[]="  START PROGRAM ";						
code unsigned char input1[]="   FIRST INPUT  ";						
code unsigned char inputnext[]="   NEXT INPUT   ";	
code unsigned char sorting[]="   SORTING..   ";	
code unsigned char completed[]="   COMPLETED   ";	
code unsigned char numbertobe[]="  NUMBER TO BE ";
code unsigned char number[]="     NUMBER     ";
code unsigned char notfound[]="   NOT FOUND"    ;	
code unsigned char searched[]="    SEARCHED   ";	
code unsigned char index[]="  THE INDEX IS  ";	
unsigned char inp[5];
unsigned char disp[] = "0000000000000000";

void main()
{
	int u,v;
	unsigned char ii;
	int found = 0;
	unsigned char search;
	lcd_init();
	
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);	
	P1 = 0x0F;
	lcd_write_string(startt);
	msdelay(5000);
	lcd_cmd(0x80);
	msdelay(4);
	lcd_write_string(input1);
	msdelay(5000);	
	P1 = P1 << 4; 
	inp[0] = P1;
	
	lcd_cmd(0x80);
	msdelay(4);	
	lcd_write_string(inputnext);
	msdelay(5000);
	
	P1 = 0x00;
	msdelay(1000);
	P1 = 0x0F;
	msdelay(4);
	P1 = P1 << 4;
	inp[1] = P1;

	lcd_cmd(0x80);
	msdelay(4);	
	lcd_write_string(inputnext);
	msdelay(5000);

	P1 = 0x00;
	msdelay(1000);
	P1 = 0x0F;
	msdelay(4);
	P1 = P1 << 4;
	inp[2] = P1;

	lcd_cmd(0x80);
	msdelay(4);	
	lcd_write_string(inputnext);
	msdelay(5000);
	
	P1 = 0x00;
	msdelay(1000);
	P1 = 0x0F;
	msdelay(4);
	P1 = P1 << 4;
	inp[3] = P1;
	
	lcd_cmd(0x80);
	msdelay(4);	
	lcd_write_string(inputnext);
	msdelay(5000);	
	
	P1 = 0x00;
	msdelay(1000);
	P1 = 0x0F;
	msdelay(4);
	P1 = P1 << 4;
	inp[4] = P1;

	lcd_cmd(0x80);
	msdelay(4);	
	lcd_write_string(sorting);
	msdelay(5000);
	P1 = 0x00;
	msdelay(1000);
	
	lcd_cmd(0xC0);
	msdelay(4);
	lcd_write_string(completed);
	
	

	for(u = 0; u<4;u++){
		for(v = 0; v<4-u;v++){
				if(inp[v+1] < inp[v]){
				  ii = inp[v+1];
					inp[v+1] = inp[v];
					inp[v] = ii;
			}
		}
	}
	v = 0;
	u = 0;

	
	P1 = inp[0];
	msdelay(5000);
	P1 = 0x00;
	msdelay(1000);
	P1 = inp[1];
	msdelay(5000);
	P1 = 0x00;
	msdelay(1000);
	P1 = inp[2];
	msdelay(5000);
	P1 = 0x00;
	msdelay(1000);
	P1 = inp[3];
	msdelay(5000);
	P1 = 0x00;
	msdelay(1000);
	P1 = inp[4];
	msdelay(5000);
	P1 = 0x00;
	msdelay(1000);

	P1 = 0xFF;
	lcd_cmd(0x80);													
	msdelay(4);
	lcd_write_string(numbertobe);
	lcd_cmd(0xC0);
	msdelay(4);
	lcd_write_string(searched);
	msdelay(5000);
	P1 = P1 << 4;
	search = P1;
	
	P1 = 0x00;
	lcd_cmd(0x01);
	msdelay(1000);
	
	u=0;
	v=0;
	for(u=0;u<5;u++){
	if(inp[u] == search){
	found = 1;
	break;
	}
	}

	if(found == 1){
	u = u+1;
	lcd_cmd(0x80);													
	msdelay(4);
	lcd_write_string(index);
	P1 = u;
	u = u<<4;
	P1 = u;
	//P1 = P1 << 4;
	}
	else{
	P1 = 0xFF;
	lcd_cmd(0x80);													
	msdelay(4);
	lcd_write_string(number);
	lcd_cmd(0xC0);
	msdelay(4);
	lcd_write_string(notfound);
	}
	
	
	while(1);
		
}