/*
 * lcd_avr.h
 *
 * Created: 19/05/2022 06:36:15
 *  Author: Vland
 */ 


#ifndef LCD_AVR_H_
#define LCD_AVR_H_

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define LCD_DATA PORTB
#define LCD_CONTROL PORTB
#define RS_pin 4 
#define E_pin 5
#define D4 0
#define D5 1
#define D6 2
#define D7 3


void LCD_Init(void);
void LCD_Comand(unsigned char cmd);
void LCD_Caracter(unsigned char data);
void LCD_Data(unsigned char Data);
void LCD_String(const char *caden);
void Set_Cursor(unsigned char x,unsigned char y);
void LCD_clear(void);



#endif /* LCD_AVR_H_ */