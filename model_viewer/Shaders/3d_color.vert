#version 330 core

in vec3 in_vertex;
in vec3 in_color;
in vec3 in_normal;
in vec2 in_uv;

uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 normal;

out vec3 fragment_color;
out vec3 fragment_normal;
out vec2 fragment_uv;

void main()
{
	gl_Position = projection * modelview * vec4(in_vertex, 1.0);
	vec4 calc_norm = normal * vec4(in_normal, 0.0);
	
	fragment_normal = calc_norm.xyz;
	fragment_color = in_color;
	fragment_uv = in_uv;
}
