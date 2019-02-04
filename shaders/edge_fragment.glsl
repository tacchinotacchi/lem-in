#version 330

layout(location = 0) out vec4 color;

in vec2 texture_coords;

//uniform float start;
//uniform float end;
uniform sampler2D edge_tex;

void	main()
{
	vec4 temp_color;

	temp_color = texture(edge_tex, texture_coords);
	color = vec4(temp_color.g, temp_color.b, temp_color.r, temp_color.a);
	if (color.a < 0.9)
		discard;
}
