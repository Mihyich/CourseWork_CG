// За основу взято: https://github.com/cforfang/opengl-shadowmapping

#version 460 core

out vec4 FragColor;

in vec4 FragPos;
in vec3 Normal;
in vec4 FragPosLightSpace;

uniform sampler2D shadowMap;
uniform vec3 lightPos;

float ChebyshevUpperBound(float moment1, float moment2, float t)
{
    if (t <= moment1)
        return 1.0;

    float variance = moment2 - (moment1 * moment1);
    variance = max(variance, 0.0005);

    float d = t - moment1;
    float p_max = variance / (variance + d * d);

    return p_max;
}

float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz;
    projCoords = projCoords * 0.5 + 0.5;

    float moment1 = texture(shadowMap, projCoords.xy).r;
    float moment2 = pow(moment1, 2.0) + 0.25 * (pow(dFdx(moment1), 2.0) + pow(dFdy(moment1), 2.0));    
    
    return clamp(ChebyshevUpperBound(moment1, moment2, projCoords.z), step(fragPosLightSpace.w, 0.0), 1.0);
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
    vec3 lighting = (ambient + (shadow) * diffuse);

    FragColor = vec4(lighting, 1.0);
}