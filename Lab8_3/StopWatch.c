#include <at89c5131.h>
#include "lcd.h"

sbit inpin=P3^4;




//Main function
void main(void)
{	
	int i = 0;
	int k = 0;
	unsigned int min = 0;
	unsigned int sec = 0;
	int showit[4] = {0,0,0,0};
		
	P1_0 = 1;
	lcd_init();
	msdelay(4);
	
	TMOD = 0x05; //mode 1 timer 0 and for timer 1

	
	TH0 = 0x00;  //Values for Timer 0 TH0
	TL0 = 0x00;  //Values for Timer 0 TL0

	while(1){
		if(P1_0 == 1){
			TR0 = 1;
			goto outt;
		}
	}

	outt: while(1){
		if(P1_0 == 0){
			TR0 = 0;
			goto display;
		}
	}
	display: sec = (TH0*256 + TL0)/(10*6); 
	min = sec / 60;
	sec = sec % 60;
	i = sec;
	while(i>0){
  showit[k]=i%10;
  i=i/10;
  k++;
	}
	
	if(k == 1){
		k++;
	}
	
	i = min;
	while(i>0){
  showit[k]=i%10;
  i=i/10;
  k++;
	}	
	
	k--;
	for (i=3;i>=2;i--){
		lcd_write_char(showit[i] + 48);
		msdelay(10);
	}
	lcd_write_char(':');
	for (i=1;i>=0;i--){
		lcd_write_char(showit[i] + 48);
		msdelay(10);
	}
	
	while(1);
}