Pasos para instalar Xv6:

1. Descargas e Instalaciones:
	- Se descargó e instaló una VM para utilizar Linux Ubuntu en Windows 11.
	- En la terminal de Linux se ejecutó el comando "sudo apt install ./code_1.92.0-1722473020_amd64.deb" para instalar VSCode en la VM.
	* sudo permite manejar la terminal como admin master, permitiendo tareas como agregar y eliminar usuarios, etc. PD: Pide la clave de usuario del sistema para ejecutarse.
	- En la terminal de Linux se ejecutó el comando "sudo -i" y "apt-get install git" para instalar git en la VM.
	- En la terminal de Linux se ejecutó el comando "apt-get install qemu-system" para instalar qemu en la VM.
	- Se siguieron los pasos de este blog https://bernardnongpoh.github.io/posts/riscv para la instalacion de riscv toolchain en la VM.

2. Sign up y uso de  Github:
	- Se creo una cuenta en github para el uso de los repositorios.
	- Se usó el link de la primera presentacion para ir al github de Xv6 proporcionado por el profesor.
	- Se creo un Fork desde el link de Xv6 al github personal creado anteriormente.

3. Clonacion de Fork:
	- Se inició VSCode en Ubuntu.
	- En la terminal de VSCode se ejecutó "git clone --depth 1 https://github.com/Vale-Arce22/xv6-riscv" para hacer una clonacion superficial del Fork creado en el paso 2.
	- Se ejecutó "cd xv6-riscv" para ir a la carpeta "xv6-riscv" creada a partir de la clonación.
	- Se ejecutó "git fetch --unshallow" para realizar el resto de la clonación de manera profunda y poder clonar todos los archivos del repositorio.
	
4. Compilación y Ejecución
	- En la terminal se ejecutó "git checkout -b Tarea0" para crear un primer branch con el nombre Tarea0.
	- En la terminal se ejecutó "make qemu" para compilar y ejecutar Xv6 dentro de la VM QEMU.
	- Una vez Xv6 ejecutandose en QEMU se verificó que funcionara correctamente con los comandos: 
		ls
		echo "Hola xv6"
		cat README

Problemas encontrados y soluciones:
 1. El acceso a la VM de manera gratuita solo fue posible a través de la descarga pirata.

 2. Al hacer el paso a paso del blog https://bernardnongpoh.github.io/posts/riscv para la instalación de riscv toolchain en la VM, se tenía que utilizar el comando sudo para hacer uso del admin master, sin embargo, se desconocia el funcionamiento de este comando. Esto se solucionó investigando y aprendiendo de este comando en internet, para luego ejecutarlo.

 3. Al clonar el repositorio, la cantidad de archivos no permitia que se pudiera llegar a termino y tiraba error. Esto se solucionó haciendo en primera instancia una clonación superficial, para luego hacer una clonación mas profunda con los comandos mencionados en el paso 3.

 4. Al hacer el make qemu tiro un error debido a que el compilador RISC-V y sus herramientas no estaban instaladas correctamente, en especifico gcc. Esto se solucionó ejecutando los comandos "sudo apt-get update" y "sudo apt-get install gcc-riscv64-unknown-elf", comandos para actualizar la lista de paquetes disponibles y sus versiones, y para instalar el compilador gcc, respectivamente.

 5. No fue posible cerrar Xv6 con Ctrl + A, X; ni interrumpir el proceso con Ctrl + C. Esto se solucionó:
	1) Cerrando la terminal.
	2) Abriendo una nueva terminal.
	3) Ejecutando el comando "pgrep qemu" para obtener el PID.
	4) Ejecutando el comando "kill -9 <PID>" para forzar el termino del proceso.

