game: main.c
	clang -framework SDL2 -framework OpenGL -o game main.c

clean:
	rm game
