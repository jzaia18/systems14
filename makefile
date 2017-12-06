all: c.c
	gcc -o control c.c

run: all
	./control

clean: control debug
	rm control debug

debug:
	gcc -o debug -g c.c

valgrind: debug
	valgrind ./debug

gdb: debug
	gdb ./debug
