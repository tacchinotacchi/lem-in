#version 330

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

out vec2 texture_coords;

uniform float node_scale;

void	main()
{
	gl_Position = gl_in[0].gl_Position + vec4(-node_scale, node_scale, 0.0, 0.0);
	texture_coords = vec2(0.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(-node_scale, -node_scale, 0.0, 0.0);
	texture_coords = vec2(0.0, 1.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(node_scale, node_scale, 0.0, 0.0);
	texture_coords = vec2(1.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(node_scale, -node_scale, 0.0, 0.0);
	texture_coords = vec2(1.0, 1.0);
	EmitVertex();
	EndPrimitive();
}
