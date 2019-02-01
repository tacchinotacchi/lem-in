#version 330

layout(location = 0) out vec4 color;

in vec2 texture_coords;

//uniform float start;
//uniform float end;
uniform sampler2D edge_tex;

void	main()
{
	color = vec4(1.0, 0.0, 0.0, 1.0);
}
