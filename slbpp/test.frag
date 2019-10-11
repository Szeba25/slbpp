#version 330 core
out vec4 FragColor;

in vec3 fragTintColor;
in vec2 fragTexCoord;

uniform sampler2D textureData;

void main()
{
    FragColor = texture(textureData, fragTexCoord) * vec4(fragTintColor, 1.0f);
}
