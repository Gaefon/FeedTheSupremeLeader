#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 vert_uv;
layout(location = 2) in vec3 vert_normal;

layout(location = 0) out vec4 outColor;

void main()
{
	vec3 light_color = vec3(1.0, 1.0, 1.0);
	vec3 light_direction = vec3(0.0, 0.707f, -0.707f);
	float intensity = 0.5;
	
	float diffuse_intensity = max(0.0, dot(normalize(vert_normal), -light_direction)); 
	
	outColor = texture(texSampler, vert_uv);
	
	outColor = vec4(outColor.xyz, 1.0) * vec4(light_color * (intensity + diffuse_intensity), 1.0);
}


