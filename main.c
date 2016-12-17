#include <stdlib.h>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>

const char *vertex_shader =
"#version 150\n"
"in vec3 v;"
"void main() {"
"   gl_Position = vec4(v, 1.0);"
"}";

const char *fragment_shader =
"#version 150\n"
"out vec4 frag_color;"
"void main() {"
"   frag_color = vec4(0.0, 0.0, 1.0, 1.0);"
"}";

const float points[] = {
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

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

    SDL_GLContext context = SDL_GL_CreateContext(window);

    if(context == NULL) {
        printf("OpenGL context could not be created: %s\n", SDL_GetError());
        return 1;
    } else {
        printf("OpenGL context created successfully.\n");
    }

    SDL_GL_SetSwapInterval(1);

    glClearColor ( 1.0, 1.0, 1.0, 1.0 );

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    GLint is_compiled = 0;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &is_compiled);

    if(is_compiled == GL_FALSE) {
        GLint maxlength;
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxlength);
        char *infoLog = malloc(sizeof(char) * maxlength);
        glGetShaderInfoLog(vs, maxlength, &maxlength, &infoLog[0]);
        printf("Vertex shader failed to compile. \n MESSAGE: %s \n", infoLog);
        free(infoLog);

        return 1;
    }

    glGetShaderiv(fs, GL_COMPILE_STATUS, &is_compiled);

    if(is_compiled == GL_FALSE) {
        GLint maxlength;
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxlength);
        char *infoLog = malloc(sizeof(char) * maxlength);
        glGetShaderInfoLog(fs, maxlength, &maxlength, &infoLog[0]);
        printf("Fragment shader failed to compile. %d \n MESSAGE: %s \n", maxlength, infoLog);
        free(infoLog);

        return 1;
    }

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    GLint isLinked = 0;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &isLinked);

    if(isLinked == GL_FALSE)
    {
        GLint maxlength;
        glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &maxlength);
        char *infoLog = malloc(sizeof(char) * maxlength);
        glGetProgramInfoLog(shader_program, maxlength, &maxlength, &infoLog[0]);
        printf("Shader failed to link. \n MESSAGE: %s \n", infoLog);
        free(infoLog);
    }

    glUseProgram(shader_program);

    glBindVertexArray(vao);

    SDL_Event events;

    int running = 1;
    while(running)
    {
        while(SDL_PollEvent(&events))
        {
            if(events.type == SDL_QUIT)
                running = 0;
        }

        glClear (GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
        SDL_Delay(33);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
