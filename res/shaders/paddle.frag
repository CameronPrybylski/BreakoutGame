#version 330 core
layout(location = 0) out vec4 FragColor;
in vec2 u_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
   vec4 texColor = texture(u_Texture, u_TexCoord);
   FragColor = texColor;// + vec4(0.0f, 0.0f, 0.5f, 0.5f);
}