#version 460 core

layout(location = 0) out float FragDepth;

uniform float expK = 0.5;

void main()
{
    float depth = gl_FragCoord.z / gl_FragCoord.w;
    FragDepth = exp(expK * depth);
}