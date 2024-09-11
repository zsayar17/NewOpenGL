#version 330 core

// !!! if the gl_FragCoord is manipulated then early depth test will fail and decrease the performance


out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material {
    float shininess;
};

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;

uniform Material material;

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;

    float innerCutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_POINT_LIGHTS 4
#define NR_SPOT_LIGHTS 1
#define NR_DIR_LIGHTS 1

uniform vec3 viewPos;
uniform DirLight directionalLights[NR_DIR_LIGHTS];
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

float CalcDiffuse(vec3 normal, vec3 lightDir);
float CalcSpecular(vec3 normal, vec3 lightDir, vec3 viewDir);
vec3 CalcDirLight(DirLight light, float spec, float diff, vec3 diffuseTextureColor, vec3 specularTextureColor);
vec3 CalcPointLight(PointLight light, float spec, float diff, vec3 diffuseTextureColor, vec3 specularTextureColor);
vec3 CalcSpotLight(SpotLight light, float spec, float diff, vec3 diffuseTextureColor, vec3 specularTextureColor);

vec3 CalcDirLights(vec3 normal, vec3 viewDir, vec3 diffuseTextureColor, vec3 specularTextureColor);
vec3 CalcPointLights(vec3 normal, vec3 viewDir, vec3 diffuseTextureColor, vec3 specularTextureColor);
vec3 CalcSpotLights(vec3 normal, vec3 viewDir, vec3 diffuseTextureColor, vec3 specularTextureColor);

float linearizeDepth(float depth);

void main()
{
    vec3 diffuseTextureColor = texture(diffuseMap, TexCoord).rgb;
    vec3 specularTextureColor = texture(specularMap, TexCoord).rgb;

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0.0);

    result += CalcDirLights(norm, viewDir, diffuseTextureColor, specularTextureColor);
    result += CalcPointLights(norm, viewDir, diffuseTextureColor, specularTextureColor);
    //result += CalcSpotLights(norm, viewDir, diffuseTextureColor, specularTextureColor);

    FragColor = vec4(result, 1.0);

    //FragColor = vec4(vec3(gl_FragCoord.z), 1.0);

    //FragColor = vec4(vec3(linearizeDepth(gl_FragCoord.z)), 1.0);
    //FragColor = texture(diffuseMap, TexCoord);
}

float CalcDiffuse(vec3 normal, vec3 lightDir)
{
    return max(dot(normal, lightDir), 0.0);
}

float CalcSpecular(vec3 normal, vec3 lightDir, vec3 viewDir)
{
    vec3 reflectDir = reflect(-lightDir, normal);

    return pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
}

vec3 CalcDirLight(DirLight light, float spec, float diff, vec3 diffuseTextureColor, vec3 specularTextureColor)
{
    vec3 ambient  = light.ambient  * diffuseTextureColor;
    vec3 diffuse  = light.diffuse  * diff * diffuseTextureColor;
    vec3 specular = light.specular * spec * specularTextureColor;

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, float spec, float diff, vec3 diffuseTextureColor, vec3 specularTextureColor)
{
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * pow(distance, 2));

    vec3 ambient  = light.ambient  * diffuseTextureColor * attenuation;
    vec3 diffuse  = light.diffuse  * diff * diffuseTextureColor * attenuation;
    vec3 specular = light.specular * spec * specularTextureColor * attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, float spec, float diff, vec3 diffuseTextureColor, vec3 specularTextureColor)
{
    vec3 lightDir = normalize(light.position - FragPos);
    float theta = dot(normalize(light.direction), -lightDir);
    float epsilon = light.innerCutOff - light.outerCutOff;
    float intensity = smoothstep(0.0, 1.0, (theta - light.outerCutOff) / epsilon);

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * pow(distance, 2));

    vec3 ambient  = light.ambient  * diffuseTextureColor * attenuation;
    vec3 diffuse  = light.diffuse  * diff * diffuseTextureColor * attenuation;
    vec3 specular = light.specular * spec * specularTextureColor * attenuation;

    return (ambient + diffuse + specular) * intensity;
}

vec3 CalcDirLights(vec3 normal, vec3 viewDir, vec3 diffuseTextureColor, vec3 specularTextureColor)
{
    vec3 result;

    for (int i = 0; i < NR_DIR_LIGHTS; i++)
    {
        vec3 lightDir = normalize(-directionalLights[i].direction);

        float diff = CalcDiffuse(normal, lightDir);
        float spec = CalcSpecular(normal, lightDir, viewDir);
        result += CalcDirLight(directionalLights[i], spec, diff, diffuseTextureColor, specularTextureColor);
    }

    return result;
}

vec3 CalcPointLights(vec3 normal, vec3 viewDir, vec3 diffuseTextureColor, vec3 specularTextureColor)
{
    vec3 result;

    for (int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        float diff = CalcDiffuse(normal, normalize(pointLights[i].position - FragPos));
        float spec = CalcSpecular(normal, normalize(pointLights[i].position - FragPos), viewDir);
        result += CalcPointLight(pointLights[i], spec, diff, diffuseTextureColor, specularTextureColor);
    }

    return result;
}

vec3 CalcSpotLights(vec3 normal, vec3 viewDir, vec3 diffuseTextureColor, vec3 specularTextureColor)
{
    vec3 result;

    for (int i = 0; i < NR_SPOT_LIGHTS; i++)
    {
        float diff = CalcDiffuse(normal, normalize(spotLights[i].position - FragPos));
        float spec = CalcSpecular(normal, normalize(spotLights[i].position - FragPos), viewDir);
        result += CalcSpotLight(spotLights[i], spec, diff, diffuseTextureColor, specularTextureColor);
    }

    return result;
}

float linearizeDepth(float depth)
{
    // From 0-1 range to NDC (0-1)
    float near = 0.1;
    float far = 100.0;
    float ndc = depth * 2.0 - 1.0;
    // re-calc z in clip space becasue of the perspective division
    float linear = (2.0 * near * far) / (far + near - ndc * (far - near));

    // devide by far plane to get the depth in the range 0-1
    return linear / far;
}

