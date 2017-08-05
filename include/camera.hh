#pragma once

#include "math.hh"
#include "input.hh"

#include <iostream>

class Camera {
public:

    Camera( int32_t width, int32_t height ) {
        m_proj.perspective( 75.0f, ( float ) width / ( float ) height, 0.1f, 100.0f );
    }
    ~Camera() {}

    void update() {

        auto input = Input::get_instace();

        //std::cout << m_movedir.x << "__" << m_movedir.y << "\n";
        
        mouse this_mouse = input->get_mouse();
        if( this_mouse.lmb && !m_drag_camera ) {
            m_last_mouse = this_mouse;
            m_drag_camera = true;
        } else if( this_mouse.lmb && m_drag_camera ) {
            m_movedir.x -= ( m_last_mouse.x - this_mouse.x ) * m_mouse_speed;
            m_movedir.y -= ( m_last_mouse.y - this_mouse.y ) * m_mouse_speed;
            m_last_mouse = this_mouse;
        } else {
            m_drag_camera = false;
        }

        if( input->key_down( SDLK_UP ) ) {
            m_movedir.y -= m_dir_speed;
        }
        if( input->key_down( SDLK_DOWN ) ) {
            m_movedir.y += m_dir_speed;
        }
        if( input->key_down( SDLK_RIGHT ) ) {
            m_movedir.x += m_dir_speed;
        }
        if( input->key_down( SDLK_LEFT ) ) {
            m_movedir.x -= m_dir_speed;
        }

        m_direction.x = sinf( -m_movedir.x );
        m_direction.z = cosf( -m_movedir.x );
        m_direction.y = tanf( -m_movedir.y );

        if( input->key_down( SDLK_w ) ) {
            m_eye = m_eye + ( m_direction*m_movement_speed );
        }
        if( input->key_down( SDLK_s ) ) {
            m_eye = m_eye - ( m_direction*m_movement_speed );
        }
        if( input->key_down( SDLK_a ) ) {
            float3 strafe = float3( -m_direction.z, 0.0f, m_direction.x );
            m_eye = m_eye - ( strafe*m_movement_speed );
        }
        if( input->key_down( SDLK_d ) ) {
            float3 strafe = float3( -m_direction.z, 0.0f, m_direction.x );
            m_eye = m_eye + ( strafe*m_movement_speed );
        }
        if( input->key_down( SDLK_q ) ) {
            float3 high = float3( 0.0f, -1.0f, 0.0f );
            m_eye = m_eye + ( high*m_movement_speed );
        }
        if( input->key_down( SDLK_e ) ) {
            float3 high = float3( 0.0f, 1.0f, 0.0f );
            m_eye = m_eye + ( high*m_movement_speed );
        }

        m_view.look_at( m_eye, m_eye + m_direction, float3( 0.0f, -1.0f, 0.0f ) );
    }
    float4x4 get_view() const { return m_view; }
    float4x4 get_proj() const { return m_proj; }

private:

    const float m_movement_speed = 0.1f;
    const float m_dir_speed = 0.01f;
    const float m_mouse_speed = 0.001f;

#if 1 // camera for Lucy
    float2 m_movedir = float2( -0.32f, -0.08f );
    float3 m_eye = float3( 0.0f, 3.0f, -15.0f );
#else
    float2 m_movedir = float2( -0.32f, -0.08f );
    float3 m_eye = float3( 0.0f, 3.0f, -15.0f );
#endif

    float3 m_direction = float3( 0.0f, 0.0f, 0.0f );
    float4x4 m_view = float4x4( 1.0f );
    float4x4 m_proj = float4x4( 1.0f );

    mouse m_last_mouse;
    bool m_drag_camera = false;

};