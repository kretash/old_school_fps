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
    const float ratio_x = ( float ) height / ( float ) width;

    auto input = Input::get_instace();

    auto renderer = std::make_shared<Renderer>();
    renderer->create_buffers( width, height );

    auto window = std::make_shared<Window>();
    window->create( width, height, scale );

    Triangle t0, t1;

    {
        const float s = 1.0f;
        const float s_x = -s * ratio_x;
        const float l_x =  s * ratio_x;
        const float s_y = -s;
        const float l_y =  s;

        Vertice v0;
        v0.pos = float3( s_x, s_y, 0.0f );
        v0.normal = float3( 1.0f, 1.0f, 1.0f );
        v0.uv = float2( 0.0f, 0.0f );

        Vertice v1;
        v1.pos = float3( s_x, l_y, 0.0f );
        v1.normal = float3( 0.0f, 0.0f, 0.0f );
        v1.uv = float2( 0.0f, 0.0f );

        Vertice v2;
        v2.pos = float3( l_x, s_y, 0.0f );
        v2.normal = float3(0.0f, 0.0f, 0.0f);
        v2.uv = float2( 0.0f, 0.0f );

        Vertice v3;
        v3.pos = float3( l_x, l_y, 0.0f );
        v3.normal = float3(1.0f, 0.0f, 0.0f);
        v3.uv = float2( 1.0f, 1.0f );

        t0.triangle[0] = v0;
        t0.triangle[1] = v3;
        t0.triangle[2] = v1;

        t1.triangle[0] = v0;
        t1.triangle[1] = v3;
        t1.triangle[2] = v2;
    }

    while( running ) {
        input->update();
        running = !input->quit();

        renderer->clear( 0xff111111 );

        renderer->render_triangle( t0 );
        renderer->render_triangle( t1 );

        auto final_buffer = renderer->get_color_buffer();
        window->present( final_buffer );
    }

    return 0;
}
