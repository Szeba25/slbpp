#version 330 core
layout (location = 0) in vec2 positionData;
layout (location = 1) in vec3 tintColorData;
layout (location = 2) in vec2 texCoordData;

uniform mat4 projection;
uniform mat4 view;

out vec3 fragTintColor;
out vec2 fragTexCoord;

void main()
{
    gl_Position = projection * view * vec4(positionData, 0.0f, 1.0f);
	fragTintColor = tintColorData;
	fragTexCoord = texCoordData;
}
