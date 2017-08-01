#include "texture.hh"

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

void Texture::load( const char* file ) {
    n = 4;
    m_image_data = ( uint32_t* ) stbi_load( file, &x, &y, &n, 4 );
}


uint32_t Texture::sample( float2 uv ) {

    float fx = ( float ) x;
    float fy = ( float ) y;

    float2 tuv = uv;

    // vertical flip.
    tuv.y = ( 1.0f - tuv.y );

    tuv.x = tuv.x + ( 1.0f / fx )*0.5f;
    tuv.y = tuv.y + ( 1.0f / fy )*0.5f;

    int32_t sx = ( int32_t ) ( tuv.x * fx );
    int32_t sy = ( int32_t ) ( tuv.y * fy );

    sx = clamp( sx, 0, x );
    sy = clamp( sy, 0, y );

    int32_t index = sy*x + sx;
    uint32_t color = m_image_data[index];

    return color;
}

Texture::~Texture() {
    if( m_image_data != nullptr )
        stbi_image_free( m_image_data );
}