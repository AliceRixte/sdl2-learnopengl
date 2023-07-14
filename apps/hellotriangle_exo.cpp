#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <SDL2/SDL_opengl.h>

#include <iostream>

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     1.0f,  0.5f, 0.0f
};  


const char* vertexShaderSource = 
        "#version 330 core \n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main (){\n"
            "gl_Position = vec4(aPos.x, aPos.y,aPos.z, 1.0);\n"
        "}\0";

 const char* redFragmentShaderSource = 
        "#version 330 core \n"
        "out vec4 FragColor;\n"
        "void main(){\n"
        "   FragColor = vec4(0.8f,0.0f,0.2f,1.0f); \n"
        "}";

 const char* blueFragmentShaderSource = 
        "#version 330 core \n"
        "out vec4 FragColor;\n"
        "void main(){\n"
        "   FragColor = vec4(0.2f,0.0f,0.8f,1.0f); \n"
        "}";

const char* fragmentShaderSources[2] = {redFragmentShaderSource, blueFragmentShaderSource};


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

    const unsigned int NB_COLOR = 2;
    int i = 0;

    unsigned int fragmentShader [NB_COLOR];

    for(int i =0; i < NB_COLOR;  i++){
        fragmentShader[i] = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader[i], 1, &(fragmentShaderSources[i]), NULL);
        glCompileShader(fragmentShader[i]);

        glGetShaderiv(fragmentShader[i], GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(fragmentShader[i], 512, NULL, infolog);
            std::cerr << "ERROR :: SHADER :: FRAGMENT :: COMPILATION FAILED \n"
                << "GL infolog : " << infolog << std::endl;
        }
    }
    

    unsigned int shaderProgram [NB_COLOR];

    for(int i =0; i < NB_COLOR;  i++){
        shaderProgram[i] = glCreateProgram();

        glAttachShader(shaderProgram[i], vertexShader);
        glAttachShader(shaderProgram[i], fragmentShader[i]);
        glLinkProgram(shaderProgram[i]);

        glGetProgramiv(shaderProgram[i],GL_LINK_STATUS, &success);

        if(!success){
        glGetProgramInfoLog(shaderProgram[i], 512, NULL, infolog);
        std::cerr << "ERROR :: SHADER :: PROGRAM :: LINKING FAILED \n"
            <<"GL infolog" << infolog <<std::endl;
        }
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader[0]);

    
    

    
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //glBindBuffer(GL_ARRAY_BUFFER,0);


    unsigned int triangles[2][3] = {{0,1,2}, {1,2,3}};
    unsigned int VAOs[2], EBOs[2];

    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, EBOs);

    for(int i = 0; i <2 ; i++){
        glBindVertexArray(VAOs[i]);
    
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangles[i]), triangles[i], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0); 
    }
    glBindBuffer(GL_VERTEX_ARRAY, 0);
   

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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

        
        for(int i = 0; i <2 ; i++){
            glUseProgram(shaderProgram[i]);
            glBindVertexArray(VAOs[i]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        }

        SDL_GL_SwapWindow( window );
        SDL_Delay( 1 );
    }

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram[0]);
    glDeleteProgram(shaderProgram[1]);

    SDL_GL_DeleteContext( context );
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}