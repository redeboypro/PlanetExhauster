#version 150

in vec2 in_position;
in vec2 in_uv;

out vec2 frag_uv;

uniform mat4 transform_matrix;

void main(void) {
    gl_Position = transform_matrix * vec4(in_position, 0.0, 1.0); 
    frag_uv = in_uv;
}