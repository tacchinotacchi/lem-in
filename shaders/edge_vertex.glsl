#version 330
layout(location = 0) in vec3 world_coord;

out vec3 camera;

uniform mat4 transform;
uniform mat4 rotation;
uniform mat4 perspective;

void	main()
{
	vec4 view;

	view = rotation * transform * vec4(world_coord, 1.0);
	camera = view.xyz;
	gl_Position = perspective * view;
}
