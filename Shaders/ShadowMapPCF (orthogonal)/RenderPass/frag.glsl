#version 460 core

out vec4 FragColor;

in vec4 FragPos;
in vec3 Normal;
in vec4 FragPosLightSpace;

uniform sampler2D shadowMap;
uniform vec3 lightPos;
uniform float shadowBias = 0.001;
uniform float pcfRadius = 1.5;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // Конвертация из [-1, 1] в [0, 1]
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    // Проверка на тень
    if (projCoords.z > 1.0)
        return 0.0;
    
    // Тень с использованием PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize * pcfRadius).r;
            shadow += projCoords.z - shadowBias > pcfDepth ? 1.0 : 0.0;
        }
    }

    return shadow / 9.0;
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