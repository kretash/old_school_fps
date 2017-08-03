#include "math.hh"

float2 operator*(const float& lhs, const float2& rhs) {
    return float2(rhs.x * lhs, rhs.y * lhs);
}

float3 operator*( const float& lhs, const float3& rhs ) {
    return float3( rhs.x * lhs, rhs.y * lhs, rhs.z  * lhs );
}

void float3::normalize() {
    float m = sqrtf( x * x + y * y + z * z );
    x /= m;    y /= m;    z /= m;
}

inline float float3::length() {
    float square_me = x * x + y * y + z * z;
    return sqrtf( square_me );
}

float orient2d( const float3 a, const float3 b, const float2 c ) {
    return ( b.x - a.x )*( c.y - a.y ) - ( b.y - a.y )*( c.x - a.x );
}

float3 half(float3 a, float3 b) {
    float3 sum = a + b;
    sum.normalize();
    return sum;
}

float3 normal(const float3 f) {
    float3 normal = f;
    float m = f.x * f.x + f.y * f.y + f.z * f.z;
    if (m == 0.0f) return f;
    m = 1.0f / sqrtf(m);
    normal.x *= m;
    normal.y *= m;
    normal.z *= m;
    return normal;
}

float dot(const float3 d, const float3 f) {
    float dot = d.x * f.x + d.y * f.y + d.z * f.z;
    return dot;
}

float3 cross(const float3 d, const float3 f) {
    float3 r;
    r.x = d.y * f.z - d.z * f.y;
    r.y = d.z * f.x - d.x * f.z;
    r.z = d.x * f.y - d.y * f.x;
    return r;
}

float3 interpolate_floats( float3 pos, float3 x1, float3 x2, float3 x3 ) {

    float a_area = 0.0f;
    float x_area = 0.0f;
    float y_area = 0.0f;
    float z_area = 0.0f;

    const float l1 = abs( ( x2 - x1 ).length() );
    const float l2 = abs( ( x2 - x3 ).length() );
    const float l3 = abs( ( x3 - x1 ).length() );
    const float lpos1 = abs( ( pos - x1 ).length() );
    const float lpos2 = abs( ( pos - x2 ).length() );
    const float lpos3 = abs( ( pos - x3 ).length() );

    {
        float s = ( l1 + l2 + l3 )*0.5f;
        a_area = sqrtf( s * ( s - l1 ) * ( s - l2 ) * ( s - l3 ) );
    }
    {
        float s = ( lpos2 + l2 + lpos3 )*0.5f;
        x_area = sqrtf( s * ( s - lpos2 ) * ( s - l2 ) * ( s - lpos3 ) );
    }
    {
        float s = ( lpos1 + lpos3 + l3 )*0.5f;
        y_area = sqrtf( s * ( s - lpos1 ) * ( s - lpos3 ) * ( s - l3 ) );
    }
    {
        float s = ( l1 + lpos1 + lpos2 )*0.5f;
        z_area = sqrtf( s * ( s - l1 ) * ( s - lpos1 ) * ( s - lpos2 ) );
    }

    return float3( x_area / a_area, y_area / a_area, z_area / a_area );

}

void float4::normalize() {
    float m = sqrtf(x * x + y * y + z * z + w * w);
    x /= m;    y /= m;    z /= m;   w /= m;
}

void float4::clamp(float min, float max) {
    x = def_clamp(x, min, max);
    y = def_clamp(y, min, max);
    z = def_clamp(z, min, max);
    w = def_clamp(w, min, max);
}

float4 operator*(const float& lhs, const float4& rhs) {
    return float4(rhs.x * lhs, rhs.y * lhs, rhs.z  * lhs, rhs.w  * lhs);
}

