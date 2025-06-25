#version 330 core
layout(location = 0) out vec4 FragColor;
in vec2 u_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    // Convert texture coordinates to [-1, 1] space
    vec2 centeredCoord = u_TexCoord * 2.0 - 1.0;
    float distance = length(centeredCoord);
    if(distance > 1.0){
        discard;
    }
    vec4 texColor = texture(u_Texture, u_TexCoord);
    FragColor = texColor;// + vec4(0.0f, 0.0f, 0.5f, 0.5f);
}