#include "renderer.hh"
#include <math.h>
#include <algorithm>

void Renderer::create_buffers( int32_t width, int32_t height ) {

    m_width = width;
    m_height = height;

    m_color_buffer.resize( height * width );

#if false
    for( int32_t e = 0; e < height; ++e ) {
        for( int32_t i = 0; i < width; ++i ) {

            float f_i = ( float ) i;
            float f_e = ( float ) e;
            float f_width = ( float ) width;
            float f_height = ( float ) height;

            uint8_t r = ( uint8_t ) ( ( f_i / f_width )*255.0f );
            uint8_t g = ( uint8_t ) ( ( f_e / f_height )*255.0f );
            uint8_t b = ( uint8_t ) ( 0 );
            uint8_t a = ( uint8_t ) ( 255 );

            uint32_t color = a << 24 | b << 16 | g << 8 | r;

            //color = 255 << 8;

            m_color_buffer[e*width + i] = ( color );


}
    }
#endif
}

void Renderer::clear( uint32_t color ) {

    for( size_t i = 0; i < m_color_buffer.size(); ++i )
        m_color_buffer[i] = color;

}

float orient2d( const float3 a, const float3 b, const float2 c ) {
    return ( b.x - a.x )*( c.y - a.y ) - ( b.y - a.y )*( c.x - a.x );
}

void Renderer::render_triangle( float3 x1, float3 x2, float3 x3 ) {

    float3 v1 = { x1.x, x1.y, x1.z };
    float3 v2 = { x2.x, x2.y, x2.z };
    float3 v3 = { x3.x, x3.y, x3.z };

    float max_x = max( v1.x, max( v2.x, v3.x ) );
    float min_x = min( v1.x, min( v2.x, v3.x ) );
    float max_y = max( v1.y, max( v2.y, v3.y ) );
    float min_y = min( v1.y, min( v2.y, v3.y ) );

    max_x = ( max_x + 1.0f ) * m_width / 2.0f;
    min_x = ( min_x + 1.0f ) * m_width / 2.0f;
    max_y = ( max_y + 1.0f ) * m_height / 2.0f;
    min_y = ( min_y + 1.0f ) * m_height / 2.0f;

    v1.x = ( v1.x + 1.0f ) *m_width*0.5f;
    v1.y = ( v1.y + 1.0f ) *m_height*0.5f;

    v2.x = ( v2.x + 1.0f ) *m_width*0.5f;
    v2.y = ( v2.y + 1.0f ) *m_height*0.5f;

    v3.x = ( v3.x + 1.0f ) *m_width*0.5f;
    v3.y = ( v3.y + 1.0f ) *m_height*0.5f;

    max_x = clamp( max_x, 0, m_width );
    min_x = clamp( min_x, 0, m_width );
    max_y = clamp( max_y, 0, m_height );
    min_y = clamp( min_y, 0, m_height );

    for( int i = ( int ) min_y; i < max_y; ++i ) {

        int i_m = i*m_width;

        for( int e = ( int ) min_x; e < max_x; ++e ) {

            float2 p = { ( float ) e, ( float ) ( i ) };
            float3 pos = { ( float ) e, ( float ) i, 0.0f };

            float w0 = orient2d( v2, v3, p );
            float w1 = orient2d( v3, v1, p );
            float w2 = orient2d( v1, v2, p );

            if( w0 >= 0.0f && w1 >= 0.0f && w2 >= 0.0f ) {
                unsigned int color = 0xff00ff00;
                m_color_buffer[i_m + e] = color;
            } else if( w0 <= 0.0f && w1 <= 0.0f && w2 <= 0.0f ) {
                unsigned int color = 0xff00ffff;
                m_color_buffer[i_m + e] = color;
            }

        }

    }


}

uint32_t* Renderer::get_color_buffer() {
    return &m_color_buffer[0];
}