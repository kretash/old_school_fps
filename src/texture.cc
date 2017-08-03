#include "texture.hh"

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

void Texture::load( const char* file ) {
    n = 4;
    m_image_data = ( uint32_t* ) stbi_load( file, &x, &y, &n, 4 );
}


float4 Texture::sample( float2 uv ) {

    float fx = ( float ) x;
    float fy = ( float ) y;

    float2 tuv = uv;

    // vertical flip.
    tuv.y = ( 1.0f - tuv.y );

    tuv.x = tuv.x + ( 1.0f / fx )*0.5f;
    tuv.y = tuv.y + ( 1.0f / fy )*0.5f;

    int32_t sx = ( int32_t ) ( tuv.x * fx );
    int32_t sy = ( int32_t ) ( tuv.y * fy );

    sx = def_clamp( sx, 0, x );
    sy = def_clamp( sy, 0, y );

    int32_t index = sy*x + sx;
    uint32_t color = m_image_data[index];

    float4 fcolor = float4
    (
        (float)(color & 0xffff0000 >> 24),
        (float)(color & 0x00ff0000 >> 16),
        (float)(color & 0x0000ff00 >> 8),
        (float)(color & 0x000000ff)
    );

    fcolor = fcolor / 255.0f;

    return fcolor;
}

Texture::~Texture() {
    if( m_image_data != nullptr )
        stbi_image_free( m_image_data );
}