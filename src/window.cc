#include <iostream>
#include <cassert>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "window.hh"
#include "gl_helper.hh"
#include "input.hh"

Window::Window() {

}

void Window::create( int32_t width, int32_t height, int32_t scale ) {

    m_width = width;
    m_height = height;

    int sdl_init_ = SDL_Init( SDL_INIT_VIDEO );
    if( sdl_init_ < 0 )
        std::cout << "SDL error ->" << SDL_GetError() << std::endl;

    SDL_Window *window = SDL_CreateWindow( "renderer", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, width * scale, height * scale, SDL_WINDOW_OPENGL );

    m_blk_window = window;

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GL_SetSwapInterval( 0 );

    SDL_GLContext gl_context = SDL_GL_CreateContext( window );

    glewExperimental = GL_TRUE;
    GLenum glew_init_;
    if( ( glew_init_ = glewInit() ) != GLEW_OK ) {
        std::cout << glewGetErrorString( glew_init_ ) << std::endl;
        assert( false && "GLEW INIT FAILED" );
    }

#if _WIN64
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG );
    glEnable( GL_DEBUG_OUTPUT );
    glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );
    glDebugMessageCallback( opengl_error_callback, nullptr );
    glDebugMessageControl( GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true );
#endif

    std::cout << "Vendor         : " << glGetString( GL_VENDOR ) << '\n';
    std::cout << "GPU            : " << glGetString( GL_RENDERER ) << '\n';
    std::cout << "OpenGL Version : " << glGetString( GL_VERSION ) << '\n';
    std::cout << "GLSL Version   : " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << '\n';

    glGenVertexArrays( 1, &m_vao );
    glBindVertexArray( m_vao );

    m_program = _create_program( "vs_basic.glsl", "fs_basic.glsl" );

    if( m_program == -1 ){
        Input::get_instace()->force_quit();
        return;
    }

    glUseProgram( m_program );

    glGenTextures( 1, &m_fb_texture );
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, m_fb_texture );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr );

}

void Window::present( void* color_buffer ) {

    glBindTexture( GL_TEXTURE_2D, m_fb_texture );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, color_buffer );

    glClearColor( 0.0f, 0.0f, 1.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glUseProgram( m_program );

    glDrawArrays( GL_TRIANGLES, 0, 3 );

    SDL_Window* window = ( SDL_Window* ) m_blk_window;
    SDL_GL_SwapWindow( window );
}

Window::~Window() {
    SDL_Window* window = ( SDL_Window* ) m_blk_window;
    SDL_DestroyWindow( window );
    SDL_Quit();
}