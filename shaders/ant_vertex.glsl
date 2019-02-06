#version 330
layout(location = 0) in vec3 world_coord;

uniform mat4 transform;
uniform mat4 rotation;
uniform mat4 perspective;

void	main()
{
	gl_Position = perspective * rotation * transform * vec4(world_coord, 1.0);
	gl_Position.z -= 0.010;
}
