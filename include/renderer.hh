#pragma once 

#include <stdint.h>
#include <vector>

#include "math.hh"

class Texture;

class Vertice{
public:
    float3 pos;
    float3 normal;
    float2 uv;
};

class Triangle{
public:
    Vertice triangle[3];
};

class Uniforms{
public:
    float4x4 mvp;
};

struct VertexInput{
    float3 pos;
    float3 normal;
    float2 uv;
};

struct VertexToFragment {
    float4 pos;
    float4 normal;
    float4 uv;
};

struct FragmentOutput {
    float4 frag_color;
};

class Renderer {
public:
    Renderer() {};
    ~Renderer() {};

    void create_buffers( int32_t width, int32_t height );

    VertexToFragment vertex_shader( VertexInput i, Uniforms u );
    FragmentOutput fragment_shader( VertexToFragment i, Uniforms u );

    void bind(Texture* t);
    void bind_mvp( float4x4 mvp );

    void clear( uint32_t color );

    void render_triangle( Triangle t );

    uint32_t* get_color_buffer();
private:
    int32_t m_width;
    int32_t m_height;
    Uniforms m_uniforms = {};
    Texture* m_bind_texture = nullptr;
    std::vector<uint32_t> m_color_buffer;
};