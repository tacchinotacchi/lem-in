#version 330

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vertex_data {
	float texture_alphas[4];
} vertex_out[];

out vec2 texture_coords;
out float texture_alphas[3];

uniform float node_scale;

void	set_texture_alphas()
{
	texture_alphas[0] = vertex_out[0].texture_alphas[0];
	texture_alphas[1] = vertex_out[0].texture_alphas[1];
	texture_alphas[2] = vertex_out[0].texture_alphas[2];
}

void	main()
{
	gl_Position = gl_in[0].gl_Position + vec4(-node_scale, node_scale, 0.0, 0.0);
	texture_coords = vec2(0.0, 0.0);
	set_texture_alphas();
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(-node_scale, -node_scale, 0.0, 0.0);
	texture_coords = vec2(0.0, 1.0);
	set_texture_alphas();
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(node_scale, node_scale, 0.0, 0.0);
	texture_coords = vec2(1.0, 0.0);
	set_texture_alphas();
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(node_scale, -node_scale, 0.0, 0.0);
	texture_coords = vec2(1.0, 1.0);
	set_texture_alphas();
	EmitVertex();
	EndPrimitive();
}
