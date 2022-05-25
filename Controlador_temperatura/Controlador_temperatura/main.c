/*
 * Controlador_temperatura.c
 *
 * Created: 19/04/2022 18:20:12
 * Author : Vland
 */ 

#include "librerias.h"
#include "pid.h"
#include "lcd_avr.h"
#include <avr/interrupt.h>


/********MACROS********/
#define PID_KP  0.37558
#define PID_KI  0.04983
#define PID_KD  0.0
#define PID_LIM_MIN  0.0
#define PID_LIM_MAX  100.0
#define TMUESTREO 0.1
/***********************/

//Recepcion Serial
char serial_buffer[10];
char serial_data_recieve[10];

//Envio Serial
char serial_data[20];


char temperatura_str[20];
char setpoint_str[20];
float temperatura = 0;
float U = 0;

//Temperatura de referencia(Colocar entre 50 y 400)
float referencia = 400;


//Inicia estructura
ControladorPID PIDmotor={PID_KP, PID_KI, PID_KD,PID_LIM_MAX,PID_LIM_MIN,TMUESTREO};


int main(void){

	cli();
	//Puerto B-> Salida
	DDRB = 0xFF;
	//Inicia el controlador
	ControladorPID_init(&PIDmotor);
	//Inicia Timer(Modo normal) -> 100ms(Tmuestreo)
	Timer_init();
	//Inicia ADC
	ADC_init();
	//Inicia Usart-> 9600
	Usart_Init();
	//Inicia PWM
	PWM_init();
	//Inicia LCD
	LCD_Init();
	LCD_clear();
	//Incia Interrupcion externa
	configure_interrup_cero();
	configure_interrup_one();
	
	sei();
	
    while (1) 
    {	
		 //Lee la temperatura	
		 temperatura = Analogic_Read(ADC0D)*500.0/1024.0;
		 //Convierte a cadena
		 sprintf(setpoint_str,"SetPoint: %.0f\r ",referencia); 
		 sprintf(temperatura_str,"T: %.0f\r     ",temperatura);
		 
		 Set_Cursor(1,1);
		 LCD_String(setpoint_str);
		 Set_Cursor(2,1);
		 LCD_String(temperatura_str);
    }
}

//Tiempo de muestreo
ISR(TIMER1_OVF_vect){
	
	//Calcula la señal de control
	U = CalculoControlPID(&PIDmotor,referencia,temperatura);
	//Establece el PWM
	PWM_set_duty((uint8_t)U);
	//Envia por el puerto serial
	sprintf(serial_data,"%.0f-%.0f-%.0f\n",temperatura,U,referencia);
	Usart_PutString(serial_data);
	
	//Resetea el timer
	TCNT1 = 62411;
}

ISR(INT0_vect){
	
	if (referencia>=400){
		referencia = 400;
	}else{
		referencia+=10;
	}
}

ISR(INT1_vect){
	
	if (referencia<=50){
		referencia = 50;
		}else{
		referencia-=10;
	}
}

ISR(USART_RX_vect){

	if (Usart_ReadLine(serial_buffer,serial_data_recieve)){
		
		referencia = (float)(atoi(serial_data_recieve));
		
	}
}
