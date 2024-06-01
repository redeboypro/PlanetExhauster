#version 150

in vec2 frag_uv;

out vec4 out_color;

uniform bool has_texture;
uniform vec4 color;
uniform sampler2D main_texture;

void main(void) {
   out_color = color;
   if (has_texture) out_color *= texture(main_texture, frag_uv);
}