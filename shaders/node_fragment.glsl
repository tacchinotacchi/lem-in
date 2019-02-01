#version 330

in vec2 texture_coords;

layout(location = 0) out vec4 color;

//uniform float start;
//uniform float end;
uniform sampler2D node_tex;

void	main()
{
	color = texture(node_tex, texture_coords);
}
