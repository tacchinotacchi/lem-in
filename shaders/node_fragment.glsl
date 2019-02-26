#version 330

in float texture_alphas[3];
in vec2 texture_coords;

layout(location = 0) out vec4 color;

uniform sampler2D node_tex;
uniform sampler2D start_tex;
uniform sampler2D end_tex;

void	main()
{
	color = texture_alphas[0] * texture(node_tex, texture_coords);
	color += texture_alphas[1] * texture(start_tex, texture_coords);
	color += texture_alphas[2] * texture(end_tex, texture_coords);
	if (color.a < 0.9)
		discard;
}
