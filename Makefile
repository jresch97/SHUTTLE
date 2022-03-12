CC = gcc
CFLAGS = -ansi -pedantic -Wall -fPIC -g -I../COSINE -I../EUROPA
LDFLAGS = -L../COSINE -L../EUROPA -l:libcosine.a -l:libeuropa.a -lX11 -lXext
SRC = main.c widget.c layout.c button.c label.c vbox.c hbox.c
OBJ = main.o widget.o layout.o button.o label.o vbox.o hbox.o

shuttle: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f shuttle $(OBJ)

.PHONY: shuttle clean
