============= OPERACIONES BASICAS DE SECUENCIAS ================

Pre-requisitos: 
	
	Tener instalado gnuplot y un visualizados de archivos pdf. 
	El programa solo corre en sistemas gnu/linux. 

	Se puede instalar gnuplot en caso de necesitarlo. 
	
	Ubuntu: 
		$ sudo apt install gnuplot
 
	Manjaro o basados en Arch:
		$ sudo pacman -S gnuplot

	Se puede instalar un visualizador de pdf en caso de necesitarlo,
	por ejemplo, Okular.  

	Ubuntu: 
		$ sudo apt install okular

	Manjaro: 

		$ sudo pacman -S okular

Compilar: 

	g++ main.cpp 

Correr: 
	Para correr sin graficar: 

	./a.out 

	Para correr obteniendo gráficas a la salida: 

	./a.out -g

