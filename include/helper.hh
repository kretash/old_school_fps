#pragma once

#include <stdint.h>
#include "math.hh"

static inline uint32_t create_color( float r, float g, float b, float a ) {

    uint32_t color =
        ( uint8_t ) ( def_clamp( a * 255.0f, 0.0f, 255.0f ) ) << 24 |
        ( uint8_t ) ( def_clamp( b * 255.0f, 0.0f, 255.0f ) ) << 16 |
        ( uint8_t ) ( def_clamp( g * 255.0f, 0.0f, 255.0f ) ) << 8 |
        ( uint8_t ) ( def_clamp( r * 255.0f, 0.0f, 255.0f ) );

    return color;
}


static inline uint32_t create_color( float r, float g, float b ) {
    return create_color( r, g, b, 1.0f );
}

static inline uint32_t create_color( float4 color ) {
    return create_color( color.x, color.y, color.z, color.w );
}
