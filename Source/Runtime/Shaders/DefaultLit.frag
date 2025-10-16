#version 330 core

in vec3 v_Normal;
in vec3 v_FragPos;

out vec4 FragColor;

uniform vec3 u_AlbedoColor;
uniform vec3 u_CameraPos;

void main()
{
    vec3 lightDir = normalize(vec3(0.5, 1.0, 0.3));
    vec3 normal = normalize(v_Normal);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 diffuse = diff * u_AlbedoColor;
    vec3 ambient = 0.1 * u_AlbedoColor;

    FragColor = vec4(ambient + diffuse, 1.0);
}