#pragma once 

#include <stdint.h>
#include <vector>

#include "math.hh"

class Vertice{
public:
    float3 pos;
    float3 normal;
    float2 uv;
};

class Triangle{
public:
    Vertice triangle[3];
    
    // waste to have it here.
    //float4x4 model;
};

class Renderer {
public:
    Renderer() {};
    ~Renderer() {};

    void create_buffers( int32_t width, int32_t height );

    void clear( uint32_t color );

    void render_triangle( Triangle t );

    uint32_t* get_color_buffer();
private:
    int32_t m_width;
    int32_t m_height;
    std::vector<uint32_t> m_color_buffer;
};