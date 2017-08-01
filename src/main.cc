//
//  main.cpp
//  old_school_fps
//
//  Created by carlos on 7/23/17.
//  Copyright © 2017 kretash. All rights reserved.
//

#include <iostream>

#include "input.hh"
#include "renderer.hh"
#include "window.hh"
#include "texture.hh"

#define TINYOBJLOADER_IMPLEMENTATION
#include "external/tiny_obj_loader.h"

int main( int argc, char *argv[] ) {

    bool running = true;
    const int32_t width = 512;
    const int32_t height = 256;
    const int32_t scale = 1;
    const float ratio_x = ( float ) height / ( float ) width;

    auto input = Input::get_instace();

    auto renderer = std::make_shared<Renderer>();
    renderer->create_buffers( width, height );

    auto window = std::make_shared<Window>();
    window->create( width, height, scale );

    Texture checker;
    checker.load( "../../assets/checker.png" );

    float4x4 model_mat;

    float4x4 view_mat = float4x4(1.0f);
    float3 camera_position = float3( 0.0f, 0.0f, -7.5f );

    float4x4 proj_mat = float4x4( 1.0f );
    proj_mat.prespective( 75.0f, ( float ) width / ( float ) height, 0.1f, 100.0f );

    // ############################### load OBJ 

    std::string inputfile = "../../assets/cube.obj";
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string err;
    bool ret = tinyobj::LoadObj( &attrib, &shapes, &materials, &err, inputfile.c_str() );

    if( !err.empty() ) {
        std::cerr << err << std::endl;
    }

    if( !ret ) { return 0; }

    std::vector<Triangle> triangles;
    std::vector<Vertice> vertices;

    for( size_t s = 0; s < shapes.size(); s++ ) {

        size_t index_offset = 0;
        for( size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++ ) {
            int fv = shapes[s].mesh.num_face_vertices[f];

            for( size_t v = 0; v < fv; v++ ) {

                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                Vertice vertice;

                vertice.pos.x = attrib.vertices[3 * idx.vertex_index + 0];
                vertice.pos.y = attrib.vertices[3 * idx.vertex_index + 1];
                vertice.pos.z = attrib.vertices[3 * idx.vertex_index + 2];

                vertice.normal.x = attrib.normals[3 * idx.normal_index + 0];
                vertice.normal.y = attrib.normals[3 * idx.normal_index + 1];
                vertice.normal.z = attrib.normals[3 * idx.normal_index + 2];

                vertice.uv.x = attrib.texcoords[2 * idx.texcoord_index + 0];
                vertice.uv.y = attrib.texcoords[2 * idx.texcoord_index + 1];

                vertices.push_back( vertice );

            }
            index_offset += fv;

        }
    }

    const size_t v_count = vertices.size() / 3;
    for( size_t i = 0; i < v_count; ++i ) {

        Triangle t;
        t.triangle[0] = vertices[i * 3 + 0];
        t.triangle[1] = vertices[i * 3 + 1];
        t.triangle[2] = vertices[i * 3 + 2];

        triangles.push_back( t );
    }

    // ################# END OF OBJ LOAD

    float time = 0.0f;

    while( running ) {
        input->update();
        running = !input->quit();

        model_mat.identity();
        model_mat.rotate_y(time* 0.1f);

        view_mat.translate( camera_position.x, camera_position.y, camera_position.z );

        renderer->clear( 0xff111111 );

        float4x4 model_view_mat = view_mat * model_mat;
        float4x4 mvp = proj_mat * model_view_mat;
        
        renderer->bind( &checker );
        renderer->bind_mvp( mvp );

        for( size_t i = 0; i < triangles.size(); ++i )
        {
            renderer->render_triangle( triangles[i] );
        }

        auto final_buffer = renderer->get_color_buffer();
        window->present( final_buffer );
        time += 0.016f;
    }

    return 0;
}
