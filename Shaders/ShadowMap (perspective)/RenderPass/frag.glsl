#version 460 core

out vec4 FragColor;

in vec4 FragPos;
in vec3 Normal;
in vec4 FragPosLightSpace;

uniform sampler2D shadowMap;
uniform vec3 lightPos;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // Конвертация из [-1, 1] в [0, 1]
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    //Глубина текущего фрагмента из карты теней
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    float currentDepth = projCoords.z;

    // Проверка на тень
    float shadow = step(closestDepth + 0.005, currentDepth);

    return shadow;
}

void main()
{
    vec3 color = vec3(0.5);
    vec3 ambient = 0.15 * color;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos.xyz);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * color;

    float shadow = ShadowCalculation(FragPosLightSpace);                      
    vec3 lighting = (ambient + (1.0 - shadow) * diffuse);

    FragColor = vec4(lighting, 1.0);
}