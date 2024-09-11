#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;

uniform sampler2D diffuseMap;

void main()
{
    vec3 result = vec3(abs(Normal.z));
    FragColor = vec4(result, 1.0);
    //FragColor = texture(diffuseMap, TexCoords);
}
