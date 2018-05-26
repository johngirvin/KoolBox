#version 450

uniform sampler2D   u_texture;
in      vec2        o_uv0;
in      vec4        o_colour;
out     vec4        FragColor;

void main() {
    FragColor = texture(u_texture, o_uv0) * o_colour;
}
