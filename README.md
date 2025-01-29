# Trabajo-SEyTR
Simulación de un sistema de estabilización de seguimiento visual 

Introducción

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

 
Imagen 1. Representación del esquema

