#version 330
layout(location = 0) in vec3 world_coord;

uniform mat4 view;
uniform mat4 proj;

void	main()
{
	gl_Position = proj * view * vec4(world_coord, 1.0);
}
