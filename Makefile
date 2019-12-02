COMPILER=gcc
DEBUG_COMPILER=-g -DDEBUG=1
OUTPUT_FILE=TP_PI

all: tad.o funcionesauxiliares.o
	$(COMPILER) -o $(OUTPUT_FILE) -pedantic -Wall -std=c99 -fsanitize=address main.c tad.o funcionesauxiliares.o

debug: COMPILER+=$(DEBUG_COMPILER)
debug: all

funcionesauxiliares.o: funcionesauxiliares.h funcionesauxiliares.c
	gcc -c funcionesauxiliares.c funcionesauxiliares.h

tad.o: tad.h tad.c
	gcc -c tad.h tad.c

clean:
	rm -r *.o *.h.gch dia_semana.csv movimientos_aeropuerto.csv composicion.csv
