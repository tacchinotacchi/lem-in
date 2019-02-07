#version 330
layout(location = 0) in vec3 world_coord;

out float texture_alphas_geom[4];

uniform mat4 transform;
uniform mat4 rotation;
uniform mat4 perspective;
uniform vec3 start_coord;
uniform vec3 end_coord;

void	main()
{
	gl_Position = perspective * rotation * transform * vec4(world_coord, 1.0);
	gl_Position.z -= 0.005;
	texture_alphas_geom[1] = 1 * float(length(world_coord - start_coord) < 0.1);
	texture_alphas_geom[2] = 1 * float(length(world_coord - end_coord) < 0.1);
	texture_alphas_geom[0] = 1 * float(texture_alphas_geom[1] == 0 && texture_alphas_geom[2] == 0);
	texture_alphas_geom[3] = texture_alphas_geom[1] * texture_alphas_geom[2];
}
