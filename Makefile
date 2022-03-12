CC = gcc
CFLAGS = -ansi -pedantic -Wall -fPIC -g -I../COSINE
LDFLAGS = -L../COSINE -l:libcosine.a
SRC = main.c widget.c layout.c button.c label.c vbox.c
OBJ = main.o widget.o layout.o button.o label.o vbox.o

shuttle: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f shuttle $(OBJ)

.PHONY: shuttle clean
