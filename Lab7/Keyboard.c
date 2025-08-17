#include <at89c5131.h>
#include "lcd.h"

code unsigned char enterpass[]="Enter Password: ";						
code unsigned char correct[]="Correct Password";			
code unsigned char granted[]="Access Granted";						
code unsigned char denied[]="Access Denied";						
code unsigned char wrong[]="Wrong Password";				
code unsigned char disp[] = "                ";

char key[] = "15A8*D6#";

void main()
{	
	char input[8] = "        ";
	unsigned int a,b;
	unsigned int index = 0;
	int flag = 1;
	lcd_init();
	msdelay(4);
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(enterpass);
	msdelay(4);
	//bits in higher nibble of P3 are rows
	index = 0;
	lcd_cmd(0xC0);
	msdelay(4);

for(index = 0; index < 8; index++){
	
	not_released:	P1 = 0x00;
	P3 = 0x0F;
	P3 = P3 << 4 ;
	a = P3;	//P3| 0xF0;


	if(a == 240){						//11110000(=240 in unsigned int)
		goto pressed;	
	}
	else{
		goto	not_released;
	}
	
	pressed: a = P3;
	if(a == 240){						
		goto pressed;	
	}
	else{
		goto debounce;
	}
	debounce: msdelay(20);
	a = P3;
	if(a == 240){					
		goto not_released;	
	}
	else{
		goto row0;
	}
	


	row0: 
	P3 = 0xEF;											//scanning row 0 (P3.4)
	msdelay(10);
	b = P3;																//lower nibble of b stores entry
	b = b & 0x0F;
	//b = b & 0xFF;
		
	if(b == 0x0E){
		input[index] = 'A';
		b = P3 ;
		goto write;
	}
	else if(b == 0x0D){	
		input[index] = '3';
		b = P3 ;
		goto write;
	}
	else if(b == 0x0B){	
		input[index] = '2';
		b = P3 ;
		goto write;
	}
	else if(b == 0x07){	
		input[index] = '1';
		b = P3 ;
		goto write;
	}


	
	row1: P3 = 0xDF;											//scanning row 0 (P3.4)
	msdelay(10);
	b = P3;																//lower nibble of b stores entry
	b = b & 0x0F;
	//b = b & 0xFF;
		
	if(b == 0x0E){
		input[index] = 'B';
		b = P3 ;
		goto write;
	}
	else if(b == 0x0D){	
		input[index] = '6';
		b = P3 ;
		goto write;
	}
	else if(b == 0x0B){	
		input[index] = '5';
		b = P3 ;
		goto write;
	}
	else if(b == 0x07){	
		input[index] = '4';
		b = P3 ;
		goto write;
	}

	row2: P3 = 0xBF;											//scanning row 0 (P3.4)
	msdelay(10);
	b = P3;																//lower nibble of b stores entry
	b = b & 0x0F;
	//b = b & 0xFF;
		
	if(b == 0x0E){
		input[index] = 'C';
		b = P3 ;
		goto write;
	}
	else if(b == 0x0D){	
		input[index] = '9';
		b = P3 ;
		goto write;
	}
	else if(b == 0x0B){	
		input[index] = '8';
		b = P3 ;
		goto write;
	}
	else if(b == 0x07){	
		input[index] = '7';
		b = P3 ;
		goto write;
	}

	row3: P3 = 0x7F;											//scanning row 0 (P3.4)
	msdelay(10);
	b = P3;																//lower nibble of b stores entry
	b = b & 0x0F;
	//b = b & 0xFF;
		
	if(b == 0x0E){
		input[index] = 'D';
		b = P3 ;
		goto write;
	}
	else if(b == 0x0D){	
		input[index] = '#';
		b = P3 ;
		goto write;
	}
	else if(b == 0x0B){	
		input[index] = '0';
		b = P3 ;
		goto write;
	}
	else if(b == 0x07){	
		input[index] = '*';
		b = P3 ;
		goto write;
	}
	
	index--;
	goto next;
	
	write: lcd_write_char(input[index]);
	next: msdelay(4);
	
	
}

	for(index = 0; index < 8; index++){
		if(input[index] != key[index]){
			flag = 0;
			goto notmatch;
		}
	}
	
	lcd_cmd(0x01);
	msdelay(4);
	lcd_cmd(0x80);
	msdelay(4);
	lcd_write_string(correct);
	msdelay(4);
	lcd_cmd(0xC0);
	msdelay(4);
	lcd_write_string(granted);
	msdelay(4);
	goto endd;
	
	notmatch: lcd_cmd(0x01);
	msdelay(4);
	lcd_cmd(0x80);
	msdelay(4);
	lcd_write_string(wrong);
	msdelay(4);
	lcd_cmd(0xC0);
	msdelay(4);
	lcd_write_string(denied);
	msdelay(4);
	endd: while(1);
		
}