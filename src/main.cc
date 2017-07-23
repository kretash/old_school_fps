//
//  main.cpp
//  old_school_fps
//
//  Created by carlos on 7/23/17.
//  Copyright © 2017 kretash. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "input.hh"
#include "gl_helper.hh"
#include "renderer.hh"

#define DEBUG 1

int main(int argc, const char *argv[])
{

	bool running = true;
	const int32_t width = 320;
	const int32_t height = 240;
	const int32_t scale = 3;

	int sdl_init_ = SDL_Init(SDL_INIT_VIDEO);
	if (sdl_init_ < 0)
		std::cout << "SDL error ->" << SDL_GetError() << std::endl;

	SDL_Window *window = SDL_CreateWindow("renderer", SDL_WINDOWPOS_CENTERED,
						SDL_WINDOWPOS_CENTERED, width * scale, height * scale, SDL_WINDOW_OPENGL);


	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetSwapInterval(1);

	SDL_GLContext gl_context = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	GLenum glew_init_;
	if ((glew_init_ = glewInit()) != GLEW_OK)
	{
		std::cout << glewGetErrorString(glew_init_) << std::endl;
		assert(false && "GLEW INIT FAILED");
	}

#if DEBUG
	// SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

	// glEnable(GL_DEBUG_OUTPUT);
	// glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	// glDebugMessageCallback(opengl_error_callback, nullptr);
	// glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);

	std::cout << "Vendor         : " << glGetString(GL_VENDOR) << '\n';
	std::cout << "GPU            : " << glGetString(GL_RENDERER) << '\n';
	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << '\n';
	std::cout << "GLSL Version   : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';

#endif

	GLuint vao = 0;
	GLint program = 0;
	GLuint texture = 0;
	GLuint fb_texture = 0;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	program = _create_program("vs_basic.glsl", "fs_basic.glsl");
	glUseProgram(program);

	glGenTextures(1, &fb_texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fb_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	auto input = Input::get_instace();
	auto renderer = std::make_shared<Renderer>();
	renderer->create_buffers(width, height);

	while (running)
	{
		input->update();
		running = !input->quit();

		glBindTexture( GL_TEXTURE_2D, fb_texture );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		 renderer->get_color_buffer() );

		glClearColor( 0.0f, 0.0f, 1.0f, 0.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glUseProgram(program);

		glDrawArrays( GL_TRIANGLES, 0, 3 );

		SDL_GL_SwapWindow(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
