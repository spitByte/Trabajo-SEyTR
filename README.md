# Trabajo-SEyTR
Simulación de un sistema de estabilización de seguimiento visual 

INTRODUCCIÓN

En este informe se documenta el desarrollo de un sistema embebido en tiempo real simulado, cuyo objetivo es estabilizar una cámara que rastrea un objetivo en un plano XY ubicado a 10 metros de distancia que se mueve dentro de un rectángulo de 20x5m con origen en su centro geométrico. El sistema está diseñado como un bucle de control cerrado y está sujeto a un movimiento continuo para simular inestabilidad.
En cualquier momento, el usuario puede interrumpir el seguimiento visual para ingresar manualmente coordenadas X e Y de un punto al que el sistema deberá apuntar. Esto convierte el sistema en un sistema en tiempo real, ya que responde dinámicamente a la intervención del usuario mediante el uso de interrupciones.

El sistema incluye las siguientes etapas:

•	Entrada: Compuesta por dos tipos de entradas:
  o	Referencia de usuario: Son coordenadas ingresadas manualmente por el usuario, que indican un punto específico al que se desea que la cámara apunte.
  o	Entrada generada aleatoriamente: Representa la posición del objetivo en movimiento, generada de manera aleatoria para simular la detección de un objeto en el entorno.

•	Perturbaciones: Se introducen variaciones aleatorias para simular interferencias del entorno.

•	Planta: Representada por actuadores que ajustan la posición de la cámara.

•	Retroalimentación: Representada por sensores que proporcionan datos sobre la posición real.

•	Corrección: Se calcula el error comparando la posición deseada con la real.

IMPLEMENTACIÓN EN UN SISTEMA REAL

La implementación de este sistema en un entorno físico requiere una combinación de hardware especializado para garantizar la estabilidad y el control preciso de la cámara. Los principales componentes necesarios serían:

1.	Cámara de Alta Precisión:
   	Una cámara con estabilización óptica y una alta tasa de fotogramas por segundo (FPS) para mejorar el seguimiento del objetivo en entornos dinámicos.
  	Ejemplo: Cámaras industriales con sensores CMOS de alta sensibilidad.

2.	Plataforma Móvil y Actuadores:
   	Un sistema de motores paso a paso o servomotores controlados por un controlador de movimiento permitirá ajustar la posición de la cámara en el plano XY.
   	Ejemplo: Motores de precisión como los Dynamixel o servomotores de la serie MG995.

3.	Sensores de Posición y Movimiento:
   	Para obtener retroalimentación precisa, se utilizarían sensores como encoders ópticos, giróscopos y unidades de medición inercial (IMU).
   	Ejemplo: Encoders rotativos de alta resolución y sensores IMU como el MPU-6050.

4.	Unidad de Procesamiento:
    Un microcontrolador ejecutará los cálculos en tiempo real y gestionará las interrupciones del sistema.
   	Ejemplo: controlador ESP32

5.	Sistema de Alimentación:
   	Fuente de alimentación estable para garantizar la operación continua del sistema.

6.	Módulo de Comunicación:
   	Para la interacción con el usuario y la transmisión de datos en tiempo real, se podrían utilizar módulos de comunicación inalámbrica o por cable.

CÓMO USAR EL CÓDIGO

1. Descarga los archivos:

Descargar todos los archivos fuente (main.c, motor.c, pert.c, error.c, visualTrack.c y sus respectivos archivos de encabezado).

2. Compila el código

3. Ejecuta el programa

4. Visualiza los valores de seguimiento

El programa mostrará en pantalla los valores de:

visualT: Coordenadas del objetivo generado aleatoriamente.

real: Posición real de la cámara.

error: Diferencia entre la posición deseada y la real.

5. Interrumpe el seguimiento y proporciona coordenadas manuales:

Cuando se presiona el botón de interrupción, el programa detendrá la actualización automática y solicitará al usuario ingresar manualmente las coordenadas X e Y deseadas.

6. Ingresa los valores cuando el programa lo solicite y presiona Enter.
