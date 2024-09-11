#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D diffuseMap;

void main()
{
    vec4 texColor = texture(diffuseMap, TexCoord);

    // High threshold for discarding
    /*if(texColor.a < 0.6)
        discard;*/

    // Low threshold for discarding
    /*if(texColor.a < 0.1)
        discard;
    */
    FragColor = texColor;
}
