#include "texture.hh"

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

void Texture::load( const char* file ) {
    n = 4;
    m_image_data = ( uint32_t* ) stbi_load( file, &x, &y, &n, 4 );
}


uint32_t Texture::sample( float2 uv ) {

    //float scale_x = ( ( float ) x - 1.0f ) / ( float ) x;
    //float scale_y = ( ( float ) y - 1.0f ) / ( float ) y;

    int32_t sx = ( int32_t ) ( uv.x * ( float ) (x-1)  );
    int32_t sy = ( int32_t ) ( (1.0f-uv.y) * ( float ) (y-1));

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