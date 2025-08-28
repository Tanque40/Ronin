#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 vColor;
out vec3 vNormal;
out vec3 vFragPos;

void main() {
	// Send to Fragment
	vColor = aColor;
	vNormal = mat3(transpose(inverse(model))) * aNormal;
	vFragPos = vec3(model * vec4(aPos, 1.0));

	//Use here
	gl_Position = projection * view * model * vec4(vFragPos, 1.0);
}
