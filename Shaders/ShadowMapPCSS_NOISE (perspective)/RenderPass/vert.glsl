#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 lightView;
uniform mat4 lightProjection;

out vec4 FragPos;
out vec3 Normal;
out vec4 FragPosLightSpace;

out vec2 lightProjectionParams; // Конкретные значение матрицы перспективной проекции

void main()
{
    FragPos = model * vec4(aPos, 1.0);
    Normal = mat3(transpose(inverse(model))) * aNormal;
    FragPosLightSpace = lightProjection * lightView * FragPos;
    lightProjectionParams = vec2(lightProjection[2][2], lightProjection[2][3]);
    gl_Position = projection * view * FragPos;
}