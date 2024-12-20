#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec2 texCoords;
    vec3 FragPos;
    vec3 Normal;
} gs_in[];

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform float time;

vec4 explode(vec4 position, vec3 normal)
{
    float magnitude = 2.0;
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude;
    return position + vec4(direction, 0.0);
}

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void main() {
    /*vec3 normal = GetNormal();

    gl_Position = explode(gl_in[0].gl_Position, normal);
    TexCoord = gs_in[0].texCoords;
    Normal = normal;
    FragPos = gs_in[0].FragPos;
    EmitVertex();

    gl_Position = explode(gl_in[1].gl_Position, normal);
    TexCoord = gs_in[1].texCoords;
    Normal = normal;
    FragPos = gs_in[1].FragPos;
    EmitVertex();

    gl_Position = explode(gl_in[2].gl_Position, normal);
    TexCoord = gs_in[2].texCoords;
    Normal = normal;
    FragPos = gs_in[2].FragPos;
    EmitVertex();*/

    gl_Position = gl_in[0].gl_Position;
    TexCoord = gs_in[0].texCoords;
    Normal = gs_in[0].Normal;
    FragPos = gs_in[0].FragPos;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    TexCoord = gs_in[1].texCoords;
    Normal = gs_in[1].Normal;
    FragPos = gs_in[1].FragPos;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    TexCoord = gs_in[2].texCoords;
    Normal = gs_in[2].Normal;
    FragPos = gs_in[2].FragPos;
    EmitVertex();

    EndPrimitive();
}
