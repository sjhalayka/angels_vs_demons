#version 400
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colour;

uniform mat4 mvp_matrix;

out vec4 vertex_colour;


void main()
{
    gl_Position = mvp_matrix*vec4(position, 1);

    vertex_colour = vec4(colour, 1.0);
}
