#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject
{
    mat4 modelview;
    mat4 proj;
} ubo;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec3 normals;

layout(location = 0) out vec3 vert_color;
layout(location = 1) out vec2 vert_uv;
layout(location = 2) out vec3 vert_normal;

out gl_PerVertex
{
	vec4 gl_Position;
};

void main()
{
	gl_Position = ubo.proj * ubo.modelview * vec4(position, 1.0f);
	vert_color = color;
	vert_uv = uv;
	vert_normal = normals;
}

