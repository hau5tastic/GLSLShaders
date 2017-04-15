#version 330
in  vec3 vertNormal;
in  vec3 lightDir;
in  vec3 lightDir2;
out vec4 fragColor;

void main() { 
	/// I could have passed these in as Uniforms but for simplicity, 
	/// I'll just define them here: specular, diffuse, ambient for the surface material 
	const vec4 ks = vec4(0.5, 0.5, 0.5, 0.0);
	const vec4 kd = vec4(0.0, 0.0, 1.0, 0.0); /// const means it cannot be changed just like C++
	const vec4 ka = 0.05 * kd;
	
	const vec4 ks2 = vec4(0.0, 1.0, 0.0, 0.0);
	const vec4 kd2 = vec4(0.0, 1.0, 0.0, 0.0);					
	
	/// The reflect() method this most GPU expensive step in this proceedure
	/// The Blinn-Phong method is faster.   	
	vec3 reflection = normalize(reflect(-lightDir, vertNormal));
	float diff = max(dot(vertNormal, lightDir), 0.0);
	float spec = max(0.0, dot(vertNormal, reflection));
	if(diff != 0.0){
		spec = pow(spec,16.0);
	}

	vec3 reflection2 = normalize(reflect(-lightDir2, vertNormal));
	float diff2 = max(dot(vertNormal, lightDir2), 0.0);
	float spec2 = max(0.0, dot(vertNormal, reflection2));
	if(diff2 != 0.0){
		spec2 = pow(spec2, 16.0);
	}

	fragColor =  ka + ((diff * kd) + (spec * ks)) + ((diff2 * kd) + (spec2 * ks));	
}