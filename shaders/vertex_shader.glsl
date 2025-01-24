#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 outColor;
out vec2 TexCoord;

uniform mat4 transform_matrix;

void main()
{
   gl_Position = transform_matrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   outColor = aColor;
   TexCoord = aTexCoord;
}