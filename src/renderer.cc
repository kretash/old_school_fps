#include "renderer.hh"
#include "texture.hh"

void Renderer::create_buffers( int32_t width, int32_t height ) {

    m_width = width;
    m_height = height;

    m_color_buffer.resize( height * width );

}

void Renderer::clear( uint32_t color ) {

    for( size_t i = 0; i < m_color_buffer.size(); ++i )
        m_color_buffer[i] = color;

}

void Renderer::bind(Texture* t) {
    m_bind_texture = t;
}

void Renderer::bind_mvp( float4x4 mvp ) {
    m_uniforms.mvp = mvp;
}

VertexToFragment Renderer::vertex_shader( VertexInput i, Uniforms u ){
    VertexToFragment out;

    out.pos = u.mvp * float4(i.pos, 1.0f);

    return out;
}

FragmentOutput Renderer::fragment_shader( VertexToFragment i, Uniforms u ){
    FragmentOutput out;

    return out;
}

void Renderer::render_triangle( Triangle t ) {
    
    VertexToFragment vtf[3];

    for( int32_t i = 0; i < 3; ++i ){
        VertexInput input;

        input.pos = t.triangle[i].pos;
        input.normal = t.triangle[i].normal;
        input.uv = t.triangle[i].uv;

        vtf[i] = vertex_shader( input, m_uniforms );

        vtf[i].pos.x /= vtf[i].pos.w;
        vtf[i].pos.y /= vtf[i].pos.w;
        vtf[i].pos.z /= vtf[i].pos.w;
        vtf[i].pos.w = 1.0f;
    }

    float3 v0 = { vtf[0].pos.x, -1.0f * vtf[0].pos.y, vtf[0].pos.z };
    float3 v1 = { vtf[1].pos.x, -1.0f * vtf[1].pos.y, vtf[1].pos.z };
    float3 v2 = { vtf[2].pos.x, -1.0f * vtf[2].pos.y, vtf[2].pos.z };

    float max_x = std::max( v0.x, std::max( v1.x, v2.x ) );
    float min_x = std::min( v0.x, std::min( v1.x, v2.x ) );
    float max_y = std::max( v0.y, std::max( v1.y, v2.y ) );
    float min_y = std::min( v0.y, std::min( v1.y, v2.y ) );

    max_x = ( max_x + 1.0f ) * m_width / 2.0f;
    min_x = ( min_x + 1.0f ) * m_width / 2.0f;
    max_y = ( max_y + 1.0f ) * m_height / 2.0f;
    min_y = ( min_y + 1.0f ) * m_height / 2.0f;

    v0.x = ( v0.x + 1.0f ) *m_width*0.5f;
    v0.y = ( v0.y + 1.0f ) *m_height*0.5f;

    v1.x = ( v1.x + 1.0f ) *m_width*0.5f;
    v1.y = ( v1.y + 1.0f ) *m_height*0.5f;

    v2.x = ( v2.x + 1.0f ) *m_width*0.5f;
    v2.y = ( v2.y + 1.0f ) *m_height*0.5f;

    max_x = clamp( max_x, 0.0f, (float)m_width );
    min_x = clamp( min_x, 0.0f, (float)m_width );
    max_y = clamp( max_y, 0.0f, (float)m_height );
    min_y = clamp( min_y, 0.0f, (float)m_height );

    for( int i = ( int ) min_y; i < max_y; ++i ) {

        int i_m = i*m_width;

        for( int e = ( int ) min_x; e < max_x; ++e ) {

            float2 p = { ( float ) e, ( float ) ( i ) };
            float3 pos = { ( float ) e, ( float ) i, 0.0f };

            float w0 = orient2d( v1, v2, p );
            float w1 = orient2d( v2, v0, p );
            float w2 = orient2d( v0, v1, p );

            float3 c0 = float3(t.triangle[0].uv, 0.0f);
            float3 c1 = float3(t.triangle[1].uv, 0.0f);
            float3 c2 = float3(t.triangle[2].uv, 0.0f);

            float3 inter = interpolate_floats( pos, v0, v1, v2 );

            float3 fcolor = inter.x * c0 + inter.y * c1 + inter.z * c2;

            fcolor.x = isnan(fcolor.x) ? 0 : fcolor.x;
            fcolor.y = isnan(fcolor.y) ? 0 : fcolor.y;
            fcolor.z = isnan(fcolor.z) ? 0 : fcolor.z;

            uint32_t color = 0;

            if (m_bind_texture != nullptr) {
                float2 uvs = float2(fcolor.x, fcolor.y);
                color = m_bind_texture->sample( uvs );
            }

            if( w0 >= 0.0f && w1 >= 0.0f && w2 >= 0.0f ) {
                //backface here?
                m_color_buffer[i_m + e] = color;
            } else if( w0 <= 0.0f && w1 <= 0.0f && w2 <= 0.0f ) {
               m_color_buffer[i_m + e] = color;
            }

        }

    }


}

uint32_t* Renderer::get_color_buffer() {
    return &m_color_buffer[0];
}