#version 450

uniform mat4 u_vp;

in      vec2 i_pos;
in      vec2 i_uv0;
in      vec4 i_colour;

out     vec2 o_uv0;
out     vec4 o_colour;

void main() {
    gl_Position = u_vp * vec4(i_pos.x, i_pos.y, 0, 1.0);
    o_uv0    = i_uv0;
    o_colour = i_colour / 255.0;
}
