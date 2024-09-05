#version 460 core

layout(location = 0) out float FragDepth;

uniform float expK;

in vec4 coord;

void main()
{
    float depth = coord.z;
    FragDepth = exp(expK * depth);
}