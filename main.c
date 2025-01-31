/*El flujo de trabajo del código comienza con la generación de datos en visualTrack.c,
donde se crean coordenadas aleatorias del objetivo dentro de un área predefinida.
Estas coordenadas representan el punto que la cámara debe rastrear. Simultáneamente,
pert.c introduce perturbaciones aleatorias para simular las condiciones inestables del entorno.

Cuando el sistema está en funcionamiento normal, la posición deseada proviene de visualTrack.c,
y el control de la cámara se ajusta automáticamente para minimizar la diferencia entre la posición real y la deseada.
Sin embargo, en cualquier momento, el usuario puede interrumpir el seguimiento automático
e ingresar manualmente nuevas coordenadas, lo que convierte el sistema en un sistema en tiempo real.

Para gestionar la entrada manual, se emplea un semáforo binario. Un task separado monitorea constantemente 
la entrada del teclado y, cuando el usuario presiona la tecla espacio, el semáforo es liberado. 
La tarea encargada de recibir las coordenadas manuales espera (queda bloqueada) hasta que el semáforo se active. 
Una vez desbloqueada, solicita al usuario ingresar nuevas coordenadas X e Y, las almacena y las reemplaza en visualT, 
permitiendo que el sistema ajuste su orientación en tiempo real.

Tras la inserción de los nuevos valores, el sistema reanuda el bucle de control, tomando en cuenta las nuevas 
coordenadas ingresadas por el usuario. motor.c recibe estos valores ajustados y calcula la nueva posición real 
de la cámara con una desviación del 3% respecto a la entrada. error.c luego calcula la discrepancia entre la nueva 
posición deseada y la alcanzada, permitiendo que el sistema continúe ajustando la cámara en tiempo real para seguir 
el nuevo punto de referencia.*/



#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>
#include <esp_log.h>
#include "pert.h"
#include "motor.h"
#include "visualTrack.h"
#include "error.h"

#define LIM_X_TRACK  10  //Límite (positivo) dimensión X para el sistema de seguimiento
#define LIM_Y_TRACK   2.5  //Límite (positivo) dimensión Y para el sistema de seguimiento

#define LIM_X_PERT (LIM_X_TRACK*0.1)  //Límite (positivo) dimensión X para la perturbación
#define LIM_Y_PERT (LIM_Y_TRACK*0.1)  //Límite (positivo) dimensión Y para la perturbación

#define DIM 2     // Dimensión del espacio de trabajo
#define X  0      // Coordenada X
#define Y  1      // Coordenada Y

float request[DIM] = {0,0};
float visualT[DIM];
float pert[DIM];
float real[DIM];
float error[DIM];
float input[DIM];

TaskHandle_t trackingTaskHandle = NULL;
TaskHandle_t userInputTaskHandle = NULL;
SemaphoreHandle_t spaceKeySemaphore = NULL;  // Semáforo para sincronizar las tareas

static const char *TAG = "ENTRADA DE USUARIO";


// Tarea que espera para que la telca sea presionada
void keyboardListenerTask(void *pvParameters) {
    while (true) {
        char c = getchar();  // Espera a que se presione la tecla
        if (c == ' ') {  // Si la tecla es presionada (ESPACIO)
            ESP_LOGI(TAG, "Entrada manual activada");
            xSemaphoreGive(spaceKeySemaphore);  // Se libera el semáforo
        }
        vTaskDelay(pdMS_TO_TICKS(100)); 
    }
}



// Tarea que gestiona la entrada manual de coordenadas
void userInputTask(void *pvParameters) {
    while (true) {
        //Espera hasta que se presione la tecla (semáforo liberado)
        if (xSemaphoreTake(spaceKeySemaphore, portMAX_DELAY) == pdTRUE) {
            ESP_LOGI(TAG, "Introduzca las coordenadas (X Y): ");
            scanf("%f %f", &request[X], &request[Y]);
            ESP_LOGI(TAG, "Nuevas coordenadas: X=%.2f, Y=%.2f", request[X], request[Y]);
        }
        ESP_LOGI(TAG, "request: X=%.2f, Y=%.2f", request[X], request[Y]);
        ESP_LOGI(TAG, "real: X=%.2f, Y=%.2f", real[X], real[Y]);
        ESP_LOGI(TAG, "error: X=%.2f, Y=%.2f", error[X], error[Y]);
    }
}

// Tarea que gestiona la entrada visual de coordenadas
void trackingTask(void *pvParameters) {
    while (true) {
        generateVisualTrack(LIM_X_TRACK, LIM_Y_TRACK, visualT);
        generatePert(LIM_X_PERT, LIM_Y_PERT, pert);
        generateInput(request, visualT, pert, input);
        generateOutput(input, real);
        generateError(request, visualT, real, error);

        ESP_LOGI(TAG, "visualT: X=%.2f, Y=%.2f", visualT[X], visualT[Y]);
        ESP_LOGI(TAG, "real: X=%.2f, Y=%.2f", real[X], real[Y]);
        ESP_LOGI(TAG, "error: X=%.2f, Y=%.2f", error[X], error[Y]);

        vTaskDelay(pdMS_TO_TICKS(100));  
    }
}

void app_main(void) {
    // Creación del semáforo (binario)
    spaceKeySemaphore = xSemaphoreCreateBinary();
    if (spaceKeySemaphore == NULL) {
        ESP_LOGE(TAG, "No se pudo crear el semáforo");
        return;
    }

    // Creación de la tareas
    xTaskCreate(trackingTask, "TrackingTask", 2048, NULL, 1, &trackingTaskHandle);
    xTaskCreate(userInputTask, "UserInputTask", 2048, NULL, 2, &userInputTaskHandle);
    xTaskCreate(keyboardListenerTask, "KeyboardListenerTask", 2048, NULL, 3, NULL);
}
