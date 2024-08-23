#version 460 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D colorImage;

void main()
{
    FragColor = texture(colorImage, TexCoords).rgba;
}