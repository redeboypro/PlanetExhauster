#version 150

in vec2 frag_uv;

out vec4 out_color;

uniform sampler2D main_texture;

void main(void) {
   out_color = texture(main_texture, frag_uv);
}