//
//  main.cpp
//  old_school_fps
//
//  Created by carlos on 7/23/17.
//  Copyright © 2017 kretash. All rights reserved.
//

#include "input.hh"
#include "renderer.hh"
#include "window.hh"

int main(int argc, char *argv[])
{
	bool running = true;
	const int32_t width = 320;
	const int32_t height = 240;
	const int32_t scale = 3;

	auto input = Input::get_instace();

	auto renderer = std::make_shared<Renderer>();
	renderer->create_buffers(width, height);

	auto window = std::make_shared<Window>();
    window->create(width, height, scale);

	while (running)
	{
		input->update();
		running = !input->quit();

        renderer->clear( 0xff111111 );

        renderer->render_triangle( float3( 0.5f, 0.25f, 0.0f), float3( 0.25f, 0.75f, 0.0f ), float3( 0.75f, 0.75f, 0.0f ) );

        auto final_buffer = renderer->get_color_buffer();
        window->present( final_buffer );
	}

	return 0;
}
