#version 330

in vec4 newVert;

out vec4 fragColor;

uniform samplerCube mySkyBox;  
uniform mat4 modelViewMatrix;

void main() { 
	vec4 normVert = normalize(newVert);
	   
	vec3 eyeDir = normalize(vec3(modelViewMatrix * normVert));
		
	vec3 reflection = reflect(eyeDir, normVert.xyz);
	vec3 refraction = refract(eyeDir, normVert.xyz, 1.0/1.6);

	// Converts from eye to world space
	reflection = vec3(inverse(modelViewMatrix) * vec4(reflection, 0.0));
	refraction = vec3(inverse(modelViewMatrix) * vec4(refraction, 0.25));

	vec3 normReflection = normalize(reflection);
	vec3 normRefraction = normalize(refraction);

	//fragColor = texture(mySkyBox, normReflection);
	fragColor = mix(texture(mySkyBox, normReflection), texture(mySkyBox, normRefraction), 0.016);
} 