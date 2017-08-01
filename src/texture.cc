#include "texture.hh"

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

void Texture::load(const char* file) {
    n = 4;
    m_image_data = (uint32_t*) stbi_load(file, &x, &y, &n, 4);
}


uint32_t Texture::sample(float2 uv) {

    int32_t sx = (int32_t)(uv.x * (float)x);
    int32_t sy = (int32_t)(uv.y * (float)y);

    sx = clamp(sx, 0, x);
    sy = clamp(sy, 0, y);

    uint32_t color = m_image_data[sy*x + sx];

    //if (color == 0xff) color = 0xffffffff;

    return color;
}

Texture::~Texture() {
    if (m_image_data != nullptr)
        stbi_image_free(m_image_data);
}