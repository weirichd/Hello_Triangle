game:
	gcc -o game main.c `pkg-config --cflags --libs sdl2`

clean:
	rm game
