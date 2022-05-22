# CONTROLADOR DE TEMPERATURA

### Calculo de la respuesta del sistema
Pero en el proceso de identificación queremos ver el comportamiento del horno en una región por lo que solo energizaremos con el 16.6% o 2VDC.

![](https://github.com/Hedrich2411/ControlPID-Temperatura/blob/master/img/respuesta_horno.png)

La grafica de respuesta que se obtiene desde Proteus es :

![](https://github.com/Hedrich2411/ControlPID-Temperatura/blob/master/img/grafica_horno.png)

### Importando datos a Matlab

Desde Proteus podemos exportar los datos y pasarlos a Matlab para la identificacion del sistema.

![](https://github.com/Hedrich2411/ControlPID-Temperatura/blob/master/img/datos_horno.PNG)

### Identifiación del sistema

Con la herramienta PID tunner podemos importar los datos de salida y estimar el modelo de la planta.

![](https://github.com/Hedrich2411/ControlPID-Temperatura/blob/master/img/identificacion_horno.PNG)

Los parámetros son los siguientes :

![](https://github.com/Hedrich2411/ControlPID-Temperatura/blob/master/img/Parametros_horno.PNG)

### Sintonización del controlador

Procedemos a importar el modelo y sintonizar el controlador para el calculo de las constantes del PID(kp,Ki y Kd)

![](https://github.com/Hedrich2411/ControlPID-Temperatura/blob/master/img/sintonizacion_horno.PNG)

Con estos calculos ya podemos implementar el controlador PID de temperatura en un microcontrolador.

### Resultados

Se esta utilizando un microcontrolador Atmega328p para la simulacion, asi como Node-Red para la interfaz de control del SetPoint.

![](https://github.com/Hedrich2411/ControlPID-Temperatura/blob/master/img/Funcionamiento_proteus.PNG)

El esquema de nodos en Node-red :

![](https://github.com/Hedrich2411/ControlPID-Temperatura/blob/master/img/Bloques_NodeRed.png)

La dashboard encargada del monitoreo y control de la planta : 

![](https://github.com/Hedrich2411/ControlPID-Temperatura/blob/master/img/Interfaz_nodered.png)

### Recomendaciones

- Se recomienda poner SetPoint mayores de 50ºC ya que la temperatura ambiental es de 27ºC y el funcionamiento se vera alterado al colocar la referencia por debajo de los 30 ºC
- De la misma manera si la temperatura es mayor a los 500 ºC estaria mandando un voltaje mayor a 5V al canal del ADC del microcontrolador y asi alterando el funcionamiento, por lo que se recomienda como maximo 400 ºC.
- El sistema ya esta acondicionado para trabajar en el rango de (50-400)ºC.