all: main

main: main.o window.o glad.o utils.o entity.o image.o stb_impl.o
	cc -o $@ $^ -lglfw -lGL -ldl -lpthread -lm

main.o: main.c
	cc -c $< -o $@ -I./glad/include

window.o: tsuki/window.c tsuki/window.h
	cc -c $< -o $@ -I./glad/include
entity.o: tsuki/entity.c tsuki/entity.h
	cc -c $< -o $@ -I./glad/include
utils.o: tsuki/tsuki.c tsuki/tsuki.h
	cc -c $< -o $@ -I./glad/include
image.o: tsuki/image.c tsuki/image.h
	cc -c $< -o $@ -I./glad/include


glad.o: glad/src/glad.c
	cc -c $< -o $@ -I./glad/include
stb_impl.o: tsuki/stb_impl.c
	cc -c $< -o $@ -I./glad/include

clean:
	rm -f main *.o
