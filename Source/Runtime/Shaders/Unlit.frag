#version 330 core

in vec2 v_TexCoord;
out vec4 FragColor;

uniform vec3 u_AlbedoColor;

void main()
{
    FragColor = vec4(u_AlbedoColor, 1.0);
}