#include "renderer.hh"

void Renderer::create_buffers(int32_t width, int32_t height){

    for( int32_t i = 0; i < width; ++i ){
        for( int32_t e = 0; e < height; ++e ){

            float f_i = (float)i;
            float f_e = (float)e;
            float f_width = (float)width;
            float f_height = (float)height;

            uint8_t r = (uint8_t)( (f_i/f_width)*255.0f );
            uint8_t g = (uint8_t)( (f_e/f_height)*255.0f );
            uint8_t b = (uint8_t)( 0 );
            uint8_t a = (uint8_t)( 255 );

            uint32_t color = r << 24 | g << 16 | b << 8 | a ;

            m_color_buffer.push_back( color );


        }
    }
}

uint32_t* Renderer::get_color_buffer(){
    return &m_color_buffer[0];
}