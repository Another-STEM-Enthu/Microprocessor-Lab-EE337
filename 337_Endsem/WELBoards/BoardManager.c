/**********************************************************
EE337: ADC IC MCP3008 interfacing with pt-51
(1) Complete spi_init() function from spi.h 

***********************************************************/

#include <at89c5131.h>
#include "lcd.h"																				//Driver for interfacing lcd 
#include "serial.c"		

char adc_ip_data_ascii[6]={0,0,0,0,0,'\0'};							//string array for saving ascii of input sample
code unsigned char menu[]="Press I for Issue and R for Return";								//Display msg on 2nd line of lcd
unsigned char status[30]="8051-8 TIVA-6 AT328-4 STM32-4";						//Display msg on 1st line of lcd
int quantity[5] = {0,8,6,4,4};
int quantity_max[5] = {0,8,6,4,4};



void main(void)
{

	int j=0;
	unsigned char inputt,index,number_borrow,number_return;
  lcd_init();
	uart_init();
	
	

		 
		
		lcd_cmd(0x80);																			//Move cursor to first line
		lcd_write_string("Received Bits:");											//Display "Volt: " on first line of lcd
		
	
while(1){		
		transmit_string("\r\n");

		//to correctly display the #available boards
		status[5] = quantity[1] + 48;
		status[12] = quantity[2] + 48;
		status[20] = quantity[3] + 48;
		status[28] = quantity[4] + 48;

	
		transmit_string(status);
		transmit_string("\r\n");
	
		transmit_string(menu);
		transmit_string("\r\n");
	
		
		lcd_cmd(0xC0);
		msdelay(4);
		
		while(1){
		inputt = receive_char();
		transmit_string("\r\n");
		lcd_cmd(0xC0);
		msdelay(4);
		lcd_write_char(inputt);
		msdelay(10);
		goto outt;
		}
		
		outt: if(inputt =='I' | inputt == 'i'){
		transmit_string("Enter micro-controller to be borrowed:");
		transmit_string("\r\n");
			
		while(1){
		index = receive_char();
		transmit_string("\r\n");
		lcd_cmd(0xC0);
		msdelay(4);
		lcd_write_char(inputt);
		msdelay(10);
		goto borrow;
		}
		
		borrow: transmit_string("Enter Quantity:");
		transmit_string("\r\n");
		
		while(1){
		number_borrow = receive_char();
		transmit_string("\r\n");
		lcd_cmd(0xC0);
		msdelay(4);
		lcd_write_char(inputt);
		msdelay(10);
		goto process_borrow;
		}
		
		process_borrow: 
			if((number_borrow- 48) <= quantity[index-48]){
				quantity[index-48] = quantity[index-48] - (number_borrow - 48);
				transmit_string("Requested micro-controller allocated!");
				transmit_string("\r\n");
			}
			else{
			  transmit_string("Requested micro-controller not available...");
				transmit_string("\r\n");
			}


		
		}//ending issue if


		
		
		
		
		
		
		
		
		
		
	  if(inputt =='R' | inputt == 'r'){
			transmit_string("Enter micro-controller to be returned:");
			transmit_string("\r\n");
		
			while(1){
			index = receive_char();
			transmit_string("\r\n");
			lcd_cmd(0xC0);
			msdelay(4);
			lcd_write_char(inputt);
			msdelay(10);
			goto returnn;
			}
			
			returnn: if(quantity[index-48] == quantity_max[index-48]){
			transmit_string("You can’t return what you don’t have...");
			transmit_string("\r\n");
			} //ending not possible to return wala if
			
			else{
			transmit_string("Enter Quantity:");
			transmit_string("\r\n");
			while(1){
			number_return = receive_char();
			transmit_string("\r\n");
			lcd_cmd(0xC0);
			msdelay(4);
			lcd_write_char(inputt);
			msdelay(10);
			goto process_return;
			}
			
			process_return: 
			if((number_return - 48) + (quantity[index-48]) <= quantity_max[index-48]){
			transmit_string("Returned micro-controller received!");
			transmit_string("\r\n");	
			quantity[index-48] = quantity[index-48] + (number_return-48);
			}
			else{
			transmit_string("Returned micro-controller out of bounds...");
			transmit_string("\r\n");				
			}
			
			}	//ending possible to return wala else
		
		}//ending return if
		
		
		
	
		
		
		
		
		
} //ending while(1)
 		
while(1);
}

