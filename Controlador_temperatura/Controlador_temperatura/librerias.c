/*
 * librerias.c
 *
 * Created: 20/04/2022 11:25:03
 *  Author: Vland
 */ 

#include "librerias.h"

 
void ADC_init(void){
	
	//ADC VREF: VCC-> 5V del MCU
	ADMUX &= ~(1<<REFS1);
	ADMUX |= (1<<REFS0);
	//Conversión justificada a la derecha
	ADMUX &= ~(1<<ADLAR);
	//Inicializamos el ADC apagado
	ADMUX &= ~(1<<ADLAR);
	//Desabilitamos el auto trigger
	ADCSRA &= ~(1<<ADATE);
	//Preescaler de 128
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	//Desabilitamos el buffer de entrada digital
	DIDR0 = 0xFF;

}

float Analogic_Read(uint8_t adc_channel){

	//Seleccion del canal analogico
	ADMUX = ( (ADMUX & 0xF0) | (0x0F & adc_channel) );
	//Inicia la conversión
	ADCSRA |= (1<<ADEN)|(1<<ADSC);
	//Esperamos que la conversión finalice.
	while((ADCSRA & (1<<ADSC))!=0);
	//Apagamos el ADC
	ADCSRA &= ~(1<<ADEN);
	return ADC;
}

/////////////////////////////////////////////

void Usart_Init(void){
	
	//Usart en modo asincrono->uart
	UCSR0C &=~(1<<UMSEL00);
	UCSR0C &=~(1<<UMSEL01);
	//Desactivando Paridad
	UCSR0C &=~ (1<<UPM00);
	UCSR0C &=~ (1<<UPM01);
	//Bits de parada->1
	UCSR0C &=~ (1<<USBS0);
	//Transmisión de 8 bits
	UCSR0C |=  (1<<UCSZ00);
	UCSR0C |=  (1<<UCSZ01);
	UCSR0B &=~ (1<<UCSZ02);
	//Modo doble velocidad
	UCSR0A |= (1<<U2X0);
	//Calculo para 9600 baudios
	UBRR0 = (F_CPU/8/9600) - 1;
	//Habilitamos transmisión y recepción
	UCSR0B |= (1<<TXEN0);
	UCSR0B |= (1<<RXEN0);
	//Habilitamos interrupción->recepción
	UCSR0B |= (1<<RXCIE0);
}

void Usart_PutChar(char ch){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0=ch;
}

void Usart_PutString(const char *str){
	
	while(*str)
	Usart_PutChar(*str++);
}

////////////////////////////////////////////

void PWM_init(void){
	//PIN PD6->Salida(0C0A)
	DDRD |=(1<<DDD6);
	//Modo -> Fast PWM
	TCCR0A = (1<<WGM00) | (1<<WGM01);
	//Modo -> No invertido
	TCCR0A |= (1<<COM0A1);
	//Clock -> Preescaler(1024)
	TCCR0B = (1<<CS00) | (1<<CS02);
	
}

void PWM_set_duty(uint8_t duty){
	
	OCR0A = (255*duty)/100;
}

///////////////////////////////////////////

void Timer_init(void){
	
	//Habilita interrupcion
	TIMSK1 |= (1<<TOIE1);
	/*TCNT1 = 65536 - (tiempo*clock)/preescaler
	  TCNT1 = 65536 - (100ms*8MHz)/256
	*/
	TCNT1 = 62411;
	//Preescaler->256
	TCCR1B |= (1<<CS12);
	
}

///////////////////////////////////////////////////////////////////////////////////////////

void configure_interrup_cero(void){
	
	//Pin de interrupción como entrada
	DDRD &= ~(1<<DDD2);
	//Modo flanco de subida
	EICRA |= (1<<ISC00) | (1<<ISC01);
	//Habilitamos la interrupcion INT0
	EIMSK |= (1<<INT0);
	
}

void configure_interrup_one(void){
	
	//Pin de interrupción como entrada
	DDRD &= ~(1<<DDD3);
	//Modo flanco de subida
	EICRA |= (1<<ISC11) | (1<<ISC10);
	EICRA &= ~(1<<ISC10);
	//Habilitamos la interrupcion INT1
	EIMSK |= (1<<INT1);
}