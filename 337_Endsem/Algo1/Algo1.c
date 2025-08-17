#include <at89c5131.h>
#include "lcd.h"

long unsigned int a,b,a1,b1,a0,b0,c0,c1,c2,c3,c,sec,i,k,counter;
long unsigned int showit[5] = {0,0,0,0,0};
long unsigned int prod[9] = {0,0,0,0,0,0,0,0,0};



void main(){

	k = 0;
	counter = 1;
	
	a = 29851;
	b = 11237;
	
	lcd_init();
	msdelay(4);
	
	//configuring timer
	TMOD = 0x10;
	TH1 = 0x00;
	TL1 = 0x00;
	
	//start
	TR1 = 1;
	
	
	a1 = a/10;
	a0 = a%10;
	b1 = b/10;
	b0 = b%10;
	c0 = a0*b0;
	c1 = a0*b1;
	c2 = a1*b0;
	c3 = a1*b1;
	c = c0 + (c1 + c2)*10 + c3*100;
	
	TR1 = 0;			//stop
	
	sec = (TH1*256 + TL1)/(2);

	//conversion to charr
	
	i = c;
	for(counter = 0; counter<=8; counter++){
  prod[counter]=i%10;
  i=i/10;
	}
	
	
	i = sec;
	for(counter = 1; counter<=5; counter++){
  showit[k]=i%10;
  i=i/10;
  k++;
	}
	
	if(k<4){
	for(counter = 1; counter<=(4-k); counter++){

	showit[k] = 0;
	k++;
	}
	}
	
	lcd_cmd(0x01);
	msdelay(4);
	lcd_cmd(0x80);
	msdelay(4);
	lcd_write_string("Prod1=");
	msdelay(10);
	for (i=0;i<9;i++){
		lcd_write_char(prod[8-i] + 48);
		msdelay(10);
	}
	
	lcd_cmd(0xC0);
	msdelay(10);
	lcd_write_string("Time1=");
	msdelay(10);
	for (i=0;i<k;i++){
		lcd_write_char(showit[4-i] + 48);
		msdelay(10);
	}
	
	while(1);
	
}