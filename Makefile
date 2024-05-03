all:
	gcc -Wall -pedantic DisparoTiempo.c -o DisparoTiempo
	gcc -Wall -pedantic TasaMonotonica.c -o TasaMonotonica
	gcc -Wall -pedantic TiempoLimite.c -o TiempoLimite
	gcc -Wall -pedantic PrioridadEstatica.c -o PrioridadEstatica
	
disparo:
	./DisparoTiempo
	
tasa:
	./TasaMonotonica
	
tiempo:
	./TiempoLimite

prioridad:
		echo "Prioridad Estatica"
		./PrioridadEstatica
