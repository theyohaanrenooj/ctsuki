main: main.o
	cc -o main main.o -lglfw -lGL -ldl -lpthread
main.o: src/main.c
	cc -c src/main.c -o main.o 

clean: main.o
	rm -f main.o
