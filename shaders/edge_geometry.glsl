#version 330

layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;

out vec2 texture_coords;

uniform float edge_scale;

void	main()
{
	vec3 edge;
	vec3 perp;

	/*edge = vec3(gl_in[0].gl_Position.xy - gl_in[1].gl_Position.xy, 0.0);
	perp = normalize(cross(edge, vec3(0.0, 0.0, -1.0)));
	gl_Position = gl_in[0].gl_Position + vec4(-edge_scale, edge_scale, 0.0, 0.0);
	texture_coords = vec2(0.0, 0.0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(-node_scale, -node_scale, 0.0, 0.0);
	texture_coords = vec2(0.0, 1.0);
	EmitVertex();
	EndPrimitive();*/
}
