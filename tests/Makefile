CC      = gcc
CFLAGS  = -ansi -pedantic -Wall -fPIC -g -I../include -I../../COSINE/include -I../../EUROPA
LDFLAGS = -L../../COSINE -L../../EUROPA -L../ -l:libeuropa.a -l:libshuttle.a -l:libcosine.a -lX11 -lXext
OBJ     = main.o

all: main

main: main.o
	$(CC) -o $@ $^ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(OBJ)

.PHONY: clean
