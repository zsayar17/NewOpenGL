#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;

void main()
{
    gl_Position = view * model * vec4(aPos, 1.0f);

    TexCoord = vec2(aTexCoord.x, aTexCoord.y);

    //Normal = mat3(model) * aNormal;
    // transpose and inverse the model matrix to keep normals consistent when scaling
    Normal = mat3(transpose(inverse(model))) * aNormal;

    FragPos = vec3(model * vec4(aPos, 1.0f));
}
