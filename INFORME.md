Informe de implementación de mprotect y munprotect en xv6

1. Actualización del Fork:

Antes de realizar cualquier modificación en el código de xv6, se actualizó el fork local para reflejar los cambios más recientes del repositorio original de MIT. Esto implicó agregar el repositorio del MIT como remoto, obtener los cambios más recientes y fusionarlos con la rama principal del repositorio local. Posteriormente, los cambios fueron empujados al fork en GitHub para asegurar que estuviera sincronizado con el repositorio original.

PD: Se cree que este paso fue el que provocó los problemas posteriores para no ser capaz de lograr la Tarea 3 al 100%.

2. Funcionamiento de mprotect y munprotect:

    - Modificación en la tabla de páginas (proc.c):

    Se implementaron las funciones mprotect y munprotect en proc.c. La función mprotect permite proteger un rango de memoria para evitar que los procesos puedan escribir en él, mientras que munprotect revierte esta protección. Ambas funciones actualizan las páginas de memoria de los procesos, cambiando el estado de las páginas correspondientes entre protegidas y no protegidas.

    - sys_mprotect y sys_munprotect (sysproc.c):
    Se añadieron las funciones sys_mprotect y sys_munprotect para que las funciones de protección de memoria sean accesibles a través de llamadas del sistema. Estas funciones permiten que los procesos en espacio de usuario invocaran las operaciones de protección y desprotección de memoria.

    - Interfaz de usuario (user.h, usys.pl):
    Se actualizaron los archivos user.h y usys.pl para proporcionar la interfaz necesaria para que los programas de usuario puedan utilizar las funciones mprotect y munprotect mediante llamadas al sistema.

    - Programa de prueba (code_test_t3.c):
    Se desarrolló un programa de prueba, code_test_t3.c, que reservaba memoria en el heap, aplicaba mprotect para protegerla y luego intentaba escribir en la memoria protegida. El programa también utilizaba munprotect para desproteger la memoria y permitir la escritura nuevamente. Sin embargo, al intentar ejecutar este programa, se presentaron problemas debido a la implementación de las funciones de protección, lo que impidió que el programa se ejecutara correctamente.

3. Explicación de las modificaciones realizadas:

    - Modificaciones en proc.c: Se implementaron las funciones mprotect y munprotect, que   permiten cambiar el estado de las páginas de memoria de los procesos, protegiéndolas o desprotegiéndolas según sea necesario.

    - Modificaciones en sysproc.c: Se añadieron las funciones sys_mprotect y sys_munprotect que permiten que los programas de usuario invoquen las funciones de protección de memoria mediante llamadas al sistema.

    - Modificaciones en user.h y usys.pl: Se añadieron las definiciones de las nuevas funciones para que puedan ser utilizadas por los programas de usuario.

4. Dificultades encontradas y soluciones:

    - Problemas al ejecutar el programa de prueba (code_test_t3.c):
        - Problema: El programa code_test_t3.c, desarrollado para probar las funciones mprotect y munprotect, no pudo ejecutarse correctamente debido a errores en la implementación de las funciones de protección de memoria. En particular, las funciones no gestionaban adecuadamente las direcciones de memoria, lo que causaba fallos al intentar proteger o desproteger las páginas.
        - Solución: Se realizó una revisión detallada del código en las funciones de protección, asegurándose de que las direcciones de memoria estuvieran correctamente alineadas y fueran válidas antes de aplicar las funciones. También se implementaron verificaciones adicionales para garantizar que la memoria asignada estuviera en un estado correcto antes de intentar aplicar las protecciones.

    - rrores de compilación y enlazado:
        - Problema: Durante la implementación, se encontraron errores de compilación debido a la falta de inicialización de algunos campos en las estructuras y la ausencia de validaciones en las funciones del sistema.
        - Solución: Se corrigieron las inicializaciones de las estructuras de memoria en proc.c, asegurando que todos los campos estuvieran correctamente definidos antes de ser utilizados en las funciones de protección.

    - Gestión de direcciones de memoria:
        - Problema: La validación de direcciones de memoria no estaba correctamente implementada, lo que generaba accesos incorrectos a páginas que no estaban asignadas o no eran accesibles.
        - Solución: Se añadió lógica adicional para verificar que las direcciones de memoria sean válidas y estén dentro del rango permitido antes de intentar aplicar cualquier tipo de protección o desprotección.