triangle: main.c
	clang -framework SDL2 -framework OpenGL -o triangle main.c

clean:
	rm triangle
