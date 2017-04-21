#version 330

in  vec3 texCoords;

out vec4 fragColor;

uniform samplerCube skyBox;  

void main() { 
	vec3 newTexCoords = texCoords;
	newTexCoords.x *= -1.0f;

	fragColor = texture(skyBox, newTexCoords);
}