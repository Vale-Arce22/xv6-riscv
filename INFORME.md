# Informe de implementación de Sistema de Permisos en xv6

## 1. Funcionamiento del sistema de permisos:

### 1.1. Definición de permisos en la estructura `inode`:
- Se añadió un nuevo campo `perm` a la estructura `inode` para almacenar los permisos de los archivos. Los valores posibles para este campo son:
  - 1: Permiso de lectura.
  - 2: Permiso de escritura.
  - 3: Permiso de lectura y escritura, que es el valor predeterminado.

### 1.2. Inicialización de permisos al crear archivos:
- En la función `create`, se inicializó el campo `perm` con un valor predeterminado de 3, lo que otorga permisos de lectura y escritura a los archivos creados.

### 1.3. Implementación de la función `check_perm`:
- Se implementó la función `check_perm` en el archivo `fs.c` para verificar si los permisos del archivo permiten la operación solicitada. La función recibe el puntero al `inode` del archivo y los permisos solicitados, y devuelve 0 si la operación es permitida o -1 si no lo es.

### 1.4. Validación de permisos en `sys_open`:
- Se modificó la función `sys_open` para llamar a `check_perm` antes de abrir un archivo. Esto garantiza que el archivo se abra solo si los permisos solicitados son válidos.

### 1.5. Creación de la llamada al sistema `sys_chmod`:
- Se añadió la nueva llamada al sistema `sys_chmod` para permitir cambiar los permisos de un archivo. Esta función se encargará de actualizar el campo `perm` de un archivo según los permisos especificados por el usuario.

### 1.6. Modificación de `sys_read` y `sys_write`:
- Las funciones `sys_read` y `sys_write` fueron modificadas para manejar correctamente los permisos antes de permitir la lectura o escritura en los archivos. Estas funciones ahora verifican si el archivo tiene los permisos necesarios antes de realizar las operaciones.

### 1.7. Archivo de prueba `test_t4.c`:
- Se creó el archivo de prueba `test_t4.c` para verificar la funcionalidad del sistema de permisos implementado.
- En este archivo, se crearon archivos con diferentes configuraciones de permisos y se probaron las operaciones de lectura y escritura para asegurarse de que los permisos fueran aplicados correctamente.
- El archivo de prueba incluye la creación de archivos, la modificación de permisos con `sys_chmod`, y la verificación de acceso mediante `sys_read` y `sys_write`.

## 2. Explicación de las modificaciones realizadas:

### 2.1. Modificaciones en la estructura `inode`:
- Se añadió el campo `perm` en la estructura `inode` para almacenar los permisos de lectura y escritura de los archivos. Este campo permite establecer y verificar los permisos de cada archivo.

### 2.2. Modificaciones en `sysfile.c`:
- En la función `create`, se inicializó el campo `perm` con un valor predeterminado de 3 (lectura y escritura) al momento de crear un archivo.
- Se implementó la función `check_perm` para comprobar los permisos antes de realizar una operación sobre el archivo.
- Se implementó la llamada al sistema `sys_chmod` que permite cambiar los permisos de un archivo, modificando su campo `perm`.
- Se modificaron las funciones `sys_read` y `sys_write` para verificar que los permisos sean adecuados antes de permitir la lectura o escritura de los archivos.

### 2.3. Nueva syscall `sys_chmod`:
- Se implementó una nueva llamada de sistema, `sys_chmod`, que permite cambiar los permisos de un archivo especificando los permisos deseados. Esta llamada permite modificar el campo `perm` de un archivo en función de las necesidades del usuario.

### 2.4. Modificación del archivo de prueba:
- Se creó el archivo de prueba `test_t4.c` para validar las operaciones de lectura, escritura y modificación de permisos. Este archivo verifica que los permisos definidos sean correctamente aplicados y que las operaciones se realicen según lo esperado.

## 3. Dificultades encontradas y cómo se solucionaron:

### 3.1. Problemas con la manipulación de punteros en `sys_read` y `sys_write`:
- **Problema**: Las funciones `sys_read` y `sys_write` generaban errores debido al manejo incorrecto de los argumentos, especialmente al pasar punteros de tipo incorrecto.
- **Solución**: Se implementó la función `argaddr` para manejar correctamente las direcciones de memoria y corregir los errores de conversión de punteros en ambas funciones.

### 3.2. Error por uso incorrecto de los locks:
- **Problema**: Durante la implementación de los permisos y el control de acceso, se intentó integrar el uso de locks para manejar la concurrencia al modificar los permisos de los archivos. Sin embargo, el intento de implementar un sistema de bloqueo causó una serie de fallos en el código, ya que no se manejaron correctamente las secciones críticas y las condiciones de carrera. Esto resultó en errores de sincronización que llevaron a una corrupción de datos y comportamientos inesperados en el sistema.
- **Solución**: Debido a la complejidad y los errores generados por el uso incorrecto de locks, se decidió eliminar toda la implementación relacionada con los locks y empezar de nuevo. Se optó por una solución más sencilla para el manejo de permisos, sin usar mecanismos de sincronización complejos, lo que permitió restaurar la estabilidad del sistema y lograr la funcionalidad esperada sin los problemas de concurrencia previos.
