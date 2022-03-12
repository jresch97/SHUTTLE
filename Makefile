CC = gcc
CFLAGS = -ansi -pedantic -Wall -fPIC -O2 -DNDEBUG -I../COSINE
LDFLAGS = -L../COSINE -l:libcosine.a
SRC = main.c widget.c layout.c
OBJ = main.o widget.o layout.o

gui: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f gui $(OBJ)

.PHONY: clean