float4x4 mult( const float4x4& l, const float4x4& r ) {
    float4x4 result;

    result.m[0] = l.m[0] * r.m[0] + l.m[4] * r.m[1] + l.m[8] * r.m[2] + l.m[12] * r.m[3];
    result.m[1] = l.m[1] * r.m[0] + l.m[5] * r.m[1] + l.m[9] * r.m[2] + l.m[13] * r.m[3];
    result.m[2] = l.m[2] * r.m[0] + l.m[6] * r.m[1] + l.m[10] * r.m[2] + l.m[14] * r.m[3];
    result.m[3] = l.m[3] * r.m[0] + l.m[7] * r.m[1] + l.m[11] * r.m[2] + l.m[15] * r.m[3];

    result.m[4] = l.m[0] * r.m[4] + l.m[4] * r.m[5] + l.m[8] * r.m[6] + l.m[12] * r.m[7];
    result.m[5] = l.m[1] * r.m[4] + l.m[5] * r.m[5] + l.m[9] * r.m[6] + l.m[13] * r.m[7];
    result.m[6] = l.m[2] * r.m[4] + l.m[6] * r.m[5] + l.m[10] * r.m[6] + l.m[14] * r.m[7];
    result.m[7] = l.m[3] * r.m[4] + l.m[7] * r.m[5] + l.m[11] * r.m[6] + l.m[15] * r.m[7];

    result.m[8] = l.m[0] * r.m[8] + l.m[4] * r.m[9] + l.m[8] * r.m[10] + l.m[12] * r.m[11];
    result.m[9] = l.m[1] * r.m[8] + l.m[5] * r.m[9] + l.m[9] * r.m[10] + l.m[13] * r.m[11];
    result.m[10] = l.m[2] * r.m[8] + l.m[6] * r.m[9] + l.m[10] * r.m[10] + l.m[14] * r.m[11];
    result.m[11] = l.m[3] * r.m[8] + l.m[7] * r.m[9] + l.m[11] * r.m[10] + l.m[15] * r.m[11];

    result.m[12] = l.m[0] * r.m[12] + l.m[4] * r.m[13] + l.m[8] * r.m[14] + l.m[12] * r.m[15];
    result.m[13] = l.m[1] * r.m[12] + l.m[5] * r.m[13] + l.m[9] * r.m[14] + l.m[13] * r.m[15];
    result.m[14] = l.m[2] * r.m[12] + l.m[6] * r.m[13] + l.m[10] * r.m[14] + l.m[14] * r.m[15];
    result.m[15] = l.m[3] * r.m[12] + l.m[7] * r.m[13] + l.m[11] * r.m[14] + l.m[15] * r.m[15];

    return result;
}

float4 mult_v( const float4x4& m, const float4& v ) {
    float r[4];

    for( unsigned int i = 0; i < 4; ++i ) {
        r[i] = ( m.m[0 + i] * v.x ) + ( m.m[4 + i] * v.y ) +
            ( m.m[8 + i] * v.z ) + ( m.m[12 + i] * v.w );
    }

    return float4( r[0], r[1], r[2], r[3] );
}

float4 operator*( const float4x4& lhs, const float4& rhs ) {
    return mult_v( lhs, rhs );
}

float4x4 operator*( const float4x4& lhs, const float4x4& rhs ) {
    return mult( lhs, rhs );
}

void float4x4::initialize( float i ){
    memset( m, 0, sizeof( float ) * 16 );
    m[0] = i;
    m[5] = i;
    m[10] = i;
    m[15] = i;
}

void float4x4::translate(float x, float y, float z ) {
    m[12] = x;
    m[13] = y;
    m[14] = z;
}

void float4x4::rotate_y( float a ) {
    m[0] = cosf( a );
    m[2] = sinf( a );
    m[8] = -sinf( a );
    m[10] = cosf( a );
}

void float4x4::prespective( float fov, float aspect_ratio, float n, float f ) {
    float tan_fov = tanf( fov / 2.0f );
    this->identity();
    m[0] = 1.0f / ( aspect_ratio*tan_fov );
    m[5] = 1.0f / tan_fov;
    m[10] = -( f + n ) / ( f - n );
    m[11] = -1.0f;
    m[14] = -( 2.0f * f * n ) / ( f - n );
}