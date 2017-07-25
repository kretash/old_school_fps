#pragma once 

#include <stdint.h>
#include <vector>

class Renderer{
public:
    Renderer(){};
    ~Renderer(){};

    void create_buffers( int32_t width, int32_t height );


    uint32_t* get_color_buffer();
private:
    std::vector<uint32_t> m_color_buffer;
};