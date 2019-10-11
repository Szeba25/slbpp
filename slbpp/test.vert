#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 projection;
uniform mat4 view;

out vec3 color;

void main()
{
    gl_Position = projection * view * vec4(aPos.x, aPos.y, 0.0f, 1.0f);
	color = aColor;
}