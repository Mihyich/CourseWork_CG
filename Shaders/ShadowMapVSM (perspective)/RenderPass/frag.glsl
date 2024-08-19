#version 460 core

out vec4 FragColor;

in vec4 FragPos;
in vec3 Normal;
in vec4 FragPosLightSpace;

uniform sampler2D shadowMap;
uniform vec3 lightPos;

float ChebyshevUpperBound(float moment1, float t)
{
    float moment2 = moment1 * moment1;
    float p = t <= moment1 ? 1.0 : 0.0;
    float variance = moment2 - (moment1 * moment1);
    variance = max(variance, 0.00002);
    float d = t - moment1;
    float p_max = variance / (variance + d * d);
    return max(p, p_max);
}

float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    float moment1 = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    
    return ChebyshevUpperBound(moment1, currentDepth);
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