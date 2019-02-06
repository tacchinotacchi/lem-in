#version 330

layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;

out vec2 texture_coords;

uniform float ant_scale;
uniform float animation_time;

void	main()
{
	vec4	position;

	position = mix(gl_in[0].gl_Position, gl_in[1].gl_Position, animation_time);
	gl_Position = position + vec4(-ant_scale, ant_scale, 0.0, 0.0);
	texture_coords = vec2(0.0, 0.0);
	EmitVertex();
	gl_Position = position + vec4(-ant_scale, -ant_scale, 0.0, 0.0);
	texture_coords = vec2(0.0, 1.0);
	EmitVertex();
	gl_Position = position + vec4(ant_scale, ant_scale, 0.0, 0.0);
	texture_coords = vec2(1.0, 0.0);
	EmitVertex();
	gl_Position = position + vec4(ant_scale, -ant_scale, 0.0, 0.0);
	texture_coords = vec2(1.0, 1.0);
	EmitVertex();
	EndPrimitive();
}
