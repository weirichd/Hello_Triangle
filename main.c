#include <SDL2/SDL.h>

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to init SDL\n");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
            "My Game", 
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            512,
            512,
            SDL_WINDOW_OPENGL
            );

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    } else {
        printf("Window created successfully!\n");
    }

    int running = 1;

    SDL_Event events;

    while(running)
    {
        while(SDL_PollEvent(&events))
        {
            if(events.type == SDL_QUIT)
                running = 0;
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
