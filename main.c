#include <SDL2/SDL.h>
#include <OpenGL/gl.h>

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to init SDL\n");
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window *window = SDL_CreateWindow(
            "Hello Triangle", 
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            512,
            512,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
            );

    if(window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    } else {
        printf("Window created successfully.\n");
    }

    SDL_GLContext maincontext = SDL_GL_CreateContext(window);

    if(maincontext == NULL) {
        printf("OpenGL context could not be created: %s\n", SDL_GetError());
        return 1;
    } else {
        printf("OpenGL context created successfully.\n");
    }

    SDL_GL_SetSwapInterval(1);

    glClearColor ( 1.0, 1.0, 0.0, 1.0 );
    int running = 1;

    SDL_Event events;

    while(running)
    {
        while(SDL_PollEvent(&events))
        {
            if(events.type == SDL_QUIT)
                running = 0;
        }

        glClear (GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
        SDL_Delay(33);
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
