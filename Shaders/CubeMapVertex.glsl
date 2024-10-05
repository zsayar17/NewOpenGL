#version 330 core

layout(Location = 0) in vec3 aPos;

out vec3 TexCoords;
uniform mat4 view;

void main()
{
    TexCoords = aPos;

    gl_Position = view * vec4(aPos, 1.0);
    gl_Position = gl_Position.xyww;
}
