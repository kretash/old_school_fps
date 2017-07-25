#version 410

in vec2 uv0;
out vec4 frag_color;

uniform sampler2D framebuffer;

void main() {
  vec3 color = texture( framebuffer, uv0 ).rgb;
  frag_color = vec4( color, 1.0f );
}