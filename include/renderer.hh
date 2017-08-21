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
    float4x4* matrix[8];
    Texture* texture[8];
};

struct VertexInput{
    float3 pos;
    float3 normal;
    float2 uv;
};

struct VertexToFragment {
    float4 pos;
    float3 normal;
    float2 uv;
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

    void bind_texture( int32_t id, Texture* t);
    void bind_float4x4( int32_t id, float4x4* matrix );

    void clear( uint32_t color );
    void render_triangle( Triangle t );

    uint32_t* get_color_buffer();

    float4 m_debug_color = float4(1.0f, 0.0f, 1.0f, 1.0f);
private:

    uint32_t _execute_fragment_shader(VertexToFragment vtf[3], float3 inter);

    int32_t m_width = 0;
    int32_t m_height = 0;
    int32_t m_half_width = 0;
    int32_t m_half_height = 0;

    float m_f_width = 0.0f;
    float m_f_height = 0.0f;
    float m_f_half_width = 0.0f;
    float m_f_half_height = 0.0f;

    Uniforms m_uniforms = {};
    std::vector<uint32_t> m_color_buffer;
    std::vector<float> m_depth_buffer;
};