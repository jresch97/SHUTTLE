CC = gcc
CFLAGS = -ansi -pedantic -Wall -fPIC -g -I../COSINE
LDFLAGS = -L../COSINE -l:libcosine.a
SRC = main.c widget.c button.c label.c
OBJ = main.o widget.o button.o label.o

gui: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f gui $(OBJ)

.PHONY: clean
