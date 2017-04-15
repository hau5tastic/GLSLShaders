#version 330
in  vec4 vVertex;
in  vec4 vNormal;
in  vec4 vColor;
out vec3 vertNormal;
out vec3 lightDir;
out vec3 lightDir2;
 
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform vec3 lightPos;
uniform vec3 lightPos2;

void main() {
	vertNormal = normalMatrix * vNormal.xyz; /// Rotate the normal to the correct orientation 
	vec4 eyePos = modelViewMatrix * vVertex; /// Create the eye vector 
	lightDir = normalize(lightPos - eyePos.xyz); /// Create the light direction 
	lightDir2 = normalize(lightPos2 - eyePos.xyz);

	gl_Position =  projectionMatrix * modelViewMatrix * vVertex; 
}
