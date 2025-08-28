#version 410 core
out vec4 FragColor;

uniform vec3 cameraPos; // ? Camera position, by this moment will be the light position
uniform vec4 lightColor;

in vec4 vColor;
in vec3 vNormal;
in vec3 vFragPos;

void main() {
	// ambient
	vec4 ambientStrength = vec4(0.2, 0.2, 0.2, 1.0);
	vec4 ambient = ambientStrength * lightColor;

	// diffuse
	vec3 norm = normalize(vNormal);
	vec3 lightDir = normalize(cameraPos - vFragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * lightColor;

	// specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(cameraPos - vFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec4 specular = specularStrength * spec * lightColor;

	vec4 result = (ambient + diffuse + specular) * vColor;
	float gamma = 2.2;
	FragColor= vec4(pow(result.rgb, vec3(1.0/gamma)), result.a);
}
