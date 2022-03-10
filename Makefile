CC = gcc
CFLAGS = -ansi -pedantic -Wall -fPIC -g -I../COSINE
LDFLAGS = -L../COSINE -l:libcosine.a

gui: main.c widget.c button.c label.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f gui

.PHONY: clean
