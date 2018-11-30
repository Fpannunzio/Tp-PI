COMPILER=gcc
DEBUG_COMPILER=-g -DDEBUG=1
OUTPUT_FILE=TP_PI

all: tad.o
	$(COMPILER) -o $(OUTPUT_FILE) main.c tad.o

debug: COMPILER+=$(DEBUG_COMPILER)
debug: all

tad.o: tad.h tad.c
	gcc -c tad.h tad.c

clean:
	rm -r $(OUTPUT_FILE)*.o *.h.gch