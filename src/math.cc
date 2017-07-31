#include <math.h>

#include "math.hh"


float3 operator*(const float& lhs, const float3& rhs) {
    return float3(rhs.x * lhs, rhs.y * lhs, rhs.z  * lhs);
}

inline float length(const float3 f) {
    float square_me =
        f.x * f.x +
        f.y * f.y +
        f.z * f.z;
    return sqrtf(square_me);
}

float orient2d(const float3 a, const float3 b, const float2 c) {
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

float3 interpolate_floats(float3 pos, float3 x1, float3 x2, float3 x3) {

    float a_area = 0.0f;
    float x_area = 0.0f;
    float y_area = 0.0f;
    float z_area = 0.0f;

    float3 x1x2 = float3(x2.x - x1.x, x2.y - x1.y, 0.0f);
    float3 x1x3 = float3(x2.x - x3.x, x2.y - x3.y, 0.0f);
    float3 x3x1 = float3(x3.x - x1.x, x3.y - x1.y, 0.0f);
    float3 posx1 = float3(pos.x - x1.x, pos.y - x1.y, 0.0f);
    float3 posx2 = float3(pos.x - x2.x, pos.y - x2.y, 0.0f);
    float3 posx3 = float3(pos.x - x3.x, pos.y - x3.y, 0.0f);

    const float l1 = abs(length(x2 - x1));
    const float l2 = abs(length(x2 - x3));
    const float l3 = abs(length(x3 - x1));
    const float lpos1 = abs(length(pos - x1));
    const float lpos2 = abs(length(pos - x2));
    const float lpos3 = abs(length(pos - x3));

    {
        float s = (l1 + l2 + l3)*0.5f;
        a_area = sqrtf(s * (s - l1) * (s - l2) * (s - l3));
    }
    {
        float s = (l1 + lpos1 + lpos2)*0.5f;
        x_area = sqrtf(s * (s - l1) * (s - lpos1) * (s - lpos2));
    }
    {
        float s = (lpos2 + l2 + lpos3)*0.5f;
        y_area = sqrtf(s * (s - lpos2) * (s - l2) * (s - lpos3));
    }
    {
        float s = (lpos1 + lpos3 + l3)*0.5f;
        z_area = sqrtf(s * (s - lpos1) * (s - lpos3) * (s - l3));
    }

    return float3(x_area / a_area, y_area / a_area, z_area / a_area);
}