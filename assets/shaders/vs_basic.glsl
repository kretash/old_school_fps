#version 120
#extension GL_EXT_gpu_shader4 : require

varying vec2 uv0;

void main() {

  vec2 uv = vec2( 0, 0 );
  if( ( gl_VertexID & 1 ) != 0 )uv.x = 1;
  if( ( gl_VertexID & 2 ) != 0 )uv.y = 1;

  uv0 = uv * 2;
  uv0.y = 1.0f - uv0.y;

  gl_Position.xy = uv * 4 - 1;
  gl_Position.zw = vec2( 0, 1 );
}