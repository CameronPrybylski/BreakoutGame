#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 texCoor;
layout (location = 2) in vec2 colorCoor;

out vec2 u_TexCoord;
uniform mat4 u_MVP;
void main()
{
   gl_Position = u_MVP * vec4(aPos, 0.0f, 1.0f);
   u_TexCoord = texCoor;
}