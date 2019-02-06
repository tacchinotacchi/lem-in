#version 330
layout(location = 0) in vec3 world_coord;
layout(location = 1) in vec3 in_color;

out vec3 camera;
out vec4 active_color;

uniform mat4 transform;
uniform mat4 rotation;
uniform mat4 perspective;

void	main()
{
	vec4 view;

	view = rotation * transform * vec4(world_coord, 1.0);
	camera = view.xyz;
	active_color = vec4(in_color, 1 * float(length(in_color) > 0.0));
	gl_Position = perspective * view;
}
