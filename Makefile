main: main.o
	cc -o main main.o
main.o: src/main.c
	cc -c src/main.c -o main.o

clean: main.o
	rm -r main.o
