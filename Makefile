CC = gcc
PROGRAM = cikcak
CFLAGS  = -g -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): main.o pomocneFunkcije.o funkcijeZaCrtanje.o GlutFunkcije.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^ $(LDLIBS)
	
main.o: main.c deklaracije.h
	$(CC) $(CFLAGS) -c $^
	
GlutFunkcije.o: GlutFunkcije.c
	$(CC) $(CFLAGS) -c $^ 
	
pomocneFunkcije.o: pomocneFunkcije.c
	$(CC) $(CFLAGS) -c $^
	
funkcijeZaCrtanje.o: funkcijeZaCrtanje.c
	$(CC) $(CFLAGS) -c $^
