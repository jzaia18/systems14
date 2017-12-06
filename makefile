all: c.c
	gcc -o control c.c

run: all
	./control
