/*
 * pid.h
 *
 * Created: 19/05/2022 00:16:28
 *  Author: Vland
 */ 


#ifndef PID_H_
#define PID_H_




typedef struct{

	//Costantes del pid
	float Kp;
	float Ki;
	float Kd;
	//Limites del Control
	float LimMax;
	float LimMin;
	//Tiempo de muestreo
	float ts;
	//Variables del controlador
	float integrador;
	float integradorAnterior;
	float errorAnterior;
	float derivador;
	

	//Señal de control
	float uT;

}ControladorPID;

void ControladorPID_init(ControladorPID*pid);


float CalculoControlPID(ControladorPID*pid,float referencia,float medicion);





#endif /* PID_H_ */