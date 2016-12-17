game: main.c
	clang -framework SDL2 -o game main.c

clean:
	rm game
