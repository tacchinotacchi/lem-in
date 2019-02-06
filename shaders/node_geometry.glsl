#version 330

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in float texture_alphas_geom[][4];

out vec2 texture_coords;
out float texture_alphas[4];

uniform float node_scale;

void	main()
{
	gl_Position = gl_in[0].gl_Position + vec4(-node_scale, node_scale, 0.0, 0.0);
	texture_coords = vec2(0.0, 0.0);
	texture_alphas[0] = texture_alphas_geom[0][0];
	texture_alphas[1] = texture_alphas_geom[0][1];
	texture_alphas[2] = texture_alphas_geom[0][2];
	texture_alphas[3] = texture_alphas_geom[0][3];
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(-node_scale, -node_scale, 0.0, 0.0);
	texture_coords = vec2(0.0, 1.0);
	texture_alphas[0] = texture_alphas_geom[0][0];
	texture_alphas[1] = texture_alphas_geom[0][1];
	texture_alphas[2] = texture_alphas_geom[0][2];
	texture_alphas[3] = texture_alphas_geom[0][3];
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(node_scale, node_scale, 0.0, 0.0);
	texture_coords = vec2(1.0, 0.0);
	texture_alphas[0] = texture_alphas_geom[0][0];
	texture_alphas[1] = texture_alphas_geom[0][1];
	texture_alphas[2] = texture_alphas_geom[0][2];
	texture_alphas[3] = texture_alphas_geom[0][3];
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(node_scale, -node_scale, 0.0, 0.0);
	texture_coords = vec2(1.0, 1.0);
	texture_alphas[0] = texture_alphas_geom[0][0];
	texture_alphas[1] = texture_alphas_geom[0][1];
	texture_alphas[2] = texture_alphas_geom[0][2];
	texture_alphas[3] = texture_alphas_geom[0][3];
	EmitVertex();
	EndPrimitive();
}
