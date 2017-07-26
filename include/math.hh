#pragma once

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define clamp(v, i, a) ( min( max(v, i), a) )
#define abs( v ) ( (v) < 0.0f ? -(v) : (v) )
#define mix( x, y, m ) ( x+((y-x)*m) )

struct float2 {
    float2() {}
    float2( float x, float y ) : x( x ), y( y ) {}
    float x = 0.0f, y = 0.0f;
};

struct float3 {
    float3() {}
    float3( float x, float y, float z ) : x( x ), y( y ), z( z ) {}
    float x = 0.0f, y = 0.0f, z = 0.0f;
};

struct float4 {
    float4() {}
    float4( float x, float y, float z, float w ) : x( x ), y( y ), z( z ), w( w ) {}
    float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;
};

struct float4x4 {
    float m[16];
};
