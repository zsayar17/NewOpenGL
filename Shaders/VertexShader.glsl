#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

out VS_OUT {
    vec2 texCoords;
    vec3 FragPos;
    vec3 Normal;
} vs_out;

uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);

    TexCoord = vec2(aTexCoord.x, aTexCoord.y);

    //Normal = mat3(model) * aNormal;
    // transpose and inverse the model matrix to keep normals consistent when scaling
    Normal = mat3(transpose(inverse(model))) * aNormal;

    FragPos = vec3(model * vec4(aPos, 1.0f));

    vs_out.texCoords = TexCoord;
    vs_out.FragPos = FragPos;
    vs_out.Normal = Normal;
}
