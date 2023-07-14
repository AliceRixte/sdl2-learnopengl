
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <SDL2/SDL_opengl.h>

#include <iostream>

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};  


const char* vertexShaderSource = 
        "#version 330 core \n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main (){\n"
            "gl_Position = vec4(aPos.x, aPos.y,aPos.z, 1.0);\n"
        "}\0";

 const char* fragmentShaderSource = 
        "#version 330 core \n"
        "out vec4 FragColor;\n"
        "void main(){\n"
        "   FragColor = vec4(0.8f,0.0f,0.2f,1.0f); \n"
        "}";


int main( int argc, char * argv[] )
{
    SDL_Init( SDL_INIT_VIDEO );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE );

    static const int width = 800;
    static const int height = 600;

    SDL_Window * window = SDL_CreateWindow( 
        "Learn OpenGL with SDL window",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    SDL_GLContext context = SDL_GL_CreateContext( window );

    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit()) {
        std::cerr << "Error in glew initialisation" << std::endl;
    }
    else {
        glViewport(0, 0, width, height);
    }


    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cerr 
            << "ERROR :: SHADER :: VERTEX :: COMPILATION FAILED\n"
            << "GL Infolog : " << infolog << std::endl;
    }

   

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
        std::cerr << "ERROR :: SHADER :: FRAGMENT :: COMPILATION FAILED \n"
            << "GL infolog : " << infolog << std::endl;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGetProgramiv(shaderProgram,GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
        std::cerr << "ERROR :: SHADER :: PROGRAM :: LINKING FAILED \n"
            <<"GL infolog" << infolog <<std::endl;
    }

    

    
    unsigned int VAO,VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    bool keepRunning = true;

    while(keepRunning)
    {
        SDL_Event event;
        while( SDL_PollEvent( &event ) )
        {
            switch( event.type )
            {
                case SDL_KEYUP:
                    if( event.key.keysym.sym == SDLK_ESCAPE )
                        keepRunning = false;
                    break;
                case SDL_WINDOWEVENT:
                    if( event.window.event == SDL_WINDOWEVENT_CLOSE)
                        keepRunning = false;
                    break;
            }
        }

        glClearColor(0.1f,0.1f,0.1f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT );

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);


        SDL_GL_SwapWindow( window );
        SDL_Delay( 1 );
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    SDL_GL_DeleteContext( context );
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}