Confirmacion del correcto funcionamiento de Xv6:

 1. Comando: ls

	Resultado: 

	```bash
	.              1 1 1024
	..             1 1 1024
	README         2 2 2403
	cat            2 3 35520
	echo           2 4 34368
	forktest       2 5 16232
	grep           2 6 38960
	Tarea00        2 7 33600
	Tarea01        2 8 33808
	init           2 9 34824
	kill           2 10 34288
	ln             2 11 34104
	ls             2 12 37632
	mkdir          2 13 34352
	rm             2 14 34336
	sh             2 15 57080
	stressfs       2 16 35224
	usertests      2 17 181128
	grind          2 18 50792
	wc             2 19 36504
	zombie         2 20 33688
	console        3 21 0

 2. Comando: echo "Hola xv6"

	Resultado: 
	
	```bash
	"Hola xv6"

 3. Comando: cat README

	Resultado:

	```bash
	xv6 is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix
	Version 6 (v6).  xv6 loosely follows the structure and style of v6,
	but is implemented for a modern RISC-V multiprocessor using ANSI C.

	ACKNOWLEDGMENTS

	xv6 is inspired by John Lions's Commentary on UNIX 6th Edition (Peer
	to Peer Communications; ISBN: 1-57398-013-7; 1st edition (June 14,
	2000)).  See also https://pdos.csail.mit.edu/6.1810/, which provides
	pointers to on-line resources for v6.

	The following people have made contributions: Russ Cox (context switching,
	locking), Cliff Frey (MP), Xiao Yu (MP), Nickolai Zeldovich, and Austin
	Clements.

	We are also grateful for the bug reports and patches contributed by
	Takahiro Aoyagi, Marcelo Arroyo, Silas Boyd-Wickizer, Anton Burtsev,
	carlclone, Ian Chen, Dan Cross, Cody Cutler, Mike CAT, Tej Chajed,
	Asami Doi,Wenyang Duan, eyalz800, Nelson Elhage, Saar Ettinger, Alice
	Ferrazzi, Nathaniel Filardo, flespark, Peter Froehlich, Yakir Goaron,
	Shivam Handa, Matt Harvey, Bryan Henry, jaichenhengjie, Jim Huang,
	Matúš Jókay, John Jolly, Alexander Kapshuk, Anders Kaseorg, kehao95,
	Wolfgang Keller, Jungwoo Kim, Jonathan Kimmitt, Eddie Kohler, Vadim
	Kolontsov, Austin Liew, l0stman, Pavan Maddamsetti, Imbar Marinescu,
	Yandong Mao, Matan Shabtay, Hitoshi Mitake, Carmi Merimovich, Mark
	Morrissey, mtasm, Joel Nider, Hayato Ohhashi, OptimisticSide,
	phosphagos, Harry Porter, Greg Price, RayAndrew, Jude Rich, segfault,
	Ayan Shafqat, Eldar Sehayek, Yongming Shen, Fumiya Shigemitsu, snoire,
	Taojie, Cam Tenny, tyfkda, Warren Toomey, Stephen Tu, Alissa Tung,
	Rafael Ubal, Amane Uehara, Pablo Ventura, Xi Wang, WaheedHafez,
	Keiichi Watanabe, Lucas Wolf, Nicolas Wolovick, wxdao, Grant Wu, x653,
	Jindong Zhang, Icenowy Zheng, ZhUyU1997, and Zou Chang Wei.

	The code in the files that constitute xv6 is
	Copyright 2006-2024 Frans Kaashoek, Robert Morris, and Russ Cox.

	ERROR REPORTS

	Please send errors and suggestions to Frans Kaashoek and Robert Morris
	(kaashoek,rtm@mit.edu).  The main purpose of xv6 is as a teaching
	operating system for MIT's 6.1810, so we are more interested in
	simplifications and clarifications than new features.

	BUILDING AND RUNNING XV6

	You will need a RISC-V "newlib" tool chain from
	https://github.com/riscv/riscv-gnu-toolchain, and qemu compiled for
	riscv64-softmmu.  Once they are installed, and in your shell
	search path, you can run "make qemu".