#version 330
layout(location = 0) in vec3 world_coord;

uniform mat4 transform;
uniform mat4 rotation;

void	main()
{
	gl_Position = rotation * transform * vec4(world_coord, 1.0);
}
