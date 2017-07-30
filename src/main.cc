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

int main( int argc, char *argv[] ) {

    bool running = true;
    const int32_t width = 320;
    const int32_t height = 240;
    const int32_t scale = 3;

    auto input = Input::get_instace();

    auto renderer = std::make_shared<Renderer>();
    renderer->create_buffers( width, height );

    auto window = std::make_shared<Window>();
    window->create( width, height, scale );

    Vertice v0;
    v0.pos = float3( 0.0f, 0.5f, 0.0f );
    v0.normal = float3( 0.0f, 0.0f, 1.0f );
    v0.uv = float2( 0.0f, 0.0f );

    Vertice v1;
    v1.pos = float3( -0.5f, -0.5f, 0.0f );
    v1.normal = float3( 0.0f, 0.0f, 1.0f );
    v1.uv = float2( 0.0f, 0.0f );

    Vertice v2;
    v2.pos = float3( 0.5f, -0.5f, 0.0f );
    v2.normal = float3( 0.0f, 0.0f, 1.0f );
    v2.uv = float2( 0.0f, 0.0f );

    Triangle t;
    t.triangle[0] = v0;
    t.triangle[1] = v1;
    t.triangle[2] = v2;


    while( running ) {
        input->update();
        running = !input->quit();

        renderer->clear( 0xff111111 );

        renderer->render_triangle( t );

        auto final_buffer = renderer->get_color_buffer();
        window->present( final_buffer );
    }

    return 0;
}
