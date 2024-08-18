#version 460 core

out float FragColor;

uniform float expK = 80.0;

void main()
{
    float depth = gl_FragCoord.z / gl_FragCoord.w;
    FragColor = exp(expK * depth);
}