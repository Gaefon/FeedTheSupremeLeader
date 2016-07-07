#version 330 core

in vec3 fragment_color;
in vec3 fragment_normal;

out vec4 out_Color;

void main()
{
	vec3 light_color = vec3(1.0, 1.0, 1.0);
	vec3 light_direction = vec3(0.0, 0.707f, -0.707f);
	float intensity = 0.25;
	
	
	float diffuse_intensity = max(0.0, dot(normalize(fragment_normal), -light_direction)); 
	
	out_Color = vec4(fragment_color, 1.0) * vec4(light_color * (intensity + diffuse_intensity), 1.0); 
	
	//out_Color = vec4(fragment_color, 1.0);
}
