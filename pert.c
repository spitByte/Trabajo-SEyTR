/* Este código genera las perturbaciones aleatorias
Las perturbaciones lineales varían entre -5 y 5 metros para el eje X
Las perturbaciones lineales varían entre -2.5 y 2.51 metros para el eje Y

Para crear valores positivos y negativos aleatoriamente, se escoge (por ejemplo) como criterio que 
si la cantidad (((float)rand() / RAND_MAX) * limX) es mayor que una cantidad cualquiera entre 0 y 1, el número es positivo, de lo contrario, el número será negativo. */

/* Como resultado de ejecutar el código, se obtiene el vector 
pert[2], que es el vector que contiene las perturbaciones que sufre la base.*/

#include "pert.h"


void generatePert(float limX_Pert,float limY_Pert, float*pert){

	int i;
	for ( i = 0; i<2; i++){
		float randVal = (float)rand()/RAND_MAX;
		if (i == 0){
			pert[i] = (randVal < 0.5 ? 1:-1)*randVal*limX_Pert;
		}else{
			pert[i] = (randVal < 0.5 ? 1:-1)*randVal*limY_Pert;
		}
	}
};