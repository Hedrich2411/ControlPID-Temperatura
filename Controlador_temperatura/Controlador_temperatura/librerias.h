/*
 * librerias.h
 *
 * Created: 20/04/2022 11:25:34
 *  Author: Vland
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#define F_CPU 8000000UL
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

void Usart_Init(void);
void Usart_PutChar(char ch);
void Usart_PutString(const char *str);

void ADC_init(void);
float Analogic_Read(uint8_t adc_channel);

void PWM_init(void);
void PWM_set_duty(uint8_t duty);

void Timer_init(void);

void configure_interrup_cero(void);
void configure_interrup_one(void);

#endif /* INCFILE1_H_ */