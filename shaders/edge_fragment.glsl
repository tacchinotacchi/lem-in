#version 330

layout(location = 0) out vec4 color;

in vec2 texture_coords;

uniform sampler2D edge_tex;

void	main()
{
	color = texture(edge_tex, texture_coords);
	if (color.a < 0.9)
		discard;
}
