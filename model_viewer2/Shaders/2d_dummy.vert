#version 450
#extension GL_ARB_separate_shader_objects : enable

out gl_PerVertex
{
	vec4 gl_position;
}

vec2 position[3] = 
{
	vec2(0.0f, 0.5f),
	vec2(0.5f, -0.5),
	vec2(-0.5f, -0.5f)
};

void main(void)
{
	gl_position = vec4(positions[gl_VertexIndex], 0.0f, 1.0f);
}
