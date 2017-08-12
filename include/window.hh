#pragma once

#include <stdint.h>

class Window {
public:
    Window();
    ~Window();

    void create( int32_t width = 320, int32_t height = 240, int32_t scale = 3 );
    void new_frame();
    void present( void* color_buffer );

private:
    void* m_blk_window = nullptr;

    int32_t m_program = 0;
    int32_t m_width = 0;
    int32_t m_height = 0;
    uint32_t m_vao = 0;
    uint32_t m_texture = 0;
    uint32_t m_fb_texture = 0;
};