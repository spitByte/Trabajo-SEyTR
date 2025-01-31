/* Este archivo representa la planta del sistema. Toma como entrada las coordenadas del punto que se pretende seguir en 
el plano (resultado de las coordenadas deseadas más la perturbación). 
La salida es la posición real a la que apunta el objetivo, que se supone tomada de una serie de sensores sitaudos en los 
actuadores.
Para simular la acción de ajuste del motor, se hará que el valor de las coordenadas reales difieran siempre un 3% del las
coordenadas que entran como inputs a la planta, simulando así el seguimiento del objetivo.

El resultado de este archivo es el vector real[2], que recoje las coordenadas reales del punto al que apunta el objetivo*/

#include "motor.h"


void generateInput (float *request, float *visualT,float *pert, float *input){
    int i;
    for (i = 0; i < 2; i++){
        input[i] = (request[i] == 0 ? visualT[i] : request[i]) + pert[i];
    }
    
}

void generateOutput(float *input, float *real){
    int i;
    for (i = 0; i < 2; i++){
        real[i] = 0.97*input[i];
    }
    
}