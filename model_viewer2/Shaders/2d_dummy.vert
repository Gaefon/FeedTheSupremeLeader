#version 450
#extension GL_ARB_separate_shader_objects : enable

out gl_PerVertex
{
	vec4 gl_position;
}

layout(location = 0) out vec3 vert_color

vec2 position[3] = vec2[]
(
	vec2(0.0f, 0.5f),
	vec2(0.5f, -0.5),
	vec2(-0.5f, -0.5f)
);

vec3 colors[3] = vec3[]
(
	vec3(1.0, 0.0, 0.0),
	vec3(0.0, 1.0, 0.0),
	vec3(0.0, 0.0, 1.0)
);


void main(void)
{
	gl_position = vec4(positions[gl_VertexIndex], 0.0f, 1.0f);
	vert_color = colors[gl_VertexIndex];
}
