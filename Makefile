all: main

main: main.o tsuki.o glad.o utils.o
	cc -o $@ $^ -lglfw -lGL -ldl -lpthread

main.o: src/main.c src/tsuki.h
	cc -c $< -o $@ -I./glad/include
tsuki.o: src/tsuki.c src/tsuki.h
	cc -c $< -o $@ -I./glad/include
utils.o: src/utils.c src/utils.h
	cc -c $< -o $@

glad.o: glad/src/glad.c
	cc -c $< -o $@ -I./glad/include


clean:
	rm -f main main.o tsuki.o glad.o utils.o
