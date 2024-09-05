#version 460 core

layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 coord;

void main()
{
    vec4 outCoord = projection * view * model * vec4(aPos, 1.0);
    coord = outCoord;
    gl_Position = outCoord;
}