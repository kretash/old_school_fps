#pragma once

#include <stdint.h>
//#include <string>
#include "math.hh"

class Texture {
public:
    Texture() {};
    ~Texture();

    void load(const char* file);
    uint32_t sample(float2 uv);

    uint32_t* m_image_data = nullptr;
    int32_t x = 0;
    int32_t y = 0;
    int32_t n = 0;
};