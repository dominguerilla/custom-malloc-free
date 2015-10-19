FLAGS=-g -Wall
LIBS=-lm
CC=gcc


OBJ=malloc-free.c
HDR=malloc-free.h

prog1: $(OBJ) $(HDR)
	$(CC) prog1.c $(OBJ) $(FLAGS) $(LIBS) -o prog1

prog2: $(OBJ) $(HDR)
	$(CC) prog2.c $(OBJ) $(FLAGS) $(LIBS) -o prog2

prog3: $(OBJ) $(HDR)
	$(CC) prog3.c $(OBJ) $(FLAGS) $(LIBS) -o prog3
clean:
	-rm -f *.o
	-rm -f prog1
	-rm -f prog2
