/* Este código genera el error resultado del bucle cerrado.
Se obtiene restando el valor request o visualT de real 
El resultado de este código es el vector error[2]*/

#include "error.h"


void generateError(float *request, float *visualT,float *real,float *error){
    int i;
    for (i = 0; i < 2; i++){
        error[i] = fabs((request[i] == 0 ? visualT[i]:request[i])) - fabs(real[i]);
    }
}