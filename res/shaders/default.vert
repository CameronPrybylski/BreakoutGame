#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 texCoor;

out vec2 u_TexCoord;
void main()
{
   gl_Position = vec4(aPos, 0.0f, 1.0f);
   u_TexCoord = texCoor;
}