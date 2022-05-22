/*
 * lcd_avr.c
 *
 * Created: 19/05/2022 06:36:30
 *  Author: Vland
 */ 

#include "lcd_avr.h"

void LCD_Init(void){
	
	LCD_Data(0x00);
	_delay_ms(30);
	_delay_us(500);
	LCD_Comand(0x03);
	_delay_ms(5);
	LCD_Comand(0x03);
	_delay_us(150);
	LCD_Comand(0x03);
	LCD_Comand(0x02);
	LCD_Comand(0x02);
	LCD_Comand(0x08);
	LCD_Comand(0x00);
	LCD_Comand(0x0C);
	LCD_Comand(0x00);
	LCD_Comand(0x06);
	
}


void LCD_Data(unsigned char Data){
	
	if(Data & 1)
	LCD_DATA|=(1<<D4);
	else
	LCD_DATA&=~(1<<D4);
	if(Data & 2)
	LCD_DATA|=(1<<D5);
	else
	LCD_DATA&=~(1<<D5);
	if(Data & 4)
	LCD_DATA|=(1<<D6);
	else
	LCD_DATA&=~(1<<D6);
	if(Data & 8)
	LCD_DATA|=(1<<D7);
	else
	LCD_DATA&=~(1<<D7);
}



void LCD_Comand(unsigned char cmd){
	
	LCD_CONTROL&=~(1<<RS_pin);
	LCD_Data(cmd);
	LCD_CONTROL|=(1<<E_pin);
	_delay_us(500);
	LCD_CONTROL&=~(1<<E_pin);

}


void LCD_Caracter(unsigned char data){
	
	char Low4,High4;
	Low4=data & 0x0F;
	High4=data & 0xF0;
	LCD_CONTROL|=(1<<RS_pin);
	LCD_Data(High4>>4);
	LCD_CONTROL|=(1<<E_pin);
	_delay_us(500);
	LCD_CONTROL&=~(1<<E_pin);
	_delay_us(500);
	LCD_Data(Low4);
	LCD_CONTROL|=(1<<E_pin);
	_delay_us(500);
	LCD_CONTROL&=~(1<<E_pin);
	_delay_us(500);
}

void LCD_String(const char *caden){
	
	while(*caden)
	LCD_Caracter(*caden++);
	
}

void Set_Cursor(unsigned char x,unsigned char y){

	unsigned char Temp,Low4,High4;
	
	if(x==1){
		
		Temp=0x80+y-1;
		High4=Temp>>4;
		Low4=Temp&0x0F;
		LCD_Comand(High4);
		LCD_Comand(Low4);
		
	}
	
	if(x==2){
		
		Temp=0xC0+y-1;
		High4=Temp>>4;
		Low4=Temp&0x0F;
		LCD_Comand(High4);
		LCD_Comand(Low4);
		
	}

}

void LCD_clear(void){
	LCD_Comand(0);
	LCD_Comand(1);

}