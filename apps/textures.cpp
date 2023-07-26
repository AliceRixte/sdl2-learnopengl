#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_image.h>

//#include <SDL2/SDL_opengl.h>

#include <iostream>
#include <filesystem>

#include "learnopengl.h"

namespace fs =  std::filesystem;

const fs::path shadersPath = 
    fs::current_path().parent_path().parent_path() / "resources" / "shaders";

const fs::path texturesPath = 
    fs::current_path().parent_path().parent_path() / "resources" / "textures";

float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};



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

    Shader shader((shadersPath / "texture.vs").string()
        , (shadersPath / "texture.fs").string());

    unsigned int square[6] = {0,1,2,0,2,3};

    GLuint VBO, VAO,EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square),square, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);


    GLuint texture0; 
    glGenTextures(1, &texture0);
    glBindTexture(GL_TEXTURE_2D, texture0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_Surface* surface =IMG_Load(
        (texturesPath / "wall.jpg").string().c_str());
    if(surface){
        int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D ,0, mode, surface ->w, surface -> h 
            ,0 , mode, GL_UNSIGNED_BYTE, surface -> pixels);
        SDL_FreeSurface(surface);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cerr << "ERROR::TEXTURE::LOADING" << std::endl
            << "SDL_image log : " << IMG_GetError() <<std::endl;
    }

    GLuint texture1; 
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    surface =IMG_Load(
        (texturesPath / "awesomeface.png").string().c_str());
    if(surface){
        int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
        flip_surface(surface);
        glTexImage2D(GL_TEXTURE_2D ,0, mode, surface ->w, surface -> h 
            ,0 , mode, GL_UNSIGNED_BYTE, surface -> pixels);
        SDL_FreeSurface(surface);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cerr << "ERROR::TEXTURE::LOADING" << std::endl
            << "SDL_image log : " << IMG_GetError() <<std::endl;
    }

    bool keepRunning = true;

    shader.use();
    shader.setInt("texture0",0);
    shader.setInt("texture1",1);

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

        shader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, 0 );


        SDL_GL_SwapWindow( window );
        SDL_Delay( 1 );
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    SDL_GL_DeleteContext( context );
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
} 