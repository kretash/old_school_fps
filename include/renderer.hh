#pragma once 

#include <stdint.h>
#include <vector>

#include "math.hh"

class Renderer {
public:
    Renderer() {};
    ~Renderer() {};

    void create_buffers( int32_t width, int32_t height );

    void clear( uint32_t color );

    void render_triangle( float3 x1, float3 x2, float3 x3 );

    uint32_t* get_color_buffer();
private:
    int32_t m_width;
    int32_t m_height;
    std::vector<uint32_t> m_color_buffer;
};