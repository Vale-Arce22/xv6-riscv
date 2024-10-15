Informe de implementación de Scheduler con Sistema de Prioridades y Boosts

1. Funcionamiento del sistema de prioridades:
	- Estructura del proceso (proc.h)
		Se agregaron dos nuevos campos a la estructura de un proceso para habilitar sistema de prioridades, estos son:
			- priority: Campo que define la prioridad del proceso, donde un valor más bajo indica mayor prioridad.
			- boost: Campo utilizado para modificar la prioridad de un proceso, ya sea aumentándola o reduciéndola.

	- Función allocproc (proc.h)
		Se modificó la función allocproc para inicializar los valores de prioridad y boost en 0 (mayor prioridad) y 1, respectivamente.

	- Scheduler (proc.c)
		Se modificó la función scheduler para implementar la lógica del manejo de prioridades, la cual incluye:
		- Ajustar las prioridades de los procesos en cada iteración del scheduler.
		- Incrementar la prioridad de cada proceso utilizando el campo boost.
		- Limitar la prioridad en un rango de 0 a 9, reduciendo el boost cuando la prioridad llega a 9 y aumentando cuando se establece en 0.

	- Programa de Prueba (Prueba_t2.c):
		Se ha modificado el archivo Prueba_t2.c para crear 20 procesos y demostrar la funcionalidad del nuevo sistema de prioridades:
		- Se define un número constante NUM_PROCESOS para crear 20 procesos.
		- Cada proceso hijo ejecuta una función que imprime su identificador y espera un tiempo breve antes de finalizar.

2. Explicación de las modificaciones realizadas:

	- Modificaciones en proc.h:
		Se añadieron los campos priority, y boost en la estructura proc.

	- Modificaciones en allocproc (proc.c):
		- Se inicializaron los nuevos campos en la función allocproc:
		- p->priority = 0; para establecer la prioridad inicial.
		- p->boost = 1; para inicializar el boost.

	- Modificaciones en scheduler (proc.c):
		- Se implementó la lógica del scheduler para ajustar las prioridades de los procesos, incluyendo:
		- Un bucle que itera sobre todos los procesos, ajustando las prioridades y limitando los valores entre 0 y 9.

	- Programa de Prueba:
		- Se creó Prueba_t2.c, que incluye la definición de un número constante para crear 20 procesos y la implementación de la lógica necesaria para que cada proceso imprima su identificador y duerma un tiempo.
	
	- Nueva syscall:
		- Se implementó una nueva llamada de sistema, que nos permita visualizar la prioridad de los procesos. Esto se logró siguiendo el mismo procedimiento que se realizó para las llamadas de sistema de las tareas anteriores, modificando los archivos:
			- sysproc.c
			- syscall.h
			- syscall.c
			- usys.pl
			- user.h
	
3. Dificultades encontradas y cómo se solucionaron:

	- Errores de Compilación:
		- Problema: Se presentaron errores al compilar debido a la falta de inicialización de los nuevos campos en algunas partes del código.
		- Solución: Se revisó y actualizó el código en el archivo proc.c en el codigo perteneciente a allocproc y al scheduler para asegurar que todos los nuevos campos fueran correctamente inicializados.

	- Gestión de Prioridades:
		- Problema: Hubo confusiones sobre el manejo de los valores de prioridad y boost en el scheduler.
		- Solución: Se añadió lógica de control para ajustar y limitar las prioridades adecuadamente en el scheduler.