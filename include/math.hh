#pragma once

#include <math.h>
#include <algorithm>

//#define abs( v ) ( (v) < 0.0f ? -(v) : (v) )
//#define max(x, y) (((x) > (y)) ? (x) : (y))
//#define min(x, y) (((x) < (y)) ? (x) : (y))
#define clamp(v, i, a) ( std::min( std::max((float)v, (float)i), (float)a) )
#define mix( x, y, m ) ( x+((y-x)*m) )

struct float2 {
    float2() {}
    float2( float x, float y ) : x( x ), y( y ) {}
    float x = 0.0f, y = 0.0f;
};

struct float3 {
    float3() {}
    float3(float x, float y, float z) : x(x), y(y), z(z) {}
    float3( float2 v, float z ) : x( v.x ), y( v.y ), z( z ) {}
    float x = 0.0f, y = 0.0f, z = 0.0f;

    float3 operator+( const float3& o ) {
        return float3( this->x + o.x, this->y + o.y, this->z + o.z );
    }

    float3 operator-( const float3& o ) {
        return float3( this->x - o.x, this->y - o.y, this->z - o.z );
    }

    float3 operator*( const float& o ) {
        return float3( this->x * o, this->y * o, this->z  * o );
    }
    
    float3 operator*( const float3& o ) {
        return float3( this->x * o.x, this->y * o.y, this->z * o.z);
    }

    float3 operator/( const float& o ) {
        return float3( this->x / o, this->y / o, this->z / o );
    }

};

float3 operator*( const float& lhs, const float3& rhs );

struct float4 {
    float4() {}
    float4( float x, float y, float z, float w ) : x( x ), y( y ), z( z ), w( w ) {}
    float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;
};

struct float4x4 {
    float m[16];
};

float length( float3 vec );
float3 normalize(float3 vec);
float orient2d( const float3 a, const float3 b, const float2 c );
float3 interpolate_floats(float3 pos, float3 x1, float3 x2, float3 x3);