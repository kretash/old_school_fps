#version 120
#extension GL_EXT_gpu_shader4 : require

varying vec2 uv0;
uniform sampler2D framebuffer;

void main() {
  vec3 color = texture2D( framebuffer, uv0 ).rgb;
  gl_FragColor = vec4( color, 1.0f );
}