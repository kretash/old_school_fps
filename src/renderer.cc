#include "renderer.hh"
#include "texture.hh"

#include <algorithm>

void Renderer::create_buffers(int32_t width, int32_t height) {

    m_width = width;
    m_height = height;
    m_half_width = width / 2;
    m_half_height = height / 2;

    m_f_width = (float)width;
    m_f_height = (float)height;
    m_f_half_width = (float)m_half_width;
    m_f_half_height = (float)m_half_height;

    m_color_buffer.resize(height * width);
    m_depth_buffer.resize( height * width );

}

void Renderer::clear(uint32_t color) {

    for (size_t i = 0; i < m_color_buffer.size(); ++i)
        m_color_buffer[i] = color;

    for( size_t i = 0; i < m_depth_buffer.size(); ++i )
        m_depth_buffer[i] = 100.0f;//std::numeric_limits<int32_t>::max();

}

void Renderer::bind_texture(int32_t id, Texture* texture) {
    m_uniforms.texture[id] = texture;
}

void Renderer::bind_float4x4(int32_t id, float4x4* matrix) {
    m_uniforms.matrix[id] = matrix;
}

VertexToFragment Renderer::vertex_shader(VertexInput i, Uniforms u) {
    VertexToFragment out;

    const int32_t id = 0;
    float4x4 mvp = *m_uniforms.matrix[id];

    out.pos = mvp * float4(i.pos, 1.0f);
    float4 world_normal = mvp * float4(i.normal, 0.0f);
    out.normal = float3(world_normal.x, world_normal.y, world_normal.z);
    out.normal.normalize();
    out.uv = i.uv;

    return out;
}

FragmentOutput Renderer::fragment_shader(VertexToFragment i, Uniforms u) {
    FragmentOutput out;

    const int32_t id = 0;
    Texture* texture = m_uniforms.texture[id];

    float4 color = float4(1.0f, 0.66f, 0.66f, 1.0f);

    out.frag_color = color * dot( i.normal, float3( 0.5f, 0.0f, 0.5f));
    //out.frag_color = float4(i.uv, 0.0f, 1.0f);
    //out.frag_color = texture->sample(i.uv);

    return out;
}

uint32_t Renderer::_execute_fragment_shader(VertexToFragment vtf[3], float3 inter ) {

    VertexToFragment vtf_interpolated;
    vtf_interpolated.pos = inter.x * vtf[0].pos + inter.y * vtf[1].pos + inter.z * vtf[2].pos;
    vtf_interpolated.normal = inter.x * vtf[0].normal + inter.y * vtf[1].normal + inter.z * vtf[2].normal;
    vtf_interpolated.uv = inter.x * vtf[0].uv + inter.y * vtf[1].uv + inter.z * vtf[2].uv;

    FragmentOutput output = fragment_shader(vtf_interpolated, m_uniforms);

    output.frag_color.clamp(0.0f, 1.0f);

    uint32_t color =
        (uint8_t)(output.frag_color.w * 255.0f) << 24 |
        (uint8_t)(output.frag_color.z * 255.0f) << 16 |
        (uint8_t)(output.frag_color.y * 255.0f) << 8 |
        (uint8_t)(output.frag_color.x * 255.0f);

    return color;
}

void Renderer::render_triangle(Triangle t) {

    VertexToFragment vtf[3];

    for (int32_t i = 0; i < 3; ++i) {
        VertexInput input;

        input.pos = t.triangle[i].pos;
        input.normal = t.triangle[i].normal;
        input.uv = t.triangle[i].uv;

        vtf[i] = vertex_shader(input, m_uniforms);

        vtf[i].pos.x /= vtf[i].pos.w;
        vtf[i].pos.y /= vtf[i].pos.w;
        vtf[i].pos.z /= vtf[i].pos.w;
        vtf[i].pos.w = 1.0f;
    }

    float3 v0 = { vtf[0].pos.x, vtf[0].pos.y, vtf[0].pos.z };
    float3 v1 = { vtf[1].pos.x, vtf[1].pos.y, vtf[1].pos.z };
    float3 v2 = { vtf[2].pos.x, vtf[2].pos.y, vtf[2].pos.z };

    v0.x = (v0.x + 0.0f) *m_f_half_width;
    v0.y = (v0.y + 0.0f) *m_f_half_height;

    v1.x = (v1.x + 0.0f) *m_f_half_width;
    v1.y = (v1.y + 0.0f) *m_f_half_height;

    v2.x = (v2.x + 0.0f) *m_f_half_width;
    v2.y = (v2.y + 0.0f) *m_f_half_height;

    float min_x = std::min(v0.x, std::min(v1.x, v2.x));
    float max_x = std::max(v0.x, std::max(v1.x, v2.x));
    float min_y = std::min(v0.y, std::min(v1.y, v2.y));
    float max_y = std::max(v0.y, std::max(v1.y, v2.y));
    
    max_x = def_clamp(max_x, 0.0f, m_f_width);
    min_x = def_clamp(min_x, 0.0f, m_f_width);
    max_y = def_clamp(max_y, 0.0f, m_f_height);
    min_y = def_clamp(min_y, 0.0f, m_f_height);

    int32_t i_m = (int32_t)min_y * m_width;

    float2 p = { min_x, min_y };
    float3 pos = { min_x, min_y, 0.0f };
    float w0 = 0.0f, w1 = 0.0f, w2 = 0.0f;

    // All floats now
    // convert all to int32_t
    for (float i = min_y; i < max_y; ++i) {
        
        p.y = i;
        pos.y = i;

        for (float e = min_x; e < max_x; ++e) {

            p.x = e;
            pos.x = e;
            
            w0 = orient2d(v1, v2, p);
            w1 = orient2d(v2, v0, p);
            w2 = orient2d(v0, v1, p);

            const float thres = 0.0f;
            if (w0 <= thres && w1 <= thres && w2 <= thres ) {

                int32_t index = i_m + ( int32_t ) e;
                float3 inter = interpolate_floats( pos, v0, v1, v2 );

                float depth = inter.x * v0.z + inter.y * v1.z + inter.z * v2.z;
                if( m_depth_buffer[index] <= depth ) continue;

                uint32_t color = _execute_fragment_shader(vtf, inter );

                m_color_buffer[index] = color; 
                m_depth_buffer[index] = depth;
            }
        }

        i_m += m_width;
    }


}

uint32_t* Renderer::get_color_buffer() {
    return &m_color_buffer[0];
}