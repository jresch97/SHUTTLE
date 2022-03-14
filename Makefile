CC = gcc
CFLAGS = -ansi -pedantic -Wall -fPIC -g -I./include -I../COSINE/include -I../EUROPA
LDFLAGS = -L../COSINE -L../EUROPA -l:libcosine.a -l:libeuropa.a -lX11 -lXext
SRC = src/widget.c src/button.c src/layout.c src/vbox.c
OBJ = src/widget.o src/button.o src/layout.o src/vbox.o

all: libshuttle.a libshuttle.so

libshuttle.a: $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

libshuttle.so: $(OBJ)
	$(CC) -shared $^ -o $@

.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm libshuttle.a libshuttle.so $(OBJ)

.PHONY: clean
