#version 330
in vec4 vVertex;
in vec4 vNormal;

out vec4 eyePos;
out vec3 vertNormal;
out vec3 lightDir;

// Reflection
out vec4 newVert;

uniform vec4 lightPos;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

void main() {
	newVert = vVertex;

	vertNormal = normalMatrix * vNormal.xyz; /// Rotate the normal to the correct orientation 
	eyePos = modelViewMatrix * vVertex; /// Create the eye vector 
	lightDir = normalize(lightPos.xyz - vec3(eyePos)); /// Create the light direction

	gl_Position =  projectionMatrix * modelViewMatrix * vVertex; 
}