#version 330
layout(location = 0) in vec3 world_coord;

out vertex_data {
	float texture_alphas[4];
} vertex_out;

uniform mat4 transform;
uniform mat4 rotation;
uniform mat4 perspective;
uniform vec3 start_coord;
uniform vec3 end_coord;

void	main()
{
	gl_Position = perspective * rotation * transform * vec4(world_coord, 1.0);
	gl_Position.z -= 0.005;
	vertex_out.texture_alphas[1] = 1 * float(length(world_coord - start_coord) < 0.01);
	vertex_out.texture_alphas[2] = 1 * float(length(world_coord - end_coord) < 0.01);
	vertex_out.texture_alphas[0] = 1
		* float(vertex_out.texture_alphas[1] == 0 && vertex_out.texture_alphas[2] == 0);
}
