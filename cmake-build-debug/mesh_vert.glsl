#version 150

in vec3 in_position;
in vec2 in_uv;

out vec2 frag_uv;

uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat4 projection_matrix;

void main(void) {
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_position, 1.0); 
    frag_uv = in_uv;
}