#version 330

in  vec4 vVertex; 

out vec3 texCoords;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

void main() {
	texCoords = vVertex.xyz; ///Pass them to the fragment shader

	gl_Position = projectionMatrix * modelViewMatrix * vVertex;
}