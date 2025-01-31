/*Este código genera las coordenas del plano XY a las que se desea que apunte el objetivo.
En el contexto del proyecto, estas coordenadas se corresponden al seguimiento de un cuerpo móvil 
cuyas coordenadas son obtenidas a partir de técnicas de seguimiento visual. 
Aquí serán generads aleatoriamente.
Se considera un plano a una distancia de 10m, la zona de rastreo queda recogida en un rectángulo de 
20mx5m.*/

/*Para crear valores positivos y negativos aleatoriamente, se escoge (por ejemplo) como criterio que 
si la cantidad (((float)rand() / RAND_MAX) * limX) es mayor que una cantidad cualquiera entre 0 y 1, el número es positivo, de lo contrario, el número será negativo. */

/*El resultado de ejecutar este código es el vector visualT[2], sus componentes son las coordenadas (X,Y) del punto que
se pretende seguir*/


#include "visualTrack.h"


void generateVisualTrack(float limX_Track,float limY_Track,float *visualT){
    int i;
    for (i = 0;i<2;i++){
        float randVal = (float)rand()/RAND_MAX;
        if (i == 0){
            visualT[i] = (randVal < 0.5 ? 1:-1)*randVal*limX_Track;
        }else{
            visualT[i] = (randVal < 0.5 ? 1:-1)*randVal*limY_Track;
        }
    }

};