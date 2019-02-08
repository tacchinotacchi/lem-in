#version 330

layout(location = 0) out vec4 color;

in vec2 texture_coords;

uniform sampler2D ant_tex;

void	main()
{
	color = texture(ant_tex, texture_coords);
	if (color.a < 0.9)
		discard;
}
