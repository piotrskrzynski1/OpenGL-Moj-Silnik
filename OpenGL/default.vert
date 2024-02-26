#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 camMatrix;
uniform mat4 Model;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
	gl_Position = camMatrix * vec4(aPos, 1.0);
	TexCoord = aTexCoord;
	FragPos = aPos;
	Normal = mat3(transpose(inverse(Model))) * aNormal;
}