//
//  main.cpp
//  old_school_fps
//
//  Created by carlos on 7/23/17.
//  Copyright © 2017 kretash. All rights reserved.
//

#include "input.hh"
#include "renderer.hh"
#include "gl_renderer.hh"

int main(int argc, char *argv[])
{
	bool running = true;
	const int32_t width = 320;
	const int32_t height = 240;
	const int32_t scale = 3;

	auto input = Input::get_instace();

	auto renderer = std::make_shared<Renderer>();
	renderer->create_buffers(width, height);

	auto gl_renderer = std::make_shared<GLRenderer>();
	gl_renderer->create(width, height, scale);

	while (running)
	{
		input->update();
		running = !input->quit();

		gl_renderer->render( renderer->get_color_buffer() );
	}

	return 0;
}
