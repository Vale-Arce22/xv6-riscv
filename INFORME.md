Informe de Implementación de Llamadas al Sistema

1. Funcionamiento de las llamadas al sistema:
	- getppid():
		- La llamada al sistema getppid() se utiliza para obtener el identificador del proceso padre del proceso actual. Si el proceso actual no tiene un proceso padre, se retorna -1, indicando que se trata del proceso raíz en la jerarquía. La implementación se realizó de la siguiente manera:
		- Se añadió una función en sysproc.c para obtener el PID del proceso padre a partir de la estructura de datos del proceso actual.
		- La función sys_getppid accede al campo parent del proceso actual y retorna el PID del proceso padre, o -1 si no existe un padre.

	- getancestor(int n):
	
		- La llamada al sistema getancestor(int n) se diseñó para obtener el ancestro del proceso actual en la jerarquía de procesos. Dependiendo del valor de n, se devuelve:
		
			- getancestor(0): El PID del proceso actual.
			- getancestor(1): El PID del proceso padre.
			- getancestor(2): El PID del abuelo del proceso.
		
		- Si el valor de n es mayor que el número de ancestros disponibles, se retorna -1. - La implementación de getancestor en sysproc.c implica:
			- Recuperar el valor de n usando la función argint(), que obtiene el argumento de la llamada al sistema.
			- Recorrer la jerarquía de procesos utilizando el puntero parent hasta el ancestro deseado o hasta que no haya más ancestros.
			- Retornar el PID del ancestro encontrado o -1 si no hay suficientes ancestros.

2. Explicación de las modificaciones realizadas:

	- Modificaciones en sysproc.c

		- sys_getppid: Se añadió la función que retorna el PID del proceso padre.
		- sys_getancestor: Se implementó la función para recuperar el PID del ancestro en función del valor de n.

	- Modificaciones en syscall.c

		- Se actualizó la tabla de llamadas al sistema para incluir sys_getppid y sys_getancestor.

	- Modificaciones en Makefile

		- Se incluyó el programa de prueba yosoytupadre en el Makefile para asegurarse de que se compile e integre correctamente en el sistema.

	- Agregado de Programa de Usuario

		- Tarea1.c: Se creó un programa de usuario en la carpeta user que utiliza las llamadas al sistema getpid y getppid. Este programa se añadió al Makefile y se integró en el sistema para realizar pruebas.

	- Implementación de FIFO en xv6 (Esto fue una actividad en clase pero que ayudo para la Tarea 1)

		- Objetivo: Modificar el scheduler de xv6 para usar el algoritmo FIFO (First In, First Out) en lugar del orden actual.

		- Modificaciones:

			- Paso 1: Se agregó una propiedad llamada arrival_time para almacenar el tiempo de llegada en la estructura proc en proc.h.
			- Paso 2: Se inicializó el tiempo de llegada en la estructura cuando un proceso llega al sistema, utilizando la variable global ticks.
			- Paso 3: Se modificó el scheduler para obtener el proceso más viejo comparando el tiempo de llegada de todos los procesos.
			- Paso 4: Se asignó la CPU al proceso más viejo basado en el tiempo de llegada.
			
		- Programa de Prueba: Se creó test_fifo_xv6.c para verificar el funcionamiento del nuevo algoritmo FIFO en el sistema.

3. Dificultades encontradas y cómo Se solucionaron

	- Error de Compilación por argint()
		- Problema: Se produjo un error debido a una incompatibilidad en la declaración y el tipo de retorno de la función argint().
		- Solución: Se ajustó la declaración de argint() en defs.h para que coincidiera con la implementación en syscall.c, asegurando que se manejaran correctamente los argumentos pasados a las llamadas al sistema.

	- Referencia Indefinida a sys_getppid
		- Problema: Durante la compilación, se reportó una referencia indefinida a sys_getppid.
		- Solución: Se implementó la función sys_getppid y se actualizó la tabla de llamadas al sistema en syscall.c para incluirla correctamente.

	- Comportamiento Inesperado de getancestor
		- Problema: La función getancestor devolvía el PID del proceso actual en lugar del ancestro correcto en algunos casos.
		- Solución: Se revisó la lógica de la función para asegurarse de que recorriera correctamente la jerarquía de procesos y manejara adecuadamente los casos en los que no hay suficientes ancestros.

	- Problemas con la Gestión de Ramas en Git
		- Problema: Olvidé crear una nueva rama para los cambios y, al hacer el commit en la rama incorrecta, se borró el avance realizado. Esto requirió rehacer el trabajo desde cero.
		- Solución: Se creó una nueva rama adecuada y se volvió a implementar los cambios necesarios.

	- Dificultades con el Manejo de xv6
		- Problema: Tuve dificultades para entender el manejo de xv6 y cómo se relacionaban las instrucciones del ppt con las del GitHub.
		- Solución: Revisé la documentación y los ejemplos en el repositorio de GitHub, y consulté la documentación de xv6 para comprender mejor el funcionamiento del sistema y las instrucciones requeridas.