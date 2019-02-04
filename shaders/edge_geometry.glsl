#version 330

layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;

in vec3 camera[];
out vec2 texture_coords;

uniform float edge_scale;

void	main()
{
	vec3 perp;

	perp = normalize(cross(camera[0], camera[0] - camera[1])) * edge_scale;
	gl_Position = gl_in[0].gl_Position + vec4(perp, 0.0);
	texture_coords = vec2(0.0, 0.4);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(-perp, 0.0);
	texture_coords = vec2(0.0, 0.6);
	EmitVertex();
	gl_Position = gl_in[1].gl_Position + vec4(perp, 0.0);
	texture_coords = vec2(1.0, 0.4);
	EmitVertex();
	gl_Position = gl_in[1].gl_Position + vec4(-perp, 0.0);
	texture_coords = vec2(1.0, 0.6);
	EmitVertex();
	EndPrimitive();
}